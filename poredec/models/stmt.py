"""
(伪)高级语言代码语句
"""

from functools import cached_property

from .expr import Expression, VarExpr
from .insn import PcodeInsn, Insn


__all__ = [
    "Statement",
    "PcodeStmt",
    "IfStmt",
    "GotoStmt",
    "BreakStmt",
    "ContinueStmt",
    "SwitchStmt",
    "DoWhileStmt",
    "WhileStmt",
]


class Statement(Insn):
    """表示一条高级语言语句

    :ivar succ: 当前语句的下一条语句
    :ivar label: 语句的标签，若为None则表示没有标签
    """

    def __init__(self):
        super().__init__()
        self.label: str = None

    @property
    def text(self):  # Not implemented
        return f"<Statement at {id(self):#x}>"

    @property
    def address(self):
        return -1  # Unknown


class PcodeStmt(Statement):
    """表示一个低级语言语句"""

    def __init__(self, insn: PcodeInsn):
        super().__init__()
        self.op = insn.op
        self.disas_insn = insn.disas_insn
        self.idx = insn.idx
        self.comment = (
            f"{insn.address:#X} {insn.disas_insn.mnemonic} {insn.disas_insn.op_str}"
            if self.idx == 0
            else ""
        )

    @property
    def address(self):
        return self.disas_insn.address

    @property
    def opcode(self):
        return self.op.opcode

    @cached_property
    def inputs(self):
        return [VarExpr(var) for var in self.op.inputs]

    @cached_property
    def output(self):
        return VarExpr(self.op.output) if self.op.output else None


class IfStmt(Statement):
    """表示一个if-else语句"""

    def __init__(
        self, cond: Expression, true_body: list[Statement], false_body: list[Statement]
    ):
        super().__init__()
        self.cond = cond
        self.true_body = true_body
        self.false_body = false_body


class _BranchStmt(Statement):
    """作为Gotostmt、BreakStmt、ContinueStmt的基类，不能直接实例化"""

    def __init__(self, target: int):
        super().__init__()
        self.target = target

    @property
    def target_label(self) -> str:
        """跳转目标"""
        return f"LAB_{self.target:X}"


class GotoStmt(_BranchStmt):
    """表示一个goto语句"""


class BreakStmt(_BranchStmt):
    """表示一个break语句"""


class ContinueStmt(_BranchStmt):
    """表示一个continue语句"""


class SwitchStmt(Statement):
    """表示一个switch语句"""
    def __init__(self, cases):
        super().__init__()
        self.cases = cases


class _LoopStmt(Statement):
    """循环语句的基类

    :ivar cond: 循环的条件
    :ivar body: 循环体
    """

    def __init__(self, cond: Expression, body: list[Statement]):
        super().__init__()
        self.cond = cond
        self.body = body


class DoWhileStmt(_LoopStmt):
    """表示一个do while语句"""


class WhileStmt(_LoopStmt):
    """表示一个while语句"""
