"""反编译器主入口"""

import logging
from argparse import ArgumentParser
from pathlib import Path
import csv
import tempfile
import shutil

from . import DecompileOptions, decompile


def main():
    """反编译器入口函数"""
    parser = ArgumentParser(description="批量反编译工具")
    parser.add_argument("--tasks", help="任务列表文件路径")
    parser.add_argument("--binary", help="待分析的二进制程序路径")
    parser.add_argument("--function", help="待分析的函数地址，以十六进制形式表示")
    parser.add_argument(
        "--output", "-o", default="./outputs", help="反编译输出的结果存放目录的路径"
    )
    parser.add_argument(
        "--only-cfg",
        action="store_true",
        help="只生成控制流图，不进行进一步的反编译",
    )

    args = parser.parse_args()
    if not args.tasks and (not args.binary or not args.function):
        print("请指定--tasks或者--binary和--function")
        return
    if args.tasks and (args.binary or args.function):
        print("--tasks和--binary/--function不能同时指定")
        return

    if args.tasks:
        tasks_path = Path(args.tasks)
        if not tasks_path.exists():
            print(f"任务列表文件 {tasks_path} 不存在")
            return

        with open(tasks_path, "r", encoding="utf-8") as f:
            tasks = list(csv.reader(f))
        tasks = [(tasks_path.parent / task[0], task[1]) for task in tasks]
    else:
        tasks_path = Path(tempfile.mkdtemp(prefix="poredec_"))
        tasks = [(Path(args.binary), args.function)]

    opts = DecompileOptions()
    opts.set_only_cfg(args.only_cfg)
    opts.set_debug_structure(True)
    opts.set_log_level(logging.DEBUG)

    output_dir = Path(args.output)

    log_len = 0
    for i, (binary_path, function) in enumerate(tasks):
        function_addr = int(function, 16)

        process_log = f"正在反编译 {i}/{len(tasks)} 目标程序: {binary_path.stem} 函数: {function_addr:#X}"
        log_len = max(log_len, len(process_log))
        extra_space = (log_len - len(process_log)) * " "
        print(
            f"\r{process_log}{extra_space}",
            end="",
        )

        output_path = output_dir / f"{binary_path.stem}_{function_addr:X}"
        shutil.rmtree(output_path, ignore_errors=True)
        output_path.mkdir(parents=True, exist_ok=True)

        decompile(output_path, binary_path, function_addr, opts)

    print(f"\r反编译完成 {len(tasks)}/{len(tasks)}")

    print()
    print("反编译完成，结果存放在", args.output)


if __name__ == "__main__":
    main()
