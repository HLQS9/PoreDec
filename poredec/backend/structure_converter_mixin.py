"""
实现结构化分析的基础框架和通用API。
"""

import os
import abc
import logging
import enum
from queue import Queue

import networkx as nx
from pypcode import OpCode

from ..models.cfg import CFGNode, ControlFlowGraph
from ..models.stmt import (
    Statement,
    IfStmt,
    GotoStmt,
    ContinueStmt,
    BreakStmt,
    WhileStmt,
    DoWhileStmt,
)
from ..models.expr import Expression, ConstExpr
from ..models.loop import LoopInfo, Loop
from ..models.reduce_event import ReduceRule, ReduceEvent
from ..utils.display import CFGDisplayer, CodeFormatter


__all__ = ["StructureConverterMixin"]


class StructureConverterMixin:
    """代码结构化分析基础类，实现了基础框架和通用API

    :param cfg: 待转换的控制流图
    :param loop_info: 循环信息
    :param dbg: 是否开启调试模式，开启时每次化简后都会打印控制流图
    """

    def __init__(
        self,
        cfg: ControlFlowGraph,
        loop_info: LoopInfo,
        intermediate_output_dir=None,
        log=None,
    ):
        assert cfg
        assert loop_info
        self.cfg = cfg

        if not log:
            self.log = logging.getLogger(self.__class__.__name__)
            self.log.addHandler(logging.StreamHandler())
            self.log.setLevel(logging.WARNING)
        else:
            self.log = log

        self.loop_info = loop_info
        self.intermediate_output_dir = intermediate_output_dir

        self._reduced_loops: set[Loop] = set()

        self._loop_headers_under_analysis: set[CFGNode] = set()
        self._loop_header_stack: list[CFGNode] = []

        # 跳转目标节点，及其对应的goto语句
        self._goto_targets: dict[CFGNode, list[GotoStmt]] = dict()

        # 存放不需要再调用convert_node进行化简的节点
        self._converted_nodes: set[CFGNode] = set()
        self._reduce_events = []

    def convert(self) -> ControlFlowGraph:
        """结构化控制流图，结构化后的控制流图应该只包含一个节点，该节点中包含所有结构化语句。

        :return: 结构化后的控制流图。
        """
        cfg = self.cfg

        self.convert_node(cfg.entry)

        while self.convert_goto_targets():
            pass

        self.merge_goto_targets()

        self.replace_break_continue_outside_loop()

        return cfg

    def convert_node(self, node: CFGNode) -> bool:
        """完全化简一个节点，化简后该节点不包含后继节点
        :return: 如果节点被化简为结构化语句，则返回True
        """
        # 使用针对性的规则化简控制流图
        if not self.successors(node):
            return False

        any_reduced = False
        while self.successors(node) and self.reduce_cfg(node, by_rule=True):
            any_reduced = True

        # 使用goto规则完全结构化控制流图
        loop = self.get_loop_for(node)
        any_reduced |= self.reduce_cfg(node, by_rule=False, loop=loop)

        self._converted_nodes.add(node)
        return any_reduced

    @abc.abstractmethod
    def reduce_cfg(self, node, by_rule, loop=None) -> bool:
        """递归化简控制流图，尝试将多个节点化简为一个节点。

        函数会使用广度优先搜索遍历控制流图中从给定节点可达的所有节点，并在尝试化简这些节点——将节点与其后继节点合并。

        :param node: 待化简的节点
        :param by_rule: 为True时使用针对性规则化简，否则使用通用(goto)规则
        :param loop: 当给定loop时，只化简循环内的节点，否则化简所有node可达的节点。
        :return: 如果节点被化简为结构化语句，则返回True
        """

    def convert_goto_targets(self):
        """化简所有未完全化简的goto目标节点。该方法可能需要多次调用，因为化简一个goto目标节点可能会使其它节点变得可化简。

        :return: 如果有节点被化简，则返回True
        """
        # 所有未被化简的goto目标节点
        unconverted_goto_targets = [
            goto_target
            for goto_target in self._goto_targets
            if self.successors(goto_target) and goto_target not in self._converted_nodes
        ]
        if not unconverted_goto_targets:
            return False

        any_reduced = False
        for goto_target in unconverted_goto_targets:
            any_reduced |= self.convert_node(goto_target)
        return any_reduced

    def clean_reduced_dangling_nodes(self):
        """清理控制流图中由于针对性规则化简产生的孤立节点"""
        cfg = self.cfg
        for node in list(cfg.nodes):
            if node == cfg.entry:
                continue
            if not self.predecessors(node) and node not in self._goto_targets:
                self.log.debug("删除化简的孤立节点: %#X", node.address)
                self.cfg.remove_node(node)

    def replace_break_continue_outside_loop(self):
        """将循环外的break和continue替换为goto语句"""
        cfg = self.cfg
        queue = Queue()
        for node in list(cfg.nodes):
            queue.put((None, node.insns))
        # 遍历控制流图，找到所有可能可以替换的goto语句的位置
        while not queue.empty():
            loop_stmt, insns = queue.get()
            for idx, stmt in enumerate(insns):
                if isinstance(stmt, ContinueStmt) or isinstance(stmt, BreakStmt):
                    if not loop_stmt:
                        insns[idx] = GotoStmt(stmt.target)
                elif isinstance(stmt, IfStmt):
                    queue.put((loop_stmt, stmt.true_body))
                    if stmt.false_body:
                        queue.put((loop_stmt, stmt.false_body))
                elif isinstance(stmt, WhileStmt) or isinstance(stmt, DoWhileStmt):
                    queue.put((stmt, stmt.body))

    def merge_goto_targets(self):
        """尝试将goto语句替换为目标代码块，如果不能替换，则将目标代码块添加到CFG入口节点"""
        cfg = self.cfg

        goto_stmt_target_map = {}
        for goto_target, goto_stmts in self._goto_targets.items():
            if len(goto_stmts) != 1:
                continue
            for goto_stmt in goto_stmts:
                goto_stmt_target_map[goto_stmt] = goto_target

        graph = nx.DiGraph()
        queue = Queue()
        for node in list(cfg.nodes):
            queue.put((node, node.insns))
        # 遍历控制流图，找到所有可能可以替换的goto语句的位置
        while not queue.empty():
            node, insns = queue.get()
            for idx, stmt in enumerate(insns):
                if isinstance(stmt, GotoStmt):
                    if stmt not in goto_stmt_target_map:
                        continue
                    goto_target = goto_stmt_target_map.get(stmt)
                    if not graph.has_edge(node, goto_target):
                        graph.add_edge(node, goto_target, tasks=[])
                    graph.get_edge_data(node, goto_target)["tasks"].append((insns, idx))
                elif isinstance(stmt, IfStmt):
                    queue.put((node, stmt.true_body))
                    if stmt.false_body:
                        queue.put((node, stmt.false_body))
                elif isinstance(stmt, WhileStmt) or isinstance(stmt, DoWhileStmt):
                    queue.put((node, stmt.body))

        # 删除循环goto
        no_merge_nodes = set()
        for cycle in nx.simple_cycles(graph):
            no_merge_nodes.update(cycle)
        graph.remove_nodes_from(no_merge_nodes)

        remaining_goto_targets = set(self._goto_targets.keys())
        for node in reversed(list(nx.topological_sort(graph))):
            goto_targets = list(graph.successors(node))
            if not goto_targets:
                continue
            for goto_target in goto_targets:
                tasks = graph.get_edge_data(node, goto_target)["tasks"]
                base_idx = 0
                for insns, idx in tasks:
                    pos = base_idx + idx
                    self.log.debug(
                        "替换goto语句: %#X[pos:%d,size:%d] -> %#X[size:%d]",
                        node.address,
                        pos,
                        len(insns),
                        goto_target.address,
                        len(goto_target.insns),
                    )
                    insns[pos : pos + 1] = goto_target.insns
                    base_idx += len(goto_target.insns) - 1
                    remaining_goto_targets.discard(goto_target)

        for goto_target in sorted(remaining_goto_targets, key=lambda x: x.address):
            self.log.debug("添加未合并的goto_target: %#X", goto_target.address)
            cfg.entry.extend(goto_target.insns)

        for goto_target in self._goto_targets:
            if goto_target in cfg:
                cfg.remove_node(goto_target)

    def reduce_node(
        self,
        node: CFGNode,
        body: list[Statement],
        new_succs: list[CFGNode],
        extend: bool,
    ):
        """化简给定的CFG节点，将node中的指令替换为body中的指令，并将node的后继节点替换为succs中的节点

        :param node: 待化简的节点
        :param body: 待添加的指令序列
        :param new_succs: 新的后继节点
        :param extend: True表示将body中的指令追加到node中，否则替换node中的指令

        :example:

        >>> self.reduce_node(node, [stmt], new_succs=[succ1, succ2], extend=True)
        >>> # 上述代码将node中的指令替换为`node.insns + [stmt]`，并将node的后继节点替换为succ1和succ2
        >>> self.reduce_node(node, [stmt], new_succs=[], extend=False)
        >>> # 上述代码将node中的指令替换为`[stmt]`，并标记node没有后继节点
        """
        body = list(body)
        if extend:
            node.extend(body)
        else:
            node.reset(body)

        # 保留后继顺序（条件分支依赖T/F顺序），不能使用set打乱顺序。
        ordered_new_succs = []
        seen = set()
        for succ in new_succs:
            if succ in seen:
                continue
            seen.add(succ)
            ordered_new_succs.append(succ)

        old_succs = self.successors(node)
        old_succ_set = set(old_succs)
        new_succ_set = set(ordered_new_succs)
        succs_to_remove = [succ for succ in old_succs if succ not in new_succ_set]
        succs_to_add = [succ for succ in ordered_new_succs if succ not in old_succ_set]

        self.cfg.remove_edges_from([(node, succ) for succ in succs_to_remove])
        is_cbranch = False
        if node.insns:
            insn = node.insns[-1]
            is_cbranch = (
                hasattr(insn, "opcode")
                and insn.opcode == OpCode.CBRANCH
                and len(ordered_new_succs) == 2
            )

        branch_labels = {}
        if is_cbranch:
            branch_labels = {
                ordered_new_succs[0]: "T",
                ordered_new_succs[1]: "F",
            }

        for succ in succs_to_add:
            if is_cbranch:
                self.cfg.add_edge(node, succ, label=branch_labels[succ])
            else:
                self.cfg.add_edge(node, succ)

        # 对仍保留的条件分支边，也刷新标签以保持语义一致。
        if is_cbranch:
            for succ in ordered_new_succs:
                if self.cfg.has_edge(node, succ):
                    self.cfg[node][succ]["label"] = branch_labels[succ]

        self.log.debug(f"HACK-change: {[hex(item.address) for item in self.successors(node)]}")

        # 仅当节点被真正化简成循环语句时，才将其所属循环标记为已化简。
        # 若在IF_BREAK/SEQUENCE等中间步骤就提前标记，会导致循环化简流程被过早终止。
        reduced_to_loop_stmt = (
            (not extend)
            and len(body) == 1
            and isinstance(body[0], (WhileStmt, DoWhileStmt))
        )
        if reduced_to_loop_stmt:
            loop = self.get_loop_for(node)
            while loop:
                if loop.header == node or loop.back_edge[1] == node:
                    self._reduced_loops.add(loop)
                    break
                loop = loop.parent
        self.clean_reduced_dangling_nodes()

    # =========================================================================
    # 以下方法用于访问CFG
    # =========================================================================
    def successors(self, node: CFGNode) -> list[CFGNode]:
        """获取给定节点的后继节点

        :example:
        

        >>> succs = successors(node)
        >>> for succ in succs: pass # ...处理后继节点
        >>> succ_num = len(succs) # 获取后继节点的数量
        """
        succs = list(self.cfg.successors(node))
        if len(succs) <= 1:
            return succs

        indexed_succs = list(enumerate(succs))

        def sort_key(item: tuple[int, CFGNode]):
            idx, succ = item
            edge_data = self.cfg.get_edge_data(node, succ) or {}
            label = edge_data.get("label")
            priority = 0 if label == "T" else 1 if label == "F" else 2
            return priority, idx

        indexed_succs.sort(key=sort_key)
        return [succ for _, succ in indexed_succs]

    def predecessors(self, node: CFGNode) -> list[CFGNode]:
        """获取给定节点的前驱节点

        :example:

        >>> preds = predecessors(node)
        >>> for pred in preds: pass # ...处理前驱节点
        >>> pred_num = len(preds) # 获取前驱节点的数量
        """
        return list(self.cfg.predecessors(node))

    # =========================================================================
    # 以下方法用于循环分析
    # =========================================================================

    def get_loop_for(self, node: CFGNode) -> Loop:
        """获取给定节点所在的循环，如果该循环在结构化过程中被化简，则返回其父循环；如果没有找到循环，则返回None"""
        loop = self.loop_info.get_loop_for(node)
        while loop and loop in self._reduced_loops:
            loop = loop.parent

        return loop

    def get_loop_succs(self, node: CFGNode) -> list[CFGNode]:
        """获取给定节点的循环后继节点"""
        loop = self.get_loop_for(node)
        if loop:
            return loop.get_successors(self.cfg)
        return []

    def is_goto_target(self, node: CFGNode) -> bool:
        """检查节点当前是否仍是goto目标。"""
        return bool(self._goto_targets.get(node))

    def is_loop_header(self, node: CFGNode, loop: Loop = None) -> bool:
        """检查给定的节点是否是循环的头部

        :param node: 待检查的节点
        :param loop: 待检查的循环，如果给定该参数，则只判断节点是否是该循环的头部
        :return: 如果是循环的头部，且该循环没有在结构化过程中被化简，则返回True，否则返回False
        """
        if loop:
            return loop.header == node

        loop = self.loop_info.get_loop_for(node, is_header=True)
        if loop and loop not in self._reduced_loops:
            return True

        return False

    def is_loop_succ(self, node: CFGNode, loop: Loop) -> bool:
        """检查给定的节点是否是循环的后继节点

        :param node: 待检查的节点
        :param loop: 待检查的循环
        :return: 如果是循环的后继节点，且该循环没有在结构化过程中被化简，则返回True，否则返回False
        """
        return loop not in self._reduced_loops and node in loop.get_successors(self.cfg)

    def enter_loop(self, node: CFGNode):
        """标志进入循环，此时调用 meth:`is_loop_header_under_analysis` 返回True

        :param node: 循环的头部
        """
        self._loop_header_stack.append(node)
        self._loop_headers_under_analysis.add(node)
        self.emit_reduce_event(ReduceRule.ENTER_LOOP, node)

    def leave_loop(self):
        """标志离开循环，此时调用 meth:`is_loop_header_under_analysis` 返回False"""
        node = self._loop_header_stack.pop()
        self._loop_headers_under_analysis.remove(node)
        self.emit_reduce_event(ReduceRule.LEAVE_LOOP, node)

    def is_loop_header_under_analysis(self, node: CFGNode) -> bool:
        """检查给定的节点是否是正在分析的循环的头部

        :param node: 待检查的节点
        :return: 如果是循环的头部，则返回True
        """
        return node in self._loop_headers_under_analysis

    def is_loop_reduced(self, loop: Loop) -> bool:
        """检查给定的节点是否在结构化过程中被化简"""
        return loop in self._reduced_loops

    def is_back_edge(self, u: CFGNode, v: CFGNode) -> bool:
        """判断u->v是否是循环的回边"""
        for loop in self.loop_info.loops:
            if loop.back_edge == (u, v):
                return True
        return False

    # =========================================================================
    # 以下方法用于生成结构化代码语句
    # =========================================================================

    def get_cond_expr(self, node: CFGNode) -> Expression:
        """获取给定节点True Branch的条件表达式

        :param node: 节点不能已经被化简，即不能已经作为 meth:`reduce_node` 的调用参数
        :return: 条件表达式
        """
        insn = node.insns[-1]
        assert hasattr(insn, "opcode")
        if insn.opcode != OpCode.CBRANCH:
            return ConstExpr(1)
        return insn.inputs[1]

    def gen_continue_stmt(self, target_node: CFGNode) -> ContinueStmt:
        """生成continue语句
        :param target_node: continue跳转到的目标节点
        :return: continue语句
        """
        stmt = ContinueStmt(target_node.address)
        return stmt

    def gen_break_stmt(self, target_node: CFGNode) -> BreakStmt:
        """生成break语句
        :param target_node: break跳转到的目标节点
        :return: break语句
        """
        stmt = BreakStmt(target_node.address)
        return stmt

    def gen_goto_stmt(self, target_node: CFGNode) -> GotoStmt:
        """生成跳转到目标代码块的指令序列

        :param target_node: 目标节点
        :return: 跳转到目标代码块的指令序列，包括goto指令
        """

        insns = target_node.insns
        assert insns, "目标代码块不能为空"

        goto_stmt = GotoStmt(target_node.address)

        stmt = insns[0]
        assert isinstance(stmt, Statement)
        stmt.label = goto_stmt.target_label

        self._goto_targets.setdefault(target_node, []).append(goto_stmt)
        return goto_stmt

    def gen_if_stmt(
        self,
        cond: Expression,
        true_body: list[Statement],
        false_body: list[Statement],
    ) -> IfStmt:
        """生成if-else语句的指令序列，true_body和false_body不能同时为空，否则会抛出ValueError。
        若true_body为空，则会将条件取反。

        :param cond: 条件表达式
        :param true_body: 条件为真时的指令序列
        :param false_body: 条件为假时的指令序列
        :return: if-else语句的指令序列
        """
        true_body = list(true_body)
        false_body = list(false_body) if false_body else None
        if not true_body and not false_body:
            raise ValueError("true_body和false_body不能同时为空")
        if not true_body:
            cond = cond.logical_not()
            true_body, false_body = false_body, true_body

        return IfStmt(cond, true_body, false_body)

    def gen_while_stmt(self, cond: Expression, body: list[Statement]) -> WhileStmt:
        """生成while语句

        :param cond: 循环条件
        :param body: 循环体
        :return: while语句
        """
        return WhileStmt(cond, list(body))

    def gen_do_while_stmt(self, cond: Expression, body: list[Statement]) -> DoWhileStmt:
        """生成do-while语句

        :param cond: 循环条件
        :param body: 循环体
        :return: do-while语句
        """
        return DoWhileStmt(cond, list(body))

    def get_reduce_events(self) -> list["ReduceEvent"]:
        """获取化简事件"""
        return list(self._reduce_events)

    def emit_reduce_event(self, rule: "ReduceRule", node: CFGNode):
        """添加化简事件"""
        event = ReduceEvent(rule, node)
        self._reduce_events.append(event)

        self.log.debug(f"[{len(self._reduce_events)}] 化简: {str(event)}")
        output_dir = self.intermediate_output_dir
        if output_dir and rule != ReduceRule.NONE:
            os.makedirs(output_dir, exist_ok=True)
            idx = len(self._reduce_events)  # 从1开始
            out_path = f"{output_dir}/{idx}-{event}.png"
            CFGDisplayer(CodeFormatter().configure(simplify=True)).draw_cfg(
                self.cfg, out_path, highlights=[node.address]
            )

    def bfs_traverse_loop(self, node: CFGNode, inspect_func, loop: Loop):
        """广度优先遍历循环体，对每个节点调用inspect_func。
        :param node: 遍历的起始节点
        :param inspect_func: 检查函数，接受一个CFGNode参数，返回一个bool值
        :param loop: 循环体

        :return: 如果有节点被检查，则返回True
        """
        return self.bfs_traverse(node, inspect_func, loop.body)

    def bfs_traverse(
        self, node: CFGNode, operate_func, white_list: set[CFGNode] = None
    ):
        """
        广度优先遍历控制流图，对每个节点调用inspect_func。
        :param node: 遍历的起始节点
        :param operate_func: 检查函数，接受一个CFGNode参数，返回一个bool值
        """
        queue: Queue[CFGNode] = Queue()
        queue.put(node)
        visited = {node}

        any_true = False

        while not queue.empty():
            curr_node = queue.get()
            if curr_node not in self.cfg:
                continue

            # inspect_func可以改变节点的后继节点
            if operate_func(curr_node):
                any_true = True

            if curr_node not in self.cfg:
                continue

            for succ in self.successors(curr_node):
                if succ in visited or self.is_back_edge(node, succ):
                    continue
                if white_list and succ not in white_list:
                    continue
                visited.add(succ)
                queue.put(succ)

        return any_true
