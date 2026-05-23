"""
分析识别循环
"""

import networkx as nx

from ..models.cfg import ControlFlowGraph
from ..models.loop import Loop, LoopInfo


class LoopAnalyzer:
    """循环分析器"""

    @classmethod
    def analyze_loop(cls, cfg: ControlFlowGraph) -> LoopInfo:
        """分析控制流图，获得控制流图中的循环信息

        函数使用Tarjan算法识别强连通分量，进而通过环路分析识别单个循环，最后根据循环体的嵌套关系识别嵌套循环。

        :param cfg: 控制流图
        :return: 循环信息
        """
        # Tarjan算法
        # 输入: cfg
        # 输出: scc_with_headers, back_edges
        scc_with_headers = []
        back_edges = []

        preorder = {}
        lowlink = {}
        scc_found = set()
        scc_queue = []
        i = 0  # Preorder counter
        neighbors = {v: iter(cfg[v]) for v in cfg}
        start_nodes = [cfg.entry] if cfg.entry else cfg.nodes
        for source in start_nodes:
            if source not in scc_found:
                queue = [source]
                while queue:
                    v = queue[-1]
                    if v not in preorder:
                        i = i + 1
                        preorder[v] = i
                    done = True
                    for w in neighbors[v]:
                        if w not in preorder:
                            queue.append(w)
                            done = False
                            break
                    if done:
                        lowlink[v] = preorder[v]
                        for w in cfg[v]:
                            if w not in scc_found:
                                if preorder[w] > preorder[v]:
                                    lowlink[v] = min([lowlink[v], lowlink[w]])
                                else:
                                    # 检测到回边
                                    lowlink[v] = min([lowlink[v], preorder[w]])
                                    # w in queue表示w在当前DFS树上，否则可能是横叉边
                                    if preorder[w] <= lowlink[v] and w in queue:
                                        back_edges.append((v, w))
                        queue.pop()
                        if lowlink[v] == preorder[v]:
                            scc = {v}
                            while scc_queue and preorder[scc_queue[-1]] > preorder[v]:
                                k = scc_queue.pop()
                                scc.add(k)
                            scc_found.update(scc)
                            scc_with_headers.append((v, scc))
                        else:
                            scc_queue.append(v)

        # 识别循环
        # 输入: cfg, scc_with_headers, back_edges
        # 输出: loops
        # 每个强连通分量本身是一个循环，但内部可能包含多个循环，如嵌套循环
        # 在反编译的过程中，我们需要将嵌套循环分离开。但准确识别嵌套循环是NP难的，
        # 这里采用启发式规则来分离嵌套循环。
        scc_cycles = []
        for _, body in scc_with_headers:
            subgraph = cfg.subgraph(body)
            cycles = list(nx.simple_cycles(subgraph))
            scc_cycles.append(cycles)

        loops: list[Loop] = []
        for back_edge in back_edges:
            u, v = back_edge
            for scc_idx, (_, body) in enumerate(scc_with_headers):
                if u in body and v in body:
                    break
            else:
                raise RuntimeError(
                    f"回边({u.address:#X}, {v.address:#X})不在任何强连通分量内"
                )
            cycles = scc_cycles[scc_idx]
            loop_body = set()
            for cycle in cycles:
                if (
                    u in cycle
                    and v in cycle
                    and (cycle.index(u) + 1) % len(cycle) == cycle.index(v)
                ):
                    loop_body.update(cycle)

            loop = Loop(v, loop_body, back_edge=(u, v))
            loops.append(loop)

        # 识别嵌套循环的父子关系
        loops.sort(key=lambda loop: len(loop.body))
        for ci, loop_c in enumerate(loops):
            for pi, loop_p in enumerate(loops):
                if pi == ci:
                    continue
                p_body = loop_p.body
                c_body = loop_c.body
                if c_body.issubset(p_body) and not c_body.issuperset(p_body):
                    # loops[pi]是loops[ci]的父循环
                    loop_c.parent = loop_p
                    break

        return LoopInfo(scc_with_headers, back_edges, loops)
