"""
循环数据结构
"""

from functools import cached_property
from typing import Optional

from .cfg import CFGNode, ControlFlowGraph


__all__ = ["Loop", "LoopInfo"]


class Loop:
    """表示单个循环

    :ivar header: 循环头
    :ivar body: 循环体，包含所有循环内的节点
    :ivar back_edge: 循环回边，由循环体中的某一节点指向循环头
    :ivar parent: 上一层父循环，如果循环A完全包含循环B的循环体，则A是B的parent(父循环)
    """

    def __init__(
        self, header: CFGNode, body: set[CFGNode], back_edge: tuple[CFGNode, CFGNode]
    ):
        assert header == back_edge[1], f"header: {header}, back_edge[1]: {back_edge[1]}"
        self._header = header
        self._body = body
        self._back_edge = back_edge
        self.parent: Optional[Loop] = None

    @cached_property
    def depth(self):
        """循环的深度，即嵌套层数，从1开始计数"""
        depth = 0
        curr_loop = self
        while curr_loop:
            depth += 1
            curr_loop = curr_loop.parent
        return depth

    @property
    def header(self):
        return self._header

    @property
    def body(self):
        return self._body

    @property
    def back_edge(self):
        return self._back_edge

    def get_predecessors(self, cfg: ControlFlowGraph) -> set[CFGNode]:
        preds = set()
        for node in self.body:
            if node not in cfg:
                continue
            for pred in cfg.predecessors(node):
                if pred not in self.body:
                    preds.add(pred)
        return preds

    def get_successors(self, cfg: ControlFlowGraph) -> set[CFGNode]:
        succs = set()
        for node in self.body:
            if node not in cfg:
                continue
            for succ in cfg.successors(node):
                if succ not in self.body:
                    succs.add(succ)
        return succs

    def __str__(self):
        u, v = self.back_edge
        return f"Loop(back_edge:{u.address:#X}->{v.address:#X})"

    def __repr__(self):
        return str(self)

    def __hash__(self):
        return hash(self.back_edge)

    def __eq__(self, other):
        return isinstance(other, Loop) and self.back_edge == other.back_edge


class LoopInfo:
    """控制流图中的循环信息

    :ivar loops: CFG中的所有循环
    """

    def __init__(
        self,
        scc_with_headers: list[tuple[CFGNode, set[CFGNode]]],
        back_edges: list[tuple[CFGNode, CFGNode]],
        loops: list[Loop],
    ):
        self.sccs = {header: body for header, body in scc_with_headers}
        self.back_edges = back_edges
        # 把内层循环放在前面
        self.loops = sorted(loops, key=lambda loop: loop.depth, reverse=True)

    def get_loop_for(self, node: CFGNode, is_header=False):
        """获取节点所在的最内层循环，如果节点不在任何循环内，则返回None"""
        if is_header:
            for loop in self.loops:
                if loop.header == node:
                    return loop
        else:
            for loop in self.loops:
                if node in loop.body:
                    return loop

        return None

    def get_scc_for(self, node: CFGNode):
        """获取节点所在的强连通分量"""
        for scc in self.sccs.values():
            if node in scc:
                return scc

    def get_scc_header_for(self, node: CFGNode):
        """获取节点所在的强连通分量的头"""
        for header, body in self.sccs.items():
            if node in body:
                return header

    def is_loop_header(self, node: CFGNode):
        """判断节点是否是循环头"""
        for back_edge in self.back_edges:
            if back_edge[1] == node:
                return True
        return False

    def is_back_edge(self, edge: tuple[CFGNode, CFGNode]):
        """判断边是否是回边
        :param edge: (源节点, 目标节点)
        """
        return edge in self.back_edges
