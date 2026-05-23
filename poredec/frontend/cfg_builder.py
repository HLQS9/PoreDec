"""
控制流图构建器
"""
# pylint: disable=pointless-string-statement
# pylint: disable=unused-argument
# pylint: disable=fixme

from ..models.insn import DisasInsn
from ..models.cfg import CFGNode, ControlFlowGraph
from .lifter import Lifter


__all__ = ["CFGBuilder"]


class CFGBuilder:
    """控制流图构建器"""

    def __init__(self, lifter: Lifter):
        self.lifter = lifter  # 反汇编器

    def build_cfg(self, entry_addr: int) -> ControlFlowGraph:
        """从给定的函数起始地址开始，构建完整的函数控制流图。
        控制流图的节点为基本块class:`CFGNode`，边表示控制流转移。
        每个节点包含一到多条汇编指令class:`DisasInsn`。

        :param entry_addr: 函数的起始地址
        :return: 构建完成的控制流图
        """
        # 创建一个空的控制流图
        cfg = ControlFlowGraph()

        """
        步骤1: 从入口地址开始反汇编，依次获取所有指令
        下面代码演示了如何在给定地址(addr)处反汇编一条指令
        >>> insn = self.lifter.disassemble_at(addr)
        insn中包含了反汇编得到的指令信息，例如insn.succs表示该指令后继指令地址列表。更多信息见class:`DisasInsn`
        """
        insns: dict[int, DisasInsn] = {}  # addr -> 反汇编指令
        # TODO: 实现步骤1
        worklist = [entry_addr]
        while worklist:
            addr = worklist.pop()
            if addr in insns:
                continue

            insn = self.lifter.disassemble_at(addr)
            if insn is None:
                continue

            insns[addr] = insn

            for succ_addr in insn.succs:
                if succ_addr not in insns:
                    worklist.append(succ_addr)

        if not insns:
            return cfg

        """
        步骤2: 识别基本块的起始指令和终止指令。
        起始指令：有>1或0条前继指令，或前继指令中包含终止指令
        终止指令：有>1或0条后继指令，或后继指令中包含起始指令

        提示：起始指令和终止指令的定义存在循环依赖（起始依赖终止，终止依赖起始），
        可以使用迭代算法：重复扫描所有指令，直到不再产生新的起始/终止指令为止。
        """
        # TODO: 实现步骤2
        pred_counts: dict[int, int] = {addr: 0 for addr in insns}
        for addr, insn in insns.items():
            for succ_addr in insn.succs:
                if succ_addr in pred_counts:
                    pred_counts[succ_addr] += 1

        leaders: set[int] = set()     
        terminators: set[int] = set()  

        leaders.add(entry_addr)
        for addr, insn in insns.items():
            if insn.is_jump or insn.is_ret:
                terminators.add(addr)
        changed = True
        while changed:
            changed = False
            for addr in insns:
                if addr in leaders:
                    continue
                pred_count = pred_counts.get(addr, 0)
                if pred_count != 1:
                    leaders.add(addr)
                    changed = True
                else:
                    for other_addr, other_insn in insns.items():
                        if addr in other_insn.succs:
                            if other_addr in terminators:
                                leaders.add(addr)
                                changed = True
                            break
            for addr, insn in insns.items():
                if addr in terminators:
                    continue
                succ_count = len(insn.succs)
                if succ_count != 1:
                    terminators.add(addr)
                    changed = True
                else:
                    if insn.succs[0] in leaders:
                        terminators.add(addr)
                        changed = True

        """
        步骤3: 构造基本块, 基本块包含从起始指令到下一条终止指令间的所有指令。
        下面代码演示了如何创建一个基本块, node_insns为基本块中的所有指令
        >>> node_addr = node_insns[0].address # 获取基本块的起始地址
        >>> node = CFGNode(node_addr, node_insns) # 创建基本块
        创建的基本块可以通过下面代码添加到控制流图中
        >>> cfg.add_node(node)
        """
        # TODO: 实现步骤3
        sorted_leaders = sorted(leaders)
        blocks: dict[int, CFGNode] = {}  # leader_addr -> CFGNode

        for i, leader_addr in enumerate(sorted_leaders):
            block_insns: list[DisasInsn] = []
            curr_addr = leader_addr
            next_leader = (
                sorted_leaders[i + 1] if i + 1 < len(sorted_leaders) else None
            )

            while curr_addr in insns:
                block_insns.append(insns[curr_addr])
                if curr_addr in terminators:
                    break
                next_addr = curr_addr + insns[curr_addr].size
                if next_leader is not None and next_addr >= next_leader:
                    break
                if next_addr not in insns:
                    break

                curr_addr = next_addr

            if block_insns:
                node = CFGNode(leader_addr, block_insns)
                blocks[leader_addr] = node
                cfg.add_node(node)

        # entry_node = CFGNode(entry_addr, insns)  # 本行代码仅用于演示

        """
        步骤4: 根据控制流连接基本块
        下面代码演示了如何添加控制流图的边
        >>> cfg.add_edge(u, v) # 添加一条从u到v的边
        >>> cfg.add_edge(u, v, label="T") # 可以指定边的标签，标签会在画图时显示

        提示：对于条件跳转指令(is_cond为True)，succs[0]为跳转目标地址(True分支)，
        succs[1]为顺序执行地址(False分支)。建议分别用label="T"和label="F"标记边。
        """
        # TODO: 实现步骤4
        for leader_addr, node in blocks.items():
            last_insn = node.insns[-1]

            for succ_addr in last_insn.succs:
                target_node = blocks.get(succ_addr)
                if target_node is None:
                    continue
                label = None
                if last_insn.is_cond and len(last_insn.succs) == 2:
                    if succ_addr == last_insn.succs[0]:
                        label = "T"
                    elif succ_addr == last_insn.succs[1]:
                        label = "F"

                cfg.add_edge(node, target_node, label=label)

        """
        步骤5: 设置控制流图的入口节点
        """
        # TODO: 实现步骤5: 只需要调用cfg.set_entry方法设置控制流图的入口节点
        if entry_addr in blocks:
            cfg.set_entry(blocks[entry_addr])

        # cfg.set_entry(entry_node)  # 本行代码仅用于演示

        assert cfg.nodes, "控制流图中没有节点"
        assert cfg.entry, "需要设置控制流图的入口节点"
        return cfg
