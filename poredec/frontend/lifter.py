"""本模块基于capstone和pypcode提供了一个基础的代码提升器Lifter。
Lifter可以将机器码指令提升为汇编指令，也可以将基于汇编指令的控制流图提升为基于Pcode指令或伪C代码语句的控制流图。
"""

# -*- coding: utf-8 -*-
from typing import Optional
import capstone
import pypcode

from ..models.insn import DisasInsn, PcodeInsn
from ..models.cfg import ControlFlowGraph, CFGNode
from ..models.stmt import PcodeStmt
from ..models.lift_mode import LiftMode
from .loader import ELFLoader, ArchitectureException


__all__ = ["Lifter"]


class Lifter:
    """代码提升器

    :param loader: ELF文件加载器，用于加载目标ELF文件

    :example:

    >>> loader = ELFLoader("test.elf")
    >>> lifter = Lifter(loader)
    >>> insn = Lifter.disassemble_at(0xADD0)
    >>> print(insn) # 打印汇编指令

    >>> # 假定已经构建了一个基于汇编的控制流图cfg
    >>> high_cfg = lifter.lift_cfg(cfg, target_mode=LiftMode.HIGH)
    >>> print(high_cfg.entry.insns[0]) # 打印伪高级语言语句
    """

    ARCH_LANGUAGE = pypcode.ArchLanguage.from_id("ARM:LE:32:v8")

    def __init__(self, loader: ELFLoader) -> None:
        if loader.arch != "ARM":
            raise ArchitectureException("Only support ARM architecture")
        self.loader = loader
        self.ir_lifter = pypcode.Context(self.ARCH_LANGUAGE)
        self.cs = capstone.Cs(
            capstone.CS_ARCH_ARM,
            capstone.CS_MODE_ARM | capstone.CS_MODE_LITTLE_ENDIAN,
        )
        self.cs.detail = True
        self.cs.skipdata = False

    def disassemble_at(self, addr) -> Optional[DisasInsn]:
        """在给定的地址处反汇编一条指令

        :param addr: 指令地址
        :return: 反汇编得到的指令对象，如果地址无效或无法反汇编当前指令则返回None
        :rtype: class:`LowInsn`

        :example:

        >>> insn = cfg_builder.disassemble_at(0x401000)
        >>> if not insn:
        >>>     raise RuntimeError("无法反汇编%#x处指令", 0x401000)
        >>> print(insn)
        """
        prev_addr = self.loader.seek(addr)
        self.loader.seek(addr)
        data = self.loader.read(16)
        if data is None:
            return None
        tmp_insns = list(self.cs.disasm(data, addr, count=1))
        if not tmp_insns:
            return None
        insn = tmp_insns[0]
        self.loader.seek(prev_addr)
        return DisasInsn.from_cs_insn(insn)

    def lift_cfg(
        self, cfg: ControlFlowGraph, target_mode: LiftMode = LiftMode.HIGH
    ) -> ControlFlowGraph:
        """将控制流图中的指令提升到更高级的指令/语句，并构建基于高级指令的控制流图

        :param cfg: 待提升的控制流图
        :param target_mode: 目标指令/语句级别
        :return: 提升后的控制流图
        """
        assert target_mode in [LiftMode.LOW, LiftMode.MEDIUM, LiftMode.HIGH]

        trans = {node: node for node in cfg.nodes}

        # 提升到中间表示
        if cfg.lift_mode < LiftMode.MEDIUM and target_mode >= LiftMode.MEDIUM:
            for key, node in trans.items():
                trans[key] = self._lift_cfg_node_l2m(node)

        # 提升到高级语言
        if cfg.lift_mode < LiftMode.HIGH and target_mode >= LiftMode.HIGH:
            for key, node in trans.items():
                trans[key] = self._lift_cfg_node_m2h(node)

        # 构建新的控制流图
        lifted_cfg = ControlFlowGraph()
        lifted_cfg.lift_mode = target_mode
        lifted_cfg.set_entry(trans[cfg.entry])

        lifted_cfg.add_nodes_from(trans.values())
        for u, v, data in cfg.edges.data(data=True):
            lifted_cfg.add_edge(trans[u], trans[v], **data)

        return lifted_cfg

    def _lift_cfg_node_l2m(self, node: CFGNode):
        """提升控制流图节点，将汇编指令指令提升为Pcode中间表示"""
        ir_insns = []
        for insn in node.insns:
            assert isinstance(insn, DisasInsn), "节点中的指令不是DisasInsn，无法提升"
            ir_insns.extend(self._lift_insn_l2m(insn))
        assert ir_insns, f"无有效指令，无法提升控制流图节点{node.address:#X}"
        new_node = CFGNode(node.address, ir_insns)
        return new_node

    def _lift_cfg_node_m2h(self, node: CFGNode):
        """提升控制流图节点，将Pcode中间表示提升为高级语言语句"""
        new_node = CFGNode(node.address, node.insns)
        new_node.reset([PcodeStmt(insn) for insn in new_node.insns])
        return new_node

    def _lift_insn_l2m(self, insn: DisasInsn) -> list[PcodeInsn]:
        """将汇编指令指令提升为Pcode中间表示"""
        ir_insns = []
        try:
            translation = self.ir_lifter.translate(insn.raw_bytes, insn.address)
        except pypcode.BadDataError:
            return []

        for idx, op in enumerate(translation.ops[1:]):
            ir_insns.append(PcodeInsn(op, insn, idx))
        return ir_insns
