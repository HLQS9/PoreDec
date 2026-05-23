import enum
from .cfg import CFGNode


class ReduceRule(enum.IntEnum):
    """表示代码结构化时使用的化简规则"""

    NONE = 0  # 没有使用化简规则
    SEQUENCE = enum.auto()  # 顺序结构
    WHILE_TRUE = enum.auto()  # while(1)循环
    DO_WHILE = enum.auto()  # while(cond)循环
    IF_ELSE = enum.auto()  # if-else结构
    IF = enum.auto()  # 单个if结构
    IF_CONTINUE = enum.auto()  # if-continue结构
    IF_BREAK = enum.auto() # if-break结构
    SWITCH = enum.auto()  # switch结构
    GOTO_SEQUENCE = enum.auto()  # goto顺序结构
    GOTO_BRANCH = enum.auto()  # goto if-else结构
    GOTO_SWITCH = enum.auto()  # goto switch结构

    # 以下是辅助规则，不实际化简代码，用于调试
    ENTER_LOOP = enum.auto()  # 进入循环分析
    LEAVE_LOOP = enum.auto()  # 离开循环分析


class ReduceEvent:
    """控制流图节点化简事件"""

    def __init__(self, rule: ReduceRule, node: CFGNode):
        self.rule = rule
        self.address = node.address

    def __str__(self):
        return f"REDUCE#{self.rule.name}@{self.address:#X}"

    def __repr__(self):
        return str(self)
