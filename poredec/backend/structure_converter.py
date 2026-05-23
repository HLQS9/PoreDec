"""结构化代码生成器"""
# pylint: disable=pointless-string-statement
# pylint: disable=unused-argument
# pylint: disable=fixme

from ..models.cfg import CFGNode
from ..models.expr import ConstExpr
from .structure_converter_mixin import StructureConverterMixin, ReduceRule

__all__ = ["StructureConverter"]


class StructureConverter(StructureConverterMixin):

    def reduce_cfg(self, node, by_rule, loop=None) -> bool:
        """递归化简控制流图，尝试将多个节点化简为一个节点。

        函数会使用广度优先搜索遍历控制流图中从给定节点可达的所有节点，并在尝试化简这些节点——将节点与其后继节点合并。

        :param node: 待化简的节点
        :param by_rule: 为True时使用针对性规则化简，否则使用通用(goto)规则
        :param loop: 当给定loop时，只化简循环内的节点，否则化简所有node可达的节点。
        :return: 如果节点被化简为结构化语句，则返回True
        """
        if by_rule:
            reduce_node_func = self.reduce_node_by_rule
        else:
            reduce_node_func = self.reduce_node_by_goto

        if loop:
            return self.bfs_traverse_loop(node, reduce_node_func, loop)
        else:
            return self.bfs_traverse(node, reduce_node_func)

    def reduce_node_by_goto(self, node: CFGNode) -> bool:
        """使用goto规则化简控制流图节点。

        goto化简规则由`try_reduce_goto_`开头的函数实现。这些规则化简函数与
        :meth:`reduce_node_by_rule` 调用的规则化简函数类似；
        区别在于这些规则化函数只使用goto语句化简节点，并且一定能完成化简，并返回True。
        因此通常情况下，方法一定会返回True，否则说明实现的goto规则不完整。

        具体来说::

            识别如下结构
            node {stmt1}
                └── succ {stmt2}
            将其化简为
            node {stmt1; goto stmt2;}

        :param node: 待化简的控制流图节点
        :return: 如果节点被化简，则返回True。注意：函数返回False说明函数实现不完整
        """
        if not self.successors(node):
            return False

        if self.try_reduce_goto_sequence(node):
            self.emit_reduce_event(ReduceRule.GOTO_SEQUENCE, node)
            return True
        if self.try_reduce_goto_branch(node):
            self.emit_reduce_event(ReduceRule.GOTO_BRANCH, node)
            return True
        if self.try_reduce_goto_switch(node):
            self.emit_reduce_event(ReduceRule.GOTO_SWITCH, node)
            return True

        self.log.warning(
            f"goto规则不全面无法化简节点: {node.address:#X}，"
            f"该节点有{len(self.successors(node))}个后继节点"
        )
        return False

    def reduce_node_by_rule(self, node: CFGNode) -> bool:
        """检查给定的控制流图节点是否满足化简条件，如果可以则将其化简为结构化语句。

        函数的实现逻辑是：首先检查节点是否为循环头，如果是则尝试化简循环；否则尝试使用其他规则化简节点。
        每个规则化简函数名以`try_reduce_`开头，例如`try_reduce_sequence`。
        每个规则化简函数需要完成两方面操作：
        1. 判断节点是否满足化简条件，如果不满足则返回False。
        2. 如果满足则将节点化简为结构化语句，并返回True。
        当任意节点被化简时，函数会调用`emit_reduce_event`方法记录化简事件，并返回True。

        :param node: 待检查的控制流图节点
        :return: 如果节点被化简为结构化语句，则返回True，否则返回False
        """
        if self.is_loop_header(node) and not self.is_loop_header_under_analysis(node):
            self.enter_loop(node)
            self.completely_reduce_loop(node)
            self.leave_loop()
            return True

        if self.try_reduce_sequence(node):
            self.emit_reduce_event(ReduceRule.SEQUENCE, node)
            return True

        if self.try_reduce_while_true(node):
            self.emit_reduce_event(ReduceRule.WHILE_TRUE, node)
            return True

        if self.try_reduce_do_while(node):
            self.emit_reduce_event(ReduceRule.DO_WHILE, node)
            return True

        if self.try_reduce_if_else(node):
            self.emit_reduce_event(ReduceRule.IF_ELSE, node)
            return True

        if self.try_reduce_if(node, True) or self.try_reduce_if(node, False):
            self.emit_reduce_event(ReduceRule.IF, node)
            return True

        if self.try_reduce_if_break(node, True) or self.try_reduce_if_break(node, False):
            self.emit_reduce_event(ReduceRule.IF_BREAK, node)
            return True

        if self.try_reduce_if_continue(node, True) or self.try_reduce_if_continue(
            node, False
        ):
            self.emit_reduce_event(ReduceRule.IF_CONTINUE, node)
            return True

        return False

    def completely_reduce_loop(self, node: CFGNode):
        """完全化简以节点为循环头的循环，将循环内的节点化简为结构化语句。

        该方法首先尝试使用针对性规则化简循环；如果无法化简则使用goto规则将循环内的后继节点与节点合并，
        直到循环内只剩一个节点，从而可以将该节点转化为while(1)循环。

        注意：如果循环没有被化简，大概率是通用(goto)规则实现不完整。

        :param node: 循环头部节点
        """
        loop = self.get_loop_for(node)

        while not self.is_loop_reduced(loop) and self.reduce_cfg(node, by_rule=True):
            pass

        if not self.is_loop_reduced(loop):
            self.reduce_cfg(node, by_rule=False, loop=loop)
            self.cfg.add_edge(node, node)
            if self.try_reduce_while_true(node):
                self.emit_reduce_event(ReduceRule.WHILE_TRUE, node)

    # =====================================================================
    # 以下是具体的控制流图结构识别和化简方法
    #
    # 实现提示:
    # - 每个方法的核心操作是调用 self.reduce_node(node, body, new_succs, extend)
    # - extend=True: 将body追加到node已有指令后面，适用于顺序合并、if、goto等场景
    # - extend=False: 用body替换node的所有指令，适用于while/do-while（旧指令被包进循环体）
    # - new_succs: 化简后node的新后继节点列表，空列表表示删除所有出边
    # - 可参考已实现的 try_reduce_if_break 方法作为模板

    def try_reduce_goto_sequence(self, node: CFGNode) -> bool:
        """使用goto规则化简顺序结构。对于给定的节点，如果只有一个后继节点，则在给定节点后面添加goto语句，并删除后继节点。

        具体来说::

            识别如下结构
            node {stmt1}
            └── succ {stmt2}
            将其化简为
            node {stmt1; goto stmt2;}

        :param node: 待化简的控制流图节点
        :return: 如果节点被化简为结构化语句，则返回True，否则返回False
        """
        succs = self.successors(node)
        if len(succs) != 1:
            return False

        succ = succs[0]
        goto_stmt = self.gen_goto_stmt(succ)
        self.reduce_node(node, [goto_stmt], [], True)
        return True

    def try_reduce_goto_branch(self, node: CFGNode) -> bool:
        """使用goto规则化简if-else结构。对于给定的节点，如果有两个后继节点，则在节点后面添加if-goto-else-goto语句，并删除后继节点。

        具体来说::

            识别如下结构
            node {stmt1}
            ├── succ1 {stmt2}
            └── succ2 {stmt3}
            将其化简为
            node {stmt1; if(cond) goto stmt2; else goto stmt3;}

        :param node: 待化简的控制流图节点
        :return: 如果节点被化简为结构化语句，则返回True，否则返回False
        """
        succs = self.successors(node)
        if len(succs) != 2:
            return False

        succ1, succ2 = succs[0], succs[1]
        cond = self.get_cond_expr(node)
        goto_true = self.gen_goto_stmt(succ1)
        goto_false = self.gen_goto_stmt(succ2)
        if_stmt = self.gen_if_stmt(cond, [goto_true], [goto_false])
        self.reduce_node(node, [if_stmt], [], True)
        return True

    def try_reduce_goto_switch(self, node: CFGNode) -> bool:
        """使用goto规则化简switch结构。不要求实现"""
        return False

    def try_reduce_while_true(self, node: CFGNode) -> bool:
        """尝试将给定的节点化简为while(1)语句，避免使用goto

        具体来说::

            识别如下自循环结构
            node {stmt}
            └── node (自循环)
            将其化简为
            node {while(1) {stmt}}

        :param node: 待化简的控制流图节点
        :return: 如果节点被化简为结构化语句，则返回True，否则返回False
        """
        succs = self.successors(node)
        if len(succs) != 1:
            return False
        if succs[0] != node:
            return False

        while_stmt = self.gen_while_stmt(ConstExpr(1), node.insns)
        self.reduce_node(node, [while_stmt], [], False)
        return True

    def try_reduce_do_while(self, node: CFGNode) -> bool:
        """尝试将给定的节点化简为do-while语句，避免使用goto

        具体来说::

            识别如下结构
            node {stmt}
            ├── node (自循环)
            └── succ (循环后继节点)
            将其化简为
            node {do {stmt} while (cond)}
            └── succ

        :param node: 待化简的控制流图节点
        :return: 如果节点被化简为结构化语句，则返回True否则返回False
        """
        succs = self.successors(node)
        if len(succs) != 2:
            return False

        if succs[0] == node and succs[1] != node:
            exit_succ = succs[1]
        elif succs[1] == node and succs[0] != node:
            exit_succ = succs[0]
        else:
            return False
        cond = self.get_cond_expr(node)
        body_stmts = node.insns[:-1]
        do_while_stmt = self.gen_do_while_stmt(cond, body_stmts)
        self.reduce_node(node, [do_while_stmt], [exit_succ], False)
        return True

    def try_reduce_sequence(self, node: CFGNode) -> bool:
        """尝试将简单顺序结构化简为单个节点，避免使用goto

        具体来说::

            识别如下结构
            node {stmt1}
            └── succ {stmt2} (succ != node，即不是自循环)
                ...
                └── succ_succ_N (N >= 0)
            将其化简为
            node {stmt1; stmt2}
            ...
            └── succ_succ_N (N >= 0)

        :param node: 待化简的控制流图节点
        :return: 如果节点被化简为结构化语句，则返回True，否则返回False
        """
        succs = self.successors(node)
        if len(succs) != 1:
            return False

        succ = succs[0]
        if succ == node:
            return False

        new_succs = self.successors(succ)
        self.reduce_node(node, succ.insns, new_succs, True)
        return True

    def try_reduce_if(self, node: CFGNode, true_branch: bool) -> bool:
        """尝试将给定的节点化简为if结构，避免使用goto。
        当branch为True时，将node的第一个后继视为if_node，否则将另一个后继视为if_node

        具体来说::

            识别如下结构
            node {stmt}
            ├── if_node {stmt1}
            |     └── if_succ
            └── if_succ
            将其化简为
            node {stmt; if(cond) {stmt1}}
            └── if_succ

        :param node: 待化简的控制流图节点
        :param true_branch: 尝试化简为if结构的分支方向，为True时if语句的条件为`cond = get_cond_expr(node)`，
            否则条件为`cond = cond.logical_not()`
        :return: 如果节点被化简为结构化语句，则返回True，否则返回False
        """
        succs = self.successors(node)
        if len(succs) != 2:
            return False

        if_node = succs[0] if true_branch else succs[1]
        if_succ = succs[1] if true_branch else succs[0]

        if_node_succs = self.successors(if_node)
        if len(if_node_succs) != 1:
            return False
        if if_node_succs[0] != if_succ:
            return False

        cond = self.get_cond_expr(node)
        if not true_branch:
            cond = cond.logical_not()

        if_stmt = self.gen_if_stmt(cond, if_node.insns, None)
        self.reduce_node(node, [if_stmt], [if_succ], True)
        return True

    def try_reduce_if_continue(self, node: CFGNode, true_branch: bool) -> bool:
        """尝试将给定的节点化简为if-continue结构，避免使用goto

        具体来说::

            识别如下CFG结构
            node {stmt}
            ├── if_node
            |     └── node (跳转到循环头)
            └── if_succ
            将其化简为
            node {stmt; if(cond) continue;}
            └── if_succ

        :param node: 待化简的控制流图节点
        :param true_branch: 尝试化简为if-continue结构的分支方向，为True时if语句的条件为`cond = get_cond_expr(node)`，
            否则条件为`cond = cond.logical_not()`
        :return: 如果节点被化简为结构化语句，则返回True，否则返回False
        """
        loop = self.get_loop_for(node)
        if not loop:
            return False

        succs = self.successors(node)
        if len(succs) != 2:
            return False

        if_node = succs[0] if true_branch else succs[1]
        if_succ = succs[1] if true_branch else succs[0]
        if_node_succs = self.successors(if_node)
        if len(if_node_succs) != 1:
            return False
        if if_node_succs[0] != node:
            return False

        cond = self.get_cond_expr(node)
        if not true_branch:
            cond = cond.logical_not()

        continue_stmt = self.gen_continue_stmt(loop.header)
        if_stmt = self.gen_if_stmt(cond, [continue_stmt], None)
        self.reduce_node(node, [if_stmt], [if_succ], True)
        return True

    def try_reduce_if_break(self, node: CFGNode, true_branch: bool) -> bool:
        """尝试将给定的节点化简为if-break结构，避免使用goto

        具体来说::

            识别如下CFG结构
            node {stmt}
            ├── if_node
            |     └── exit (跳转到内层循环出口)
            └── if_succ
            将其化简为
            node {stmt; if(cond) break;}
            └── if_succ

        :param node: 待化简的控制流图节点
        :param true_branch: 尝试化简为if-break结构的分支方向，为True时if语句的条件为`cond = get_cond_expr(node)`，
            否则条件为`cond = cond.logical_not()`
        :return: 如果节点被化简为结构化语句，则返回True，否则返回False
        """
        loop = self.get_loop_for(node)
        if not loop:
            return False

        succs: list[CFGNode] = self.successors(node)
        if len(succs) != 2:
            return False

        if_node = succs[0] if true_branch else succs[1]
        if_succ = succs[1] if true_branch else succs[0]

        if not self.is_loop_succ(if_node, loop):
            return False

        cond = self.get_cond_expr(node)
        if not true_branch:
            cond = cond.logical_not()

        break_stmt = self.gen_break_stmt(loop.header)
        if_stmt = self.gen_if_stmt(cond, [break_stmt], None)
        self.reduce_node(node, [if_stmt], [if_succ], True)
        return True

    def try_reduce_if_else(self, node: CFGNode) -> bool:
        """尝试将给定的节点化简为if-else结构，避免使用goto

        具体来说::

            识别如下CFG结构
            node {stmt}
            ├── if_node {stmt1}
            |     └── if_succ
            └── else_node {stmt2}
                └── else_succ (if_succ == else_succ)
            将其化简为
            node {stmt; if(cond) {stmt1} else {stmt2};}
            └── if_succ

        :param node: 待化简的控制流图节点
        :return: 如果节点被化简为结构化语句，则返回True，否则返回False
        """
        succs = self.successors(node)
        if len(succs) != 2:
            return False

        if_node = succs[0]
        else_node = succs[1]
        if_succs = self.successors(if_node)
        else_succs = self.successors(else_node)
        if len(if_succs) != 1 or len(else_succs) != 1:
            return False
        if if_succs[0] != else_succs[0]:
            return False

        if_succ = if_succs[0]
        cond = self.get_cond_expr(node)
        if_stmt = self.gen_if_stmt(cond, if_node.insns, else_node.insns)
        self.reduce_node(node, [if_stmt], [if_succ], True)
        return True
