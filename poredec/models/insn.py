"""
本模块定义了指令相关的类

- Insn: 指令基类
- PcodeInsn: Pcode指令
- DisasInsn: 反汇编指令
"""

from typing import Optional
import capstone
from pypcode import PcodePrettyPrinter, OpCode, PcodeOp, Varnode


__all__ = ["Insn", "PcodeInsn", "DisasInsn"]


class Insn:
    """指令基类"""

    @property
    def text(self) -> str:
        """指令字符串表示"""
        raise NotImplementedError("子类应该实现这个方法")

    @property
    def address(self) -> int:
        """指令地址"""
        raise NotImplementedError("子类应该实现这个方法")

    def __str__(self) -> str:
        return self.text

    def __repr__(self) -> str:
        return self.text


class PcodeInsn(Insn):
    """Pcode指令

    :ivar disas_insn: 所属的反汇编指令
    :ivar idx: 指令索引
    """

    pretty_printer = PcodePrettyPrinter()

    def __init__(self, op: PcodeOp, disas_insn: "DisasInsn", idx: int):
        super().__init__()
        self.op = op
        self.disas_insn = disas_insn
        self.idx = idx

    @property
    def address(self) -> int:
        """指令地址"""
        return self.disas_insn.address

    @property
    def opcode(self) -> OpCode:
        """P-code的操作码"""
        return self.op.opcode

    @property
    def inputs(self) -> list[Varnode]:
        """P-code的输入变量列表"""
        return self.op.inputs

    @property
    def output(self) -> Optional[Varnode]:
        """P-code的输出变量"""
        return self.op.output

    @property
    def text(self):
        return self.pretty_printer.fmt_op(self.op)

    def __hash__(self):
        return hash((self.disas_insn, self.idx))

    def __eq__(self, other):
        return (
            isinstance(other, PcodeInsn)
            and self.disas_insn == other.disas_insn
            and self.idx == other.idx
        )


class DisasInsn(Insn):
    """表示Capstone反汇编得到的指令
    :ivar address: 指令地址
    :ivar mnemonic: 指令助记符
    :ivar op_str: 指令操作数字符串
    :ivar size: 指令长度
    :ivar raw_bytes: 指令原始字节

    :ivar is_ret: 是否是返回指令
    :ivar is_call: 是否是调用指令
    :ivar is_jump: 是否是跳转指令
    :ivar is_cond: 是否是条件跳转指令
    :ivar succs: 后继指令地址列表。对于条件跳转指令，succs[0]为跳转目标地址(True分支)，succs[1]为顺序执行地址(False分支)
    """

    def __init__(self, address, mnemonic, op_str, raw_bytes, size):
        super().__init__()
        self._address: int = address
        self.mnemonic: str = mnemonic
        self.op_str: str = op_str
        self.raw_bytes: bytes = raw_bytes
        self.size: int = size

        self.is_ret: bool = False
        self.is_call: bool = False
        self.is_jump: bool = False
        self.is_cond: bool = False
        self.succs: list[int] = []

    @property
    def address(self) -> int:
        """指令地址"""
        return self._address

    @property
    def text(self) -> str:
        return f"{self.address:#08x}: {self.mnemonic} {self.op_str}"

    @classmethod
    def from_cs_insn(cls, cs_insn: capstone.CsInsn):
        """根据给定的Capstone指令创建一个LowInsn对象
        :param cs_insn: 给定的指令
        :type cs_insn: class:`capstone.CsInsn`
        """
        insn = cls(
            address=cs_insn.address,
            mnemonic=cs_insn.mnemonic,
            op_str=cs_insn.op_str,
            raw_bytes=bytes(cs_insn.bytes),
            size=cs_insn.size,
        )

        insn.is_ret = cls._is_ret(cs_insn)
        if insn.is_ret:
            insn.succs = []
            return insn

        next_addr = cs_insn.address + cs_insn.size
        insn.succs = [next_addr]

        insn.is_call = cls._is_call(cs_insn)
        if insn.is_call:
            return insn

        insn.is_jump = cls._is_jump(cs_insn)
        if insn.is_jump:
            insn.succs = cls._get_jump_targets(cs_insn)
            insn.is_cond = cls._is_cond(cs_insn)
            if insn.is_cond:
                insn.succs.append(next_addr)
            return insn

        return insn

    @classmethod
    def _is_cond(cls, cs_insn: capstone.CsInsn) -> bool:
        # ARM条件跳转指令的助记符列表
        conds = [
            "eq",  # Equal
            "ne",  # Not equal
            "cs",  # Same as "hs"
            "hs",  # Unsigned higher or same (or carry set).
            "cc",  # Same as "lo"
            "lo",  # Unsigned lower (or carry clear).
            "mi",  # Negative. The mnemonic stands for "minus".
            "pl",  # Positive or zero. The mnemonic stands for "plus".
            "vs",  # Signed overflow. The mnemonic stands for "V set".
            "vc",  # No signed overflow. The mnemonic stands for "V clear".
            "hi",  # Unsigned higher
            "ls",  # Unsigned lower or same
            "ge",  # Signed greater than or equal
            "lt",  # Signed less than
            "gt",  # Signed greater than
            "le",  # Signed less than or equal
        ]

        return any(cs_insn.mnemonic.endswith(cond) for cond in conds)

    @classmethod
    def _is_jump(cls, cs_insn: capstone.CsInsn) -> bool:
        """
        判断给定的ARM指令是否是跳转指令

        :param cs_insn: 给定的指令
        :type cs_insn: class:`capstone.CsInsn`
        :return: 如果该指令是跳转指令则返回True，否则返回False

        """
        return cs_insn.group(capstone.CS_GRP_JUMP)

    @classmethod
    def _is_call(cls, cs_insn: capstone.CsInsn) -> bool:
        """
        判断给定的ARM指令是否是调用指令

        :param cs_insn: 给定的指令
        :type cs_insn: class:`capstone.CsInsn`
        :return: 如果该指令是调用指令则返回True，否则返回False
        """
        return cs_insn.group(capstone.CS_GRP_CALL)

    @classmethod
    def _is_ret(cls, cs_insn: capstone.CsInsn) -> bool:
        """
        判断给定的ARM指令是否是返回指令

        :param cs_insn: 给定的指令
        :type cs_insn: class:`capstone.CsInsn`
        :return: 如果该指令是返回指令则返回True，否则返回False
        """
        # 'BX LR'
        if cs_insn.group(capstone.CS_GRP_JUMP) and cs_insn.op_str == "lr":
            return True

        # 'POP {.., PC}'
        if cs_insn.mnemonic == "pop" and "pc" in cs_insn.op_str:
            return True

        # 'LDM SP!, {PC}'
        if cs_insn.mnemonic.startswith("ldm") and "pc" in cs_insn.op_str.split(",")[1]:
            return True

        # 'MOV PC, LR'
        if cs_insn.mnemonic == "mov" and "pc, lr" in cs_insn.op_str:
            return True
        return False

    @classmethod
    def _get_jump_targets(cls, cs_insn: capstone.CsInsn) -> list[int]:
        jump_targets = []

        # direct jump
        if cs_insn.operands[0].type == capstone.arm.ARM_OP_IMM:
            jump_targets.append(cs_insn.operands[0].value.imm)

        return jump_targets

    def __hash__(self):
        return hash(self.address)

    def __eq__(self, other):
        return isinstance(other, DisasInsn) and self.address == other.address
