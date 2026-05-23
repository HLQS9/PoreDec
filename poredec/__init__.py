"""
PoREDec反编译器
"""

import shutil
from pathlib import Path
import logging

from .models.lift_mode import LiftMode
from .frontend.loader import ELFLoader
from .frontend.lifter import Lifter
from .frontend.cfg_builder import CFGBuilder
from .backend.loop_analyzer import LoopAnalyzer
from .backend.structure_converter import StructureConverter
from .utils.display import CodeFormatter, CFGDisplayer


__all__ = ["decompile", "DecompileOptions"]


class DecompileOptions:
    """反编译选项

    :ivar only_cfg: 是否只生成控制流图，不进行进一步的反编译
    :ivar debug_structure: 是否输出结构化代码生成的中间结果
    :ivar log_level: 日志级别
    """

    def __init__(self):
        self.only_cfg = False
        self.debug_structure = False
        self.log_level = logging.WARNING

    def set_only_cfg(self, only_cfg: bool):
        self.only_cfg = only_cfg
        return self

    def set_debug_structure(self, debug_structure: bool):
        self.debug_structure = debug_structure
        return self

    def set_log_level(self, log_level: int):
        self.log_level = log_level
        return self


def decompile(output_dir, binary_path, function_addr, opts: DecompileOptions):
    """反编译指定的二进制程序函数
    :param output_dir: 输出目录
    :param binary_path: 待分析的二进制程序路径
    :param function_addr: 待分析的函数地址
    :param opts: 反编译选项
    """
    output_dir = Path(output_dir)
    if not output_dir.exists():
        output_dir.mkdir(parents=True)

    low_cfg_path = output_dir / "cfg-disassemble.png"
    high_cfg_path = output_dir / "cfg-pcode.png"
    structured_cfg_path = output_dir / "cfg-structured.png"
    decompiled_code_path = output_dir / "decompiled.c"
    decompiled_code_simplify_path = output_dir / "decompiled_simplified.c"
    log_path = output_dir / "decompile.log"

    if opts.debug_structure:
        structure_debug_dir = output_dir / "debug-structure"
        if structure_debug_dir.exists():
            shutil.rmtree(structure_debug_dir)
    else:
        structure_debug_dir = None

    logger = logging.getLogger("pore-dec")
    logger.setLevel(opts.log_level)
    logger.addHandler(logging.FileHandler(log_path))

    loader = ELFLoader(binary_path)
    lifter = Lifter(loader)
    cf = CodeFormatter()
    cd = CFGDisplayer(cf)

    cfg_builder = CFGBuilder(lifter)
    low_cfg = cfg_builder.build_cfg(function_addr)
    cd.draw_cfg(low_cfg, low_cfg_path)

    high_cfg = lifter.lift_cfg(low_cfg, LiftMode.HIGH)
    cd.draw_cfg(high_cfg, high_cfg_path)

    # 生成控制流图后直接返回
    if opts.only_cfg:
        return

    loop_info = LoopAnalyzer.analyze_loop(high_cfg)
    structure_converter = StructureConverter(
        high_cfg, loop_info, intermediate_output_dir=structure_debug_dir, log=logger
    )
    structured_cfg = structure_converter.convert()
    cd.draw_cfg(structured_cfg, structured_cfg_path)

    if opts.debug_structure:
        structured_cfg_dbg_path = output_dir / "cfg-structured-disassembly.png"
        cf.configure(no_pcode=True)
        cd.draw_cfg(
            structured_cfg,
            structured_cfg_dbg_path,
            highlights=structured_cfg.entry.insns,
        )

    cf.configure()
    decompiled_text = cf.fmt_stmts(structured_cfg.entry.insns)
    with decompiled_code_path.open("w") as f:
        f.write(decompiled_text)

    cf.configure(simplify=True)
    decompiled_simplified_text = cf.fmt_stmts(structured_cfg.entry.insns)
    with decompiled_code_simplify_path.open("w") as f:
        f.write(decompiled_simplified_text)
    cf.configure()
