# 数据结构实验报告（Ex2_1 与 Ex2_2_linkedlist）

仓库：`jaraum/DataStructuresEx`

> 说明：本报告依据仓库 `main` 分支中以下源码进行整理（为便于查阅均给出链接）。

- Ex2_1
  - `Ex2_1/main.c`：https://github.com/jaraum/DataStructuresEx/blob/40985042ab30e63f26beaf1d1e898df76d2a315d/Ex2_1/main.c
  - `Ex2_1/bt.c`：https://github.com/jaraum/DataStructuresEx/blob/40985042ab30e63f26beaf1d1e898df76d2a315d/Ex2_1/bt.c
  - `Ex2_1/bt.h`：https://github.com/jaraum/DataStructuresEx/blob/40985042ab30e63f26beaf1d1e898df76d2a315d/Ex2_1/bt.h
- Ex2_2_linkedlist
  - `Ex2_2_linkedlist/main.c`：https://github.com/jaraum/DataStructuresEx/blob/40985042ab30e63f26beaf1d1e898df76d2a315d/Ex2_2_linkedlist/main.c
  - `Ex2_2_linkedlist/hfmTree.c`：https://github.com/jaraum/DataStructuresEx/blob/40985042ab30e63f26beaf1d1e898df76d2a315d/Ex2_2_linkedlist/hfmTree.c
  - `Ex2_2_linkedlist/hfmTree.h`：https://github.com/jaraum/DataStructuresEx/blob/40985042ab30e63f26beaf1d1e898df76d2a315d/Ex2_2_linkedlist/hfmTree.h

---

## 一、Ex2_1 实验报告（二叉树基本操作：遍历/统计/交换）

### 1、算法设计

#### 1.1 需求概述
实现链式二叉树的基本操作：
- 构造示例二叉树；
- 输出先序/中序/后序遍历序列；
- 统计结点数、叶子结点数、树高；
- 交换左右子树（镜像翻转）并再次输出遍历结果。

#### 1.2 模块划分与层次结构
本实验可按“应用层—ADT接口层—ADT实现层”组织：

- **应用层（Ex2_1/main.c）**
  - 构造测试树 `InitExampleTree()`
  - 依次调用：遍历输出 `Order()`、统计输出 `Count()`、交换 `Swap()`

- **ADT接口层（Ex2_1/bt.h）**
  - 定义结点与二叉树结构体：`BTNode`、`BinaryTree`
  - 声明对外接口：创建、建树、遍历、统计、交换等函数

- **ADT实现层（Ex2_1/bt.c）**
  - 结点创建 `NewNode`
  - 组合建树 `MakeTree`
  - 遍历（递归）
  - 统计（递归）
  - 交换左右子树（递归）
  - 清理释放（递归）

#### 1.3 主要函数调用关系与数据传递
数据结构：
- `BinaryTree`：仅包含 `BTNode *root`
- `BTNode`：包含 `element`、`lChild`、`rChild`

调用关系（简要）：
- `main()`
  - `InitExampleTree()` → `Create()`、`MakeTree()` → `NewNode()`
  - `Order(&bt)` → `PreOrderTree()`→`PreOrder()`；`InOrderTree()`→`InOrder()`；`PostOrderTree()`→`PostOrder()`
  - `Count(&bt)` → `TreeSize()`→`Size()`；`GetLeafNum()`→`LeafNum()`；`GetTreeHeight()`→`Height()`
  - `Swap(&bt)` → `SwapTrees()`→`SwapSubTrees()`

数据传递方式：
- 树对象在 `main` 中以结构体形式创建，并通过 **指针参数 `BinaryTree*`** 传入各接口函数；
- 交换操作会直接修改结点的左右孩子指针，从而改变树的结构（镜像），但不改变结点集合。

#### 1.4 关键流程（文字流程图）

**A. 先序遍历（PreOrder）**
1. 若当前结点为空，返回
2. 访问当前结点
3. 递归遍历左子树
4. 递归遍历右子树

**B. 结点数统计（Size）**
1. 若当前结点为空，返回 0
2. 返回 `Size(left) + Size(right) + 1`

**C. 左右子树交换（SwapSubTrees）**
1. 若当前结点为空，返回
2. 递归处理左子树
3. 递归处理右子树
4. 交换当前结点 `lChild` 与 `rChild` 指针

---

### 2、算法实现与分析

#### 2.1 核心代码（节选 + 注释）

> 注：以下代码节选自仓库源码；为实验报告阅读性添加了说明性注释。

**（1）二叉树遍历（先序/中序/后序）**
```c
// Ex2_1/bt.c
void PreOrder(BTNode *t) {
  if (!t) return;            // 递归出口
  printf("%c", t->element); // 访问根
  PreOrder(t->lChild);       // 左
  PreOrder(t->rChild);       // 右
}

void InOrder(BTNode *t) {
  if (!t) return;
  InOrder(t->lChild);        // 左
  printf("%c", t->element); // 根
  InOrder(t->rChild);        // 右
}

void PostOrder(BTNode *t) {
  if (!t) return;
  PostOrder(t->lChild);      // 左
  PostOrder(t->rChild);      // 右
  printf("%c", t->element); // 根
}
```

**（2）统计：结点数/叶子数/高度**
```c
// Ex2_1/bt.c
int Size(BTNode *t) {
  if (!t) return 0;
  return Size(t->lChild) + Size(t->rChild) + 1;
}

int LeafNum(BTNode *t) {
  if (!t) return 0;
  if (t->lChild == NULL && t->rChild == NULL) return 1; // 叶子
  return LeafNum(t->lChild) + LeafNum(t->rChild);
}

int Height(BTNode *t) {
  if (!t) return 0;
  int leftHeight = Height(t->lChild);
  int rightHeight = Height(t->rChild);
  return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}
```

**（3）交换左右子树（镜像翻转）**
```c
// Ex2_1/bt.c
void SwapSubTrees(BTNode *t) {
  if (!t) return;

  SwapSubTrees(t->lChild);
  SwapSubTrees(t->rChild);

  // 交换左右孩子指针
  BTNode *temp = t->lChild;
  t->lChild = t->rChild;
  t->rChild = temp;
}
```

**（4）主程序测试逻辑（构造示例树、遍历/统计/交换）**
```c
// Ex2_1/main.c
int main(void) {
  BinaryTree mytree = InitExampleTree();
  Order(&mytree);
  Count(&mytree);
  Swap(&mytree);

  printf("New tree order:");
  Order(&mytree);
  return 0;
}
```

#### 2.2 时间复杂度分析
设二叉树结点数为 `n`，树高为 `h`：
- 先序/中序/后序遍历：每个结点访问 1 次
  - 时间复杂度：**O(n)**
  - 递归栈空间：**O(h)**（最坏退化为链时 O(n)）
- 结点数、叶子数、树高统计：均需遍历整棵树
  - 时间复杂度：**O(n)**
  - 递归栈空间：**O(h)**
- 左右子树交换：每个结点交换一次
  - 时间复杂度：**O(n)**
  - 递归栈空间：**O(h)**

---

### 3、实验结果与结论

#### 3.1 测试数据
测试树由 `InitExampleTree()` 构造，结点元素为字符（例如 B、C、D、E、F 等），程序会打印：
- 交换前：先序/中序/后序遍历结果
- 结点数、叶子数、树高
- 交换后：新的三种遍历结果

#### 3.2 预期结果说明
- **交换前后**：结点数、叶子数、树高应保持不变（只是左右孩子指针互换，结构镜像）。
- 遍历序列会变化：交换后相当于对原树做镜像，遍历结果会呈对应变化。

#### 3.3 实验结论
- 递归遍历是二叉树操作最自然、实现最简洁的方法；
- 镜像交换不会改变树的规模统计特征，但会改变遍历顺序；
- 主要操作时间复杂度均为 O(n)，在实验规模下运行效率良好。

---

## 二、Ex2_2_linkedlist 实验报告（哈夫曼树构造 + 编码/译码）

### 1、算法设计

#### 1.1 需求概述
实现 Huffman 编码的典型流程：
1. 给定符号集合及其权重（频率）；
2. 构造 Huffman 树；
3. 生成每个符号的 Huffman 编码表；
4. 对给定字符串进行编码（生成 0/1 比特串）；
5. 对比特串译码还原原文本，并验证正确性。

#### 1.2 模块划分与层次结构
- **应用层（Ex2_2_linkedlist/main.c）**
  - 给出符号与权重（A~Z）
  - 调用：构造树→生成码表→编码→译码→一致性检查

- **ADT接口层（Ex2_2_linkedlist/hfmTree.h）**
  - Huffman 树结点 `HFMTNode`、树 `BinaryTree`
  - 码表 `HFMCodeTable`
  - 优先队列（最小堆）`PriorityQueue`
  - 对外接口：建树、生成码表、编码译码、清理

- **实现层（Ex2_2_linkedlist/hfmTree.c）**
  - 最小堆：`InsertPQ`、`Serve`
  - 建树：`CreateHuffmanTree`（反复合并两最小权重子树）
  - 生成码表：`TraverseCode` 深度优先遍历
  - 编码：查表拼接
  - 译码：在树上按位行走，遇到叶子输出字符

#### 1.3 函数调用关系与数据传递
- `main()`
  - `CreateHuffmanTree(symbols, weights, count, &tree)` 输出 `tree.root`
  - `CreateHuffmanCode(&tree, &codeTable)` 输出 `codeTable.codes[]`
  - `EncodeText(sourceText, &codeTable, &encoded)` 输出动态分配的编码串
  - `DecodeBits(encoded, &tree, &decoded)` 输出动态分配的译码文本
  - `DestroyHuffmanCodes` + `ClearHuffmanTree` + `free` 释放资源

#### 1.4 关键流程（文字流程图）

**A. Huffman 树构造（最小堆）**
1. 将每个符号作为叶子结点插入最小堆（按权重排序）
2. 重复直到堆中只剩 1 个结点：
   - 取出权重最小的两棵树 left、right
   - 合并生成父结点 parent（权重=left.w+right.w）
   - parent 入堆
3. 剩余结点为 Huffman 树根

**B. 生成 Huffman 编码表（DFS）**
1. 从根开始深度优先遍历
2. 向左分支记 0，向右分支记 1
3. 到叶子时，路径比特串即该符号的编码

**C. 译码**
1. 从根读取 bits
2. bit=0 走左，bit=1 走右
3. 走到叶子输出符号并回到根继续

---

### 2、算法实现与分析

#### 2.1 核心代码（节选 + 注释）

**（1）最小堆优先队列插入/删除最小值**
```c
// Ex2_2_linkedlist/hfmTree.c
void InsertPQ(PriorityQueue *pq, HFMTNode *node) {
  if (pq->size == pq->capacity) return;
  int i = ++pq->size;
  while (i > 1 && pq->data[i / 2]->w > node->w) {
    pq->data[i] = pq->data[i / 2];
    i /= 2;
  }
  pq->data[i] = node;
}

HFMTNode *Serve(PriorityQueue *pq) {
  if (pq->size == 0) return NULL;

  HFMTNode *minNode = pq->data[1];
  HFMTNode *lastNode = pq->data[pq->size--];

  int i = 1;
  while (i * 2 <= pq->size) {
    int child = i * 2;
    if (child != pq->size && pq->data[child + 1]->w < pq->data[child]->w) child++;
    if (lastNode->w > pq->data[child]->w) {
      pq->data[i] = pq->data[child];
      i = child;
    } else break;
  }
  pq->data[i] = lastNode;
  return minNode;
}
```

**（2）构造 Huffman 树**
```c
// Ex2_2_linkedlist/hfmTree.c
int CreateHuffmanTree(const ElemType symbols[], const int weights[], int count, BinaryTree *tree) {
  PriorityQueue *pq = CreatePQ(count);

  for (int i = 0; i < count; ++i) {
    HFMTNode *node = CreateNode(symbols[i], weights[i], NULL, NULL);
    InsertPQ(pq, node);
  }

  while (pq->size > 1) {
    HFMTNode *left = Serve(pq);
    HFMTNode *right = Serve(pq);

    BinaryTree leftTree = {left}, rightTree = {right}, parentTree = {NULL};
    MakeTree(&parentTree, '\0', &leftTree, &rightTree); // 父权重=左右权重和
    InsertPQ(pq, parentTree.root);
  }

  tree->root = Serve(pq);
  DestroyPQ(pq);
  return OK;
}
```

**（3）生成码表（DFS 遍历路径编码）**
```c
// Ex2_2_linkedlist/hfmTree.c
void TraverseCode(HFMTNode *node, char *code, int depth, HFMCodeTable *table) {
  if (!node) return;

  if (IsLeaf(node)) {
    code[depth] = '\0';
    DuplicateString(code, &table->codes[(unsigned char)node->element]);
    return;
  }

  code[depth] = '0';
  TraverseCode(node->lChild, code, depth + 1, table);

  code[depth] = '1';
  TraverseCode(node->rChild, code, depth + 1, table);
}
```

**（4）编码/译码**
```c
// Ex2_2_linkedlist/hfmTree.c
int EncodeText(const char *text, const HFMCodeTable *table, char **encodedBits) {
  // 先累计总长度，再一次性分配，最后拼接
  ...
}

int DecodeBits(const char *bits, const BinaryTree *tree, char **decodedText) {
  // 按位走树；到叶子输出字符并回到根
  ...
}
```

#### 2.2 时间复杂度分析
设符号数为 `n`，文本长度为 `m`，编码后比特总长度为 `L`：
- 构造 Huffman 树（最小堆）：**O(n log n)**
- 生成码表（遍历树）：**O(n)**
- 编码：与输出长度相关，通常可表述为 **O(L)**（实现使用 `strcat`，在大规模数据下可进一步优化为指针写入避免重复扫描）
- 译码：逐比特走树：**O(L)**

---

### 3、实验结果与结论

#### 3.1 测试数据
- 符号：A~Z
- 权重：代码内置频率数组
- 测试文本：`HELLOWORLD`

程序输出包含：
1. 各字母的 Huffman 编码表；
2. 原文、编码后的 0/1 串、译码结果；
3. 一致性检查 `Round-trip check: PASS/FAIL`。

> 说明：Huffman 编码表的具体 0/1 串与“合并时左右子树选择”等实现细节有关；但只要编码与译码使用同一棵树与同一码表，译码结果应与原文一致。

#### 3.2 实验结论
- Huffman 编码利用前缀码性质实现无歧义压缩：高频字符短码、低频字符长码；
- 使用最小堆构造 Huffman 树可达到 O(n log n)；
- 通过“编码→译码→对比原文”的 round-trip 检查可验证实现正确性。

---

## 参考链接
- Ex2_1/bt.c：https://github.com/jaraum/DataStructuresEx/blob/40985042ab30e63f26beaf1d1e898df76d2a315d/Ex2_1/bt.c
- Ex2_1/bt.h：https://github.com/jaraum/DataStructuresEx/blob/40985042ab30e63f26beaf1d1e898df76d2a315d/Ex2_1/bt.h
- Ex2_1/main.c：https://github.com/jaraum/DataStructuresEx/blob/40985042ab30e63f26beaf1d1e898df76d2a315d/Ex2_1/main.c
- Ex2_2_linkedlist/hfmTree.c：https://github.com/jaraum/DataStructuresEx/blob/40985042ab30e63f26beaf1d1e898df76d2a315d/Ex2_2_linkedlist/hfmTree.c
- Ex2_2_linkedlist/hfmTree.h：https://github.com/jaraum/DataStructuresEx/blob/40985042ab30e63f26beaf1d1e898df76d2a315d/Ex2_2_linkedlist/hfmTree.h
- Ex2_2_linkedlist/main.c：https://github.com/jaraum/DataStructuresEx/blob/40985042ab30e63f26beaf1d1e898df76d2a315d/Ex2_2_linkedlist/main.c