from enum import IntEnum


__all__ = ['LiftMode']


class LiftMode(IntEnum):
    """代码提升模式"""

    LOW = 0  # 低级语言/汇编指令，DisasInsn
    MEDIUM = 1  # 中间表示，PcodeInsn
    HIGH = 2  # 高级语言，Statement
