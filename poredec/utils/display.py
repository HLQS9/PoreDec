import networkx as nx
from pypcode import PcodeOp, PcodePrettyPrinter, OpCode

try:
    from pygraphviz import AGraph
except ImportError:
    print("错误: 由于缺乏pygraphviz库不能保存CFG。请按照实验文档正确设置运行环境。")

from ..models.cfg import CFGNode, ControlFlowGraph
from ..models.expr import Expression, VarExpr
from ..models.insn import Insn
from ..models.stmt import (
    Statement,
    PcodeStmt,
    GotoStmt,
    ContinueStmt,
    BreakStmt,
    IfStmt,
    SwitchStmt,
    WhileStmt,
    DoWhileStmt,
)
from ..models.lift_mode import LiftMode


__all__ = ["CodeFormatter", "CFGDisplayer"]


class CodeFormatter:
    """代码格式化工具，用于将指令、语句转化为文本"""

    INDENT = "  "

    PPP = PcodePrettyPrinter()
    _no_pcode = False
    _simplify = False

    def __init__(self):
        self._no_pcode = False
        self._simplify = False

    def configure(self, no_pcode=False, simplify=False):
        """全局配置
        :param no_pcode: 是否不显示Pcode, 开启后格式化PcodeStmt时仅打印代码注释, 默认为False
        :param simplify: 是否简化反编译结果，开启后仅保留控制流结构, 默认为False
        """
        self._no_pcode = no_pcode
        self._simplify = simplify
        return self

    def fmt_insns(self, address: int, insns: list[Insn]):
        """格式化指令列表"""
        for insn in insns:
            if not isinstance(insn, Insn):
                raise TypeError(f"错误: 预期Insn列表, 实际包含非指令对象 {type(insn)}")

        text = f"{address:#08X}:\n"
        for insn in insns:
            text += f"{self.INDENT}{insn}\n"
        return text

    def fmt_stmts(self, stmts: list[Statement], lspace=INDENT):
        """格式化语句列表"""
        for stmt in stmts:
            if not isinstance(stmt, Statement):
                raise TypeError(
                    f"错误: 预期Statement列表, 实际包含非指令对象 {type(stmt)}"
                )

        text = ""
        last_idx = len(stmts) - 1
        for i, stmt in enumerate(stmts):
            if stmt.label:
                text += stmt.label + ":\n"

            if isinstance(stmt, PcodeStmt):
                if self._simplify:
                    stmt_text = ""
                    if i == 0 or not isinstance(stmts[i - 1], PcodeStmt):
                        stmt_text = f"{lspace}// 首指令地址: {stmt.address:#X}"
                    if i == last_idx or not isinstance(stmts[i + 1], PcodeStmt):
                        if stmt_text:
                            stmt_text += "\n"
                        stmt_text += f"{lspace}// 末指令地址: {stmt.address:#X}"
                else:
                    stmt_text = self._fmt_pcode_stmt(stmt, lspace)
            elif isinstance(stmt, ContinueStmt):
                stmt_text = self._fmt_continue_stmt(stmt, lspace)
            elif isinstance(stmt, BreakStmt):
                stmt_text = self._fmt_break_stmt(stmt, lspace)
            elif isinstance(stmt, GotoStmt):
                stmt_text = self._fmt_goto_stmt(stmt, lspace)
            elif isinstance(stmt, IfStmt):
                stmt_text = self._fmt_if_stmt(stmt, lspace)
            elif isinstance(stmt, SwitchStmt):
                stmt_text = self._fmt_switch_stmt(stmt, lspace)
            elif isinstance(stmt, WhileStmt):
                stmt_text = self._fmt_while_stmt(stmt, lspace)
            elif isinstance(stmt, DoWhileStmt):
                stmt_text = self._fmt_do_while_stmt(stmt, lspace)
            else:
                assert False, f"未知语句类型: {type(stmt)}"
            if stmt_text.strip():
                text += stmt_text + "\n"

        return text

    def _fmt_pcode_stmt(self, stmt: PcodeStmt, lspace=""):
        if stmt.opcode in (
            OpCode.BRANCH,
            OpCode.BRANCHIND,
            OpCode.CBRANCH,
        ):
            return ""
        if self._no_pcode:
            text = lspace + stmt.comment
        else:
            text = f"{lspace}// {stmt.comment}\n" if stmt.comment else ""
            text += lspace + self._fmt_op(stmt.op)
        return text

    def _fmt_op(self, op: PcodeOp) -> str:
        fmt = self.PPP.OP_FORMATS.get(op.opcode, self.PPP.DEFAULT_OP_FORMAT)
        fmt.fmt_vn = VarExpr.fmt_vn  # Monkey patch
        return (f"{fmt.fmt_vn(op.output)} = " if op.output else "") + fmt.fmt(op)

    def _fmt_goto_stmt(self, stmt: GotoStmt, lspace=""):
        return lspace + f"goto {stmt.target_label}"

    def _fmt_continue_stmt(self, stmt: ContinueStmt, lspace=""):
        return lspace + "continue"

    def _fmt_break_stmt(self, stmt: BreakStmt, lspace=""):
        return lspace + "break"

    def _fmt_if_stmt(self, stmt: IfStmt, lspace=""):
        cond = self._fmt_expr(stmt.cond)
        text = lspace + f"if ({cond})" + " {\n"
        text += self.fmt_stmts(stmt.true_body, lspace + self.INDENT)
        if stmt.false_body:
            text += lspace + "} else {\n"
            text += self.fmt_stmts(stmt.false_body, lspace + self.INDENT)
        text += lspace + "}"
        return text

    def _fmt_switch_stmt(self, stmt: SwitchStmt, lspace="") -> str:
        raise NotImplementedError()

    def _fmt_while_stmt(self, stmt: WhileStmt, lspace="") -> str:
        cond = self._fmt_expr(stmt.cond)
        body = self.fmt_stmts(stmt.body, lspace + self.INDENT)
        text = lspace + f"while ({cond})" + " {\n"
        text += body
        text += lspace + "}"
        return text

    def _fmt_do_while_stmt(self, stmt: DoWhileStmt, lspace="") -> str:
        cond = self._fmt_expr(stmt.cond)
        body = self.fmt_stmts(stmt.body, lspace + self.INDENT)
        text = lspace + "do {\n"
        text += body
        text += lspace + f"}} while ({cond});"
        return text

    def _fmt_expr(self, expr: Expression) -> str:
        return str(expr)


class CFGDisplayer:
    """控制流图可视化工具"""

    def __init__(self, formatter: CodeFormatter):
        self.formatter = formatter

    def draw_cfg(self, cfg: ControlFlowGraph, graph_path: str, highlights=list[int]):
        """把CFG图转化为PNG格式的图片，并保存到graph_path

        :param cfg: 控制流图
        :type cfg: class:`ControlFlowGraph`
        :param graph_path: 图片保存路径
        :param highlights: 高亮的节点地址列表
        """
        agraph = self.format_cfg(cfg)
        # 定制化图属性
        agraph.graph_attr.update(
            {
                "rankdir": "TB",  # Top to bottom directed graph
                "fontsize": "10",
                "fontcolor": "#333333",
                "bgcolor": "white",
                "pad": "0.5",  # Page padding
            }
        )

        # 定制化节点属性
        for node in agraph.nodes():
            address = int(node.attr["address"])
            fillcolor = "#cccccc" if address not in highlights else "#d9ead3"
            node_label = node.name.replace("\n", "\\l")
            node.attr.update(
                {
                    "label": node_label,
                    "shape": "box",
                    "style": "filled",
                    "align": "left",
                    "fillcolor": fillcolor,
                    "fontcolor": "#000000",
                    "fontsize": "10",
                    "fontname": "Times New Roman",
                }
            )

        # 定制化边属性
        for edge in agraph.edges():
            edge.attr.update(
                {
                    "color": "#999999",
                    "arrowhead": "normal",
                    "fontsize": "8",
                }
            )
            if not edge.attr.get("label"):
                edge.attr["label"] = ""

        # 使用graphviz包中的'dot'程序来绘制图片
        agraph.draw(str(graph_path), prog="dot", format="png")
        return

    def format_cfg(self, cfg: ControlFlowGraph) -> AGraph:
        """将控制流图转化为文本形式

        :param cfg: 控制流图
        :return: 文本格式的控制流图，图中的每一个节点为对应控制流图节点的文本表示
        """

        class _CFGTextNode(object):
            def __init__(
                self, node: CFGNode, lift_mode: LiftMode, formatter: CodeFormatter
            ):
                if lift_mode < LiftMode.HIGH:
                    self.text = formatter.fmt_insns(node.address, node.insns)
                else:
                    self.text = f"{node.address:#08X}:\n" + formatter.fmt_stmts(
                        node.insns
                    )

            def __str__(self):
                return self.text

        graph = nx.DiGraph()
        trans = dict()
        for node in cfg.nodes:
            new_node = trans[node] = _CFGTextNode(node, cfg.lift_mode, self.formatter)
            graph.add_node(new_node, address=node.address)

        for u, v, data in cfg.edges.data(data=True):
            graph.add_edge(trans[u], trans[v], **data)

        return nx.nx_agraph.to_agraph(graph)
