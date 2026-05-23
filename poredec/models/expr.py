"""
本模块包含高级语言表达式的定义
"""

from pypcode import Varnode


__all__ = ["Expression", "NotExpr", "VarExpr", "ConstExpr"]


class Expression:
    """高级语言表达式"""

    def logical_not(self) -> "Expression":
        """获取当前表达式的逻辑非表达式"""
        return NotExpr(self)

    def __repr__(self):
        return str(self)


class NotExpr(Expression):
    """逻辑非表达式"""

    def __init__(self, expr: Expression):
        self.expr = expr

    def __str__(self):
        return f"!{self.expr}"


class VarExpr(Expression):
    """变量表达式"""

    def __init__(self, varnode: Varnode):
        self.varnode = varnode

    def __str__(self):
        return self.fmt_vn(self.varnode)

    @staticmethod
    def fmt_vn(vn: Varnode) -> str:
        """格式化Varnode"""
        if vn.space.name == "const":
            return "%#x" % vn.offset
        elif vn.space.name == "register":
            name = vn.getRegisterName()
            if name:
                return name
        return f"{vn.space.name}_{vn.offset:x}_{vn.size:d}"


class ConstExpr(Expression):
    """常量表达式"""

    def __init__(self, value: int):
        self.value = value

    def logical_not(self):
        if self.value == 0:
            return ConstExpr(1)
        else:
            return ConstExpr(0)

    def __str__(self):
        return str(self.value)
