# PoreDec
本项目是《逆向工程原理》课程的PJ2，实现一个反编译器的以下两个功能：
1. **控制流图构建** - 从二进制文件中提取并构建控制流图
2. **结构化代码生成** - 基于控制流图生成结构化的高级语言代码

## 实现方式

通过在以下两个文件中补全代码完成：
- `poredec/frontend/cfg_builder.py` - 控制流图构建
- `poredec/backend/structure_converter.py` - 结构化代码生成

## 项目结构

- `benchmarks/` - 测试样例
- `docs-html` - 项目介绍
- `outputs/` - 输出结果
- `poredec/` - 核心代码

## 任务一: 控制流图构建
### 1.1 实现思路

整体思路分为五个步骤：

1. **反汇编所有可达指令**：从函数入口地址开始，采用工作列表逐条反汇编指令，并沿指令的后继地址扩展，直到所有可达的指令都被反汇编完毕。这一步利用了`DisasInsn`类中的`succs`字段，该字段对于条件跳转指令包含两个后继地址，对于无条件跳转指令包含跳转目标地址，对于顺序执行指令包含下一条指令地址，对于返回指令后继为空。

2. **识别基本块边界**：基本块的起始指令和终止指令的定义存在循环依赖关系——起始指令的前驱数量不为1或前驱是终止指令；终止指令的后继数量不为1或后继是起始指令。这种循环依赖使得必须采用迭代算法，反复扫描所有指令，直到不再产生新的起始/终止指令为止。入口地址必然是一个起始指令。

3. **构造基本块**：将起始指令按地址排序后，对每个起始指令，收集从它开始到下一条起始指令之前的所有指令，构成一个基本块。特别地，如果遇到终止指令，则该基本块到此结束。

4. **连接基本块**：根据每个基本块最后一条指令的后继信息，查找后继地址所在的基本块，从而建立控制流边。对于条件跳转，需要用"T"和"F"标签区分两个分支。

5. **设置入口节点**：将包含入口地址的基本块设置为控制流图的入口节点。

### 1.2 代码实现

**步骤1：反汇编所有可达指令**

```python cfg_builder.py
insns: dict[int, DisasInsn] = {}  
worklist = [entry_addr]
while worklist:
    addr = worklist.pop()
    if addr in insns:
        continue
    insn = self.lifter.disassemble_at(addr)
    if insn is None:
        continue
    insns[addr] = insn
    # 将后继地址加入工作列表
    for succ_addr in insn.succs:
        if succ_addr not in insns:
            worklist.append(succ_addr)
```

这里使用工作列表法进行遍历。维护一个工作列表`worklist`，初始包含入口地址。每次从中取出一个地址进行反汇编，将新得到的指令的后继地址加入工作列表。为了避免重复反汇编，使用`insns`字典记录已处理的地址。反汇编方法`disassemble_at`使用Capstone引擎在指定地址处反汇编一条ARM指令，并将结果封装为`DisasInsn`对象。`DisasInsn`的`from_cs_insn`类方法会根据指令类型自动计算出`succs`字段。

**步骤2：识别基本块的起始和终止指令**

```python cfg_builder.py
# 统计每条指令的前驱数量
pred_counts: dict[int, int] = {addr: 0 for addr in insns}
for addr, insn in insns.items():
    for succ_addr in insn.succs:
        if succ_addr in pred_counts:
            pred_counts[succ_addr] += 1

leaders: set[int] = set()       # 起始指令地址集合
terminators: set[int] = set()   # 终止指令地址集合

# 入口地址一定是起始指令
leaders.add(entry_addr)

# 初始标记：跳转指令和返回指令是终止指令
for addr, insn in insns.items():
    if insn.is_jump or insn.is_ret:
        terminators.add(addr)

# 迭代算法：反复扫描直到不再产生新的起始/终止指令
changed = True
while changed:
    changed = False
    # 发现新的起始指令
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
    # 发现新的终止指令
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
```

起始指令的定义为：
1. 有0条或>1条前驱指令
2. 其唯一前驱是终止指令。
终止指令的定义为：
1. 有0条或>1条后继指令
2. 其唯一后继是起始指令  
这两个定义相互依赖，因此采用迭代算法解决：初始化所有跳转和返回指令标记为终止指令，入口地址标记为起始指令；然后反复扫描所有指令，根据当前已知的起始/终止指令集合来发现新的起始/终止指令，直到两集合不再变化。这里还需要预先统计每条指令的前驱数量，以便高效判断"前驱数量不为1"的条件。

**步骤3：构造基本块**

```python cfg_builder.py
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
```

首先对起始指令按地址排序。对于每个起始指令，从该地址开始依次收集指令，直到遇到终止指令或者下一条起始指令为止。具体来说，遇到以下情况之一就会结束当前基本块：
1. 当前指令是终止指令
2. 下一条指令地址已达到或超过下一个起始指令地址
3. 下一条指令地址不在反汇编结果中。收集到的指令序列用于创建`CFGNode`对象，其地址为起始指令的地址。

**步骤4：连接基本块**

```python cfg_builder.py
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
```

遍历每个基本块，取出最后一条指令的所有后继地址。对于每个后继地址，查找包含该地址的基本块。对于条件跳转指令，第一个后继`succs[0]`是True分支的跳转目标，第二个后继`succs[1]`是False分支的fall-through地址，分别以标签"T"和"F"标记边，以便后续可视化时区分两个分支。

**步骤5：设置入口节点**

```python cfg_builder.py
if entry_addr in blocks:
    cfg.set_entry(blocks[entry_addr])
```

将包含函数入口地址的基本块设置为控制流图的入口节点。`set_entry`方法将`cfg.entry`设置为对应的`CFGNode`。

### 结果分析

以`httpd_B3FE0`测试用例为例，分析控制流图构建算法的完整过程。

该函数位于httpd二进制程序的地址`0xB3FE0`处。函数执行流程如下：

1. 从入口地址`0xB3FE0`开始反汇编，第一条指令`push {fp, lr}`是顺序执行指令，后继地址为`0xB3FE4`
2. 在`0xB3FEC`处有一条跳转指令`b #0xB400C`，因此该指令的后继只有`0xB400C`（无fall-through），同时该指令被标记为终止指令
3. `0xB400C`有两条前驱（来自`0xB3FEC`的跳转和`0xB4040`的条件跳转），因此被标记为起始指令（leader）
4. `0xB4044`处是一个条件跳转`cmp`+`beq`组合，使得该地址有两条前驱，成为leader；该地址的条件跳转有两个后继，因此也是终止指令
5. 通过迭代算法不断发现新的leader和terminator，最终将函数划分为若干基本块

生成的CFG图清晰地展示了函数的控制流结构：入口基本块通过无条件跳转进入循环体，循环体内部的`if-break`结构可以跳出循环。
<figure style="text-align: center; margin: 0;">
  <img src="../PJ2/outputs/httpd_B3FE0/cfg-disassemble.png" width="80%">
  <figcaption style="font-size: 0.85em; color: #666; margin-top: 5px;">
    图1：cfg-disassemble.png
  </figcaption>
</figure>

<figure style="text-align: center; margin: 0;">
  <img src="../PJ2/outputs/httpd_B3FE0/cfg-pcode.png" width="80%">
  <figcaption style="font-size: 0.85em; color: #666; margin-top: 5px;">
    图2：cfg-pcode.png
  </figcaption>
</figure>

<figure style="text-align: center; margin: 0;">
  <img src="../PJ2/benchmarks/references/httpd_B3FE0.png" width="80%">
  <figcaption style="font-size: 0.85em; color: #666; margin-top: 5px;">
    图3：httpd_B3FE0.png
  </figcaption>
</figure>

```
原始ARM汇编流 (按地址顺序):
0xB3FE0: push {fp, lr}      -> BB1 (entry)
0xB3FE4: add fp, sp, #4
0xB3FE8: sub sp, sp, #8
0xB3FEC: b #0xB400C          -> edge to BB2
0xB400C: ldr r3, [fp, #-8]  -> BB2
...                           -> cond edge to BB3 / exit
0xB4044: ...                  -> BB3 (loop body)
```

通过这一分析可以看出，我们的算法能够正确地将线性汇编指令序列组织为结构化的控制流图，其中每个基本块内指令连续顺序执行，基本块之间有控制流边连接。

---

## 任务二: 结构化代码生成
### 2.1 实现思路
整体实现思路分为以下几个层次：

1. **深度搜索遍历**：通过深度搜索遍历 CFG 的每一个节点，尝试完成化简操作。化简过程中 CFG 上的边逐渐被高级语言结构（Statement）所代替，直到整张 CFG 被化简为单个节点。

2. **针对性规则优先**：优先识别标准的控制流结构。若节点是循环头，则使用针对性和通用规则化简整个循环。其它情况下，尝试使用针对性规则如 `try_reduce_sequence`、`try_reduce_if` 等化简。

3. **通用规则兜底**：若无节点能被针对性规则化简，则使用默认的通用规则进行化简，如 `try_reduce_goto_sequence` 与 `try_reduce_goto_branch`。

### 2.2 代码实现

结构化代码生成的实现集中在 `structure_converter.py` 的一系列 `try_reduce_` 方法中。以下对八个核心图约简规则的具体实现进行详细分析。

**1. 降级顺序规则：`try_reduce_goto_sequence`**
该规则用于处理单一后继但无法应用高级抽象的节点。

```python
def try_reduce_goto_sequence(self, node: CFGNode) -> bool:
    succs = self.successors(node)
    if len(succs) != 1:
        return False
    succ = succs[0]
    goto_stmt = self.gen_goto_stmt(succ)
    self.reduce_node(node, [goto_stmt], [], True)
    return True

```

算法首先判定当前节点的后继数量是否严格为 1。若满足，则调用 `self.gen_goto_stmt(succ)` 生成一条显式的无条件跳转语句。随后利用 `self.reduce_node` 将该 `goto_stmt` 附加到原基本块指令中，并移除原有控制流边，完成单步折叠。

**2. 降级分支规则：`try_reduce_goto_branch`**
该规则用于处理包含两个后继但不满足标准 `if-else` 拓扑的分支。

```python
def try_reduce_goto_branch(self, node: CFGNode) -> bool:
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

```

当节点包含两个后继时，提取末尾条件表达式 `cond`。通过 `gen_goto_stmt` 分别为两个后继生成跳转语句，并借助 `gen_if_stmt` 构造 `if(cond) goto succ1; else goto succ2;`。最终调用 `reduce_node` 将 CFG 边转化为代码内部逻辑。

**3. 自循环规则：`try_reduce_while_true`**
该规则识别并合并无出口的绝对死循环。

```python
def try_reduce_while_true(self, node: CFGNode) -> bool:
    succs = self.successors(node)
    if len(succs) != 1 or succs[0] != node:
        return False
    while_stmt = self.gen_while_stmt(ConstExpr(1), node.insns)
    self.reduce_node(node, [while_stmt], [], False)
    return True

```

匹配条件为后继数量为 1 且后继指向自身（自循环）。算法生成条件恒为真 `ConstExpr(1)` 的 `WhileStmt`。在调用 `reduce_node` 时，`extend=False` 参数确保 `WhileStmt` 整体替换原有的底层指令，完成层次化语句的构建。

**4. 后测试循环规则：`try_reduce_do_while`**
识别 `do-while` 结构。

```python
def try_reduce_do_while(self, node: CFGNode) -> bool:
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

```

算法要求节点包含两条边：一条回边指向自身，另一条为出口边。条件表达式作为 `DoWhileStmt` 的独立字段保存。提取循环体时需通过 `node.insns[:-1]` 剔除末尾原本用于底层跳转的 `CBRANCH` 指令，从而消除冗余逻辑。

**5. 顺序规则：`try_reduce_sequence`**
合并满足支配关系的连续基本块。

```python
def try_reduce_sequence(self, node: CFGNode) -> bool:
    succs = self.successors(node)
    if len(succs) != 1 or succs[0] == node:
        return False
    succ = succs[0]
    new_succs = self.successors(succ)
    self.reduce_node(node, succ.insns, new_succs, True)
    return True

```

只要存在唯一的非自循环后继，即可触发合并。将 `succ.insns` 吸收至当前节点，并将当前节点的后继指针跨越 `succ` 更新为 `new_succs`。这是消除线性基本块链的核心机制。

**6. 单分支规则：`try_reduce_if`**
识别旁路结构（`if-then`）。

```python
def try_reduce_if(self, node: CFGNode, true_branch: bool) -> bool:
    # ... 省略非核心代码
    cond = self.get_cond_expr(node)
    if not true_branch:
        cond = cond.logical_not()
    if_stmt = self.gen_if_stmt(cond, if_node.insns, None)
    self.reduce_node(node, [if_stmt], [if_succ], True)
    return True

```

要求分支节点 `if_node` 有且仅有一个后继，且该后继必须与跳过分支的 `if_succ` 会合。若传入的尝试匹配方向为 `False` 分支，通过 `cond.logical_not()` 进行条件取反，保证生成的 `IfStmt` 语义正确。

**7. 循环控制规则：`try_reduce_if_continue`与`try_reduce_if_break`**
处理循环内部的提前跳转。
对于 `if_continue`，检查 `if_node` 的唯一后继是否为所在自然循环的 `loop.header`。匹配后生成 `self.gen_continue_stmt(loop.header)`，封装进 `IfStmt`。
对于 `if_break`，检查 `if_node` 是否为循环的外层出口节点（`not self.is_loop_succ(if_node, loop)` 为假则排除，实际需通过 `self.is_loop_succ` 判断）。匹配后生成 `self.gen_break_stmt(loop.header)`。两者均在保留高级循环逻辑的同时，消除了底层的长跳转边。

**8. 双分支规则：`try_reduce_if_else`**
处理菱形控制流拓扑。

```python
def try_reduce_if_else(self, node: CFGNode) -> bool:
    # ... 省略非核心代码
    if len(if_succs) != 1 or len(else_succs) != 1:
        return False
    if if_succs[0] != else_succs[0]:
        return False
    # ...
    if_stmt = self.gen_if_stmt(cond, if_node.insns, else_node.insns)
    self.reduce_node(node, [if_stmt], [if_succ], True)

```

核心识别逻辑要求 `true_body` 与 `false_body` 两条路径均具有单一后继，且必须完全汇聚于同一目标节点 `if_succs[0] == else_succs[0]`。满足条件后，利用 `gen_if_stmt` 组装包含双侧语句的抽象节点。

### 结果分析

1. **`try_reduce_sequence`**：
* **测试用例：** `sequence_1052C`
* **分析：** 从 `outputs/sequence_1052C/cfg-disassemble.png` 可见初始 CFG 呈线性链表分布。化简引擎连续触发 `SEQUENCE` 规则，将多段 P-code 指令折叠入单个根节点，`decompiled.c` 中不再含有跳转边，生成纯粹的线性语句序列。

2. **`try_reduce_goto_sequence` 与 `try_reduce_goto_branch`**：
* **测试用例：** `httpd_209AC`
* **分析：** 在 `httpd_209AC` 中包含复杂的不可约流交叉边。对于无法匹配 `if` 或循环的高复杂度汇聚点，算法回退触发 `GOTO_SEQUENCE` 和 `GOTO_BRANCH` 规则，强制生成显式的 `goto LAB_XXX` 语句。此操作在 `decompile.log` 中被记录，确保了所有 CFG 的最终闭包性。

3. **`try_reduce_while_true`**：
* **测试用例：** `loop_while_true_10420`
* **分析：** 初始 CFG 中存在明确的自循环回边。算法生成外层的 `while (1)` AST 节点包裹数据流操作，通过 `debug-structure/` 中产生的中间结果图片可以观察到，包含自循环边的节点最终收敛为单一的结构化块。

4. **`try_reduce_do_while`**：
* **测试用例：** `loop_while_10420`
* **分析：** 循环体在末尾具有一条退出边与一条回边。化简逻辑剥离了末尾的条件判断指令，并组装出 `do { ... } while (cond)` 语法，这反映在输出目录下的 `decompiled_simplified.c` 文件中，结构清晰。

5. **`try_reduce_if`**：
* **测试用例：** `branch_if_10420`
* **分析：** 控制流出现分叉并旁路跳过了一个基本块，最终汇合。结构化后生成了标准不带 `else` 的单 `if` 块。CFG 边转化为层次化包含关系。

6. **`try_reduce_if_continue`**：
* **测试用例：** `loop_while_continue_10450`
* **分析：** 根据 `loop_info` 的分析，循环体内的一个条件判定目标直接指向 `loop.header`。在 `decompiled_simplified.c` 中，对应的底层长距离跳回操作被精准转换为了高级语义的 `continue;` 关键字。

7. **`try_reduce_if_break`**：
* **测试用例：** `loop_while_if_10450`
* **分析：** 测试用例中包含跳出当前自然循环外围节点的控制边。图约简过程中，由于识别到了目标节点不属于当前循环后继集合，故成功转化为 `break;` 语句。CFG 中跨层的跳出边被安全消除。

8. **`try_reduce_if_else`**：
* **测试用例：** `branch_if_else_10420`
* **分析：** 标准菱形拓扑。由 `outputs/branch_if_else_10420/` 下的中间 PNG 文件证实，算法将两条平行路径安全地包装为 `if(cond) {...} else {...}`，并保留了唯一的汇聚后继。这使得反编译伪代码大幅度提升了可读性。
---

4. **循环处理是难点**：嵌套循环的识别和化简顺序需要精心设计。Tarjan算法用于识别强连通分量是经典方法，但对嵌套循环的精确分离仍是启发式的。

5. **代码组织与工程实践**：本项目的代码结构清晰，模块分工明确。这种工程组织方式值得在后续项目中借鉴。
