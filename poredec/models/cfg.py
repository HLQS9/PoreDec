from typing import Optional
import networkx as nx

from .insn import Insn
from .lift_mode import LiftMode


__all__ = ["CFGNode", "ControlFlowGraph"]


class CFGNode:
    """表示控制流图的节点，节点包含一个基本块的所有指令
    
    :ivar address: 节点地址
    :ivar insns: 节点包含的指令列表
    """

    address: int  # 节点地址
    insns: list[Insn]  # 汇编指令列表

    def __init__(self, address: int, insns: list[Insn]) -> None:
        self.address = address
        self.insns = list(insns)

    def append(self, insn: Insn):
        """在基本块末尾添加一条指令

        :param insn: 要添加的指令
        """
        if not self.insns:
            self.insns = []
        self.insns.append(insn)

    def extend(self, insns: list[Insn]):
        """在基本块末尾添加给定列表的指令

        :param insns: 要添加的指令列表
        """
        if not self.insns:
            self.insns = []
        self.insns.extend(insns)

    def reset(self, insns: list[Insn]):
        """设置基本块的指令列表

        :param insns: 要设置的指令列表
        """
        self.insns.clear()
        self.insns.extend(insns)

    def __hash__(self) -> int:
        return hash(self.address)

    def __eq__(self, o: object) -> bool:
        if not isinstance(o, CFGNode):
            return False
        return self.address == o.address and len(self.insns) == len(o.insns)

    def __repr__(self):
        return f"<CFGNode address={self.address:#X}>"

    def __str__(self) -> str:
        return repr(self)


class ControlFlowGraph(nx.DiGraph):
    """控制流图类，继承自networkx的DiGraph类
    控制流图的节点为基本块class:`CFGNode`，边表示控制流转移。

    :ivar entry: 控制流图的入口节点
    :ivar lift_mode: 控制流图的提升模式
    """

    def __init__(self, *args, **kwargs) -> None:
        super().__init__(*args, **kwargs)
        self.entry = None
        self.lift_mode = LiftMode.LOW

    def set_entry(self, entry: CFGNode):
        """设置控制流图的入口节点

        :param entry: 入口节点
        :type entry: class:`CFGNode`
        """
        self.entry = entry

    def get_node_by_addr(self, addr: int) -> Optional[CFGNode]:
        """获取首地址为addr的节点

        :param addr: 目标节点的地址
        :return: 当控制流图中包含首地址为addr的节点，则返回该节点，否则返回None
        """
        for node in self.nodes:
            if node.address == addr:
                return node
        return None

    def find_node_by_addr(self, addr: int) -> Optional[CFGNode]:
        """
        根据地址查找CFG中的节点，可以将地址映射到CFG中对应的基本块

        :param addr: 要查找的地址
        :return: 包含给定地址的节点，如果找不到则返回None
        """
        for node in self.nodes:
            node: CFGNode
            if node.address == addr:
                return node
            if (
                node.insns
                and node.insns[0].address <= addr
                and addr <= node.insns[-1].address
                and any(addr == insn.address for insn in node.insns)
            ):
                return node
        return None

    def __str__(self) -> str:
        s = ""
        for node in self.nodes:
            s += str(node) + "\n"
        return s

    def __repr__(self) -> str:
        return f"<ControlFlowGraph with {len(self.nodes)} nodes>"
