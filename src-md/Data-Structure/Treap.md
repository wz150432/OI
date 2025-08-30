# 树堆（Treap）：融合二叉搜索树与堆实现平衡高效性能

**树堆（Treap，Tree + Heap 的缩写）** 是一种兼具灵活性与高效性的数据结构，它将**二叉搜索树（BST）** 的有序性与**堆（Heap）** 的自平衡能力相结合。这种混合设计确保了插入、删除以及排名查询、前驱/后继查找等高级操作在**平均时间复杂度 O(log n)** 下高效执行。  

## 树堆的核心性质

树堆中的每个节点需同时满足以下两个关键性质：  

1. **二叉搜索树性质**：对于任意键值为 **(k)** 的节点：  
   
   - 其左子树中所有节点的键值均 **< (k)**；  
   - 其右子树中所有节点的键值均 **> (k)**。  
   
2. **大根堆性质**：每个节点拥有一个随机生成的优先级值，且对于任意节点：  
   $$
   \text{优先级}(u) \geq \text{优先级}(u 的左孩子) \quad \text{且} \quad \text{优先级}(u) \geq \text{优先级}(u 的右孩子)
   $$

这两个性质共同保证了树的平衡性：优先级的随机性避免了普通二叉搜索树可能出现的“斜树”最坏情况，确保树的平均高度为 $O(log n)$。  

## 核心组成部分

### 1. 节点结构

每个节点存储以下信息：  
- `key`：用于二叉搜索树排序的键值；  
- `val`（priority）：用于堆平衡的随机优先级；  
- `l`/`r`：指向左/右孩子的指针；  
- `cnt`：当前键值的重复计数（处理重复元素）；  
- `sz`：以当前节点为根的子树大小（用于排名查询）。  

```cpp
struct treap {
    int l, r;    // 左右孩子指针
    int key, val; // 二叉搜索树键值与堆优先级
    int cnt, sz;  // 重复计数与子树大小
} tr[N];
```


### 2. 旋转操作：维持平衡的关键  
当插入或删除操作破坏堆性质时，通过**旋转（zig/zag）** 可在保持二叉搜索树性质的同时，修复堆性质，实现树的平衡。  

#### 右旋(Zig)：

把当前旋转的节点`u`的父节点`u / 2`和`u / 2`的右子节点`u + 1`一起拆下来当做`u`的右子节点，而节点`u`原本的右节点`2 * u + 1`被当作了拆下来的父节点的左子节点。



左图中，旋转节点是 2：

- 父节点是 4，父节点的右子节点是 5；
- 节点 2 原本的右子节点是 3。

右旋后（右图）：

- 父节点 4 和它的右子节点 5，被 “拆” 下来作为节点 2 的**右子节点**；
- 节点 2 原本的右子节点 3，成为**父节点 4 的左子节点**；
- 节点 2 的左子节点 1 保持不变，最终形成右图的结构。

![img](https://img2024.cnblogs.com/blog/3695729/202508/3695729-20250830083638477-1752013309.png)

右旋用于修复“左孩子优先级高于父节点”的情况：  

```cpp
void zig(int& u) {
    int v = l(u);          // v 是 u 的左孩子
    l(u) = r(v);           // u 的左孩子指向 v 的右孩子
    r(v) = u;              // v 的右孩子指向 u
    u = v;                 // v 成为当前子树的新根
    pushup(u);             // 更新子树大小（先更新新根，再更新原根）
    pushup(r(u));
}
```

#### 左旋(Zag):  

把当前旋转的节点`u`的父节点`u / 2`和`u / 2`的左子节点`u - 1`一起拆下来当做`u`的左子节点，而节点`u`原本的左节点`2 * u`被当作了拆下来的父节点的右子节点。



左图中，旋转节点是 4：

- 父节点是 2，父节点的左子节点是 1；
- 节点 4 原本的左子节点是 3。

右旋后（右图）

- 父节点 2 和它的左子节点 1，被 “拆” 下来作为节点 4 的**左子节点**；
- 节点 4 原本的右子节点 3，成为**父节点 4 的右子节点**；
- 节点 4 的右子节点 5 保持不变，最终形成右图的结构。

![Zag](https://img2024.cnblogs.com/blog/3695729/202508/3695729-20250830083654765-454985097.png)

左旋用于修复“右孩子优先级高于父节点”的情况： 

```cpp
void zag(int& u) {
    int v = r(u);          // v 是 u 的右孩子
    r(u) = l(v);           // u 的右孩子指向 v 的左孩子
    l(v) = u;              // v 的左孩子指向 u
    u = v;                 // v 成为当前子树的新根
    pushup(u);             // 更新子树大小
    pushup(l(u));
}
```

> 注：`pushup` 函数用于更新节点的子树大小，实现逻辑为“当前节点子树大小 = 左子树大小 + 右子树大小 + 自身重复计数”，代码见下文完整实现。



旋转过程中，**中序遍历的节点顺序始终保持不变**。

- 以右旋（zig）为例：假设原树中序遍历为「左子树 → 当前节点 → 右子树」，旋转后节点的父子关系调整，但左子树、当前节点、右子树的相对顺序未被打乱（如你提供的示例中，旋转前中序为 1→2→3→4→5，旋转后仍为 1→2→3→4→5）。
- 左旋（zag）同理，仅改变节点的上下层级，不影响中序遍历的 “左→父→右” 顺序。



### 3. 插入操作  

插入键值 **(k)** 的步骤如下：  
1. 按二叉搜索树规则遍历，找到插入位置；  
2. 若位置为空，创建新节点并赋予随机优先级；  
3. 若新节点破坏堆性质，向上旋转调整。  

```cpp
void insert(int& u, int key) {
    if (!u) u = new_node(key); // 空位置，创建新节点
    else if (tr[u].key == key) tr[u].cnt ++ ; // 键值重复，增加计数
    else if (tr[u].key < key) { // 键值更大，插入右子树
        insert(tr[u].r, key);
        if (tr[tr[u].r].val > tr[u].val) zag(u); // 右孩子优先级更高，左旋
    } else { // 键值更小，插入左子树
        insert(tr[u].l, key);
        if (tr[tr[u].l].val > tr[u].val) zig(u); // 左孩子优先级更高，右旋
    }
    pushup(u); // 更新当前节点的子树大小
}
```

> 注：`new_node` 函数用于初始化新节点，代码见下文完整实现。


### 4. 删除操作  
删除键值 **\(k\) **的步骤如下：  
1. 按二叉搜索树规则遍历，找到目标节点；  
2. 若节点有重复计数，仅减少计数；  
3. 若节点为非叶子节点，通过“与优先级更高的孩子旋转”将其向下调整为叶子节点，再删除。  

```cpp
void remove(int& u, int key) {
    if (!u) return; // 未找到目标键值，直接返回
    if (tr[u].key == key) {
        if (tr[u].cnt > 1) tr[u].cnt -- ; // 有重复，减少计数
        else {
            if (tr[u].l || tr[u].r) { // 非叶子节点，需旋转调整
                // 选择优先级更高的孩子进行旋转
                if (!tr[u].r || tr[tr[u].l].val > tr[tr[u].r].val) {
                    zig(u);
                    remove(tr[u].l, key);
                } else {
                    zag(u);
                    remove(tr[u].r, key);
                }
            } else u = 0; // 叶子节点，直接删除（置空）
        }
    }
    else if (tr[u].key > key) remove(tr[u].l, key); // 键值更小，搜索左子树
    else remove(tr[u].r, key); // 键值更大，搜索右子树
    pushup(u); // 更新当前节点的子树大小
}
```


### 5. 高级查询操作  

#### 通过	键值的排名查询  
键值 **\(k\) **的排名定义为 “小于 **(k)** 的元素个数 **+ 1**”，实现逻辑如下：  
```cpp
int find_rank_by_val(int u, int key) {
    if (!u) return 1; // 空节点，返回默认排名 1
    if (tr[u].key == key) return tr[tr[u].l].sz + 1; // 目标节点，排名 = 左子树大小 + 1
    if (tr[u].key > key) return find_rank_by_val(tr[u].l, key); // 键值更小，搜索左子树
    // 键值更大，排名 = 左子树大小 + 当前节点计数 + 右子树中目标的排名
    return tr[tr[u].l].sz + tr[u].cnt + find_rank_by_val(tr[u].r, key);
}
```

#### 第 k 小元素查询

通过子树大小导航，找到第 **(k)** 小的元素：  
```cpp
int find_val_by_rank(int u, int rank) {
    if (!u) return INF; // 空节点，返回无穷大（无效值）
    // 左子树大小 >= k，第 k 小元素在左子树
    if (tr[tr[u].l].sz >= rank) return find_val_by_rank(tr[u].l, rank);
    // 左子树大小 + 当前节点计数 >= k，第 k 小元素是当前节点
    if (tr[tr[u].l].sz + tr[u].cnt >= rank) return tr[u].key;
    // 元素在右子树，调整 k 为右子树中的相对排名
    return find_val_by_rank(tr[u].r, rank - tr[tr[u].l].sz - tr[u].cnt);
}
```

#### 前驱与后继查询  
- **前驱**：小于 **(k)** 的最大元素；  
- **后继**：大于 **\(k\)** 的最小元素。  

```cpp
// 查找前驱（小于 key 的最大元素）
int find_prev(int u, int key) {
    if (!u) return -INF; // 空节点，返回负无穷（无效值）
    if (tr[u].key >= key) return find_prev(tr[u].l, key); // 键值过大，搜索左子树
    // 键值符合，取当前节点与右子树中前驱的最大值
    return max(tr[u].key, find_prev(tr[u].r, key));
} 

// 查找后继（大于 key 的最小元素）
int find_next(int u, int key) {
    if (!u) return INF; // 空节点，返回正无穷（无效值）
    if (tr[u].key <= key) return find_next(tr[u].r, key); // 键值过小，搜索右子树
    // 键值符合，取当前节点与左子树中后继的最小值
    return min(tr[u].key, find_next(tr[u].l, key));
}
```

$\newline$

## 6.完整实现代码  

```cpp
#include <iostream>
#include <cstdlib> // 用于 rand() 生成随机优先级

using namespace std;

const int N = 1e5 + 10;    // 节点最大数量
const int INF = 2e9 + 10;  // 无穷大（用于边界节点）

int n;          // 操作次数
int root, idx;  // 根节点指针、节点计数器

// 树堆节点结构
struct treap {
    int l, r;    // 左右孩子
    int key, val; // 键值、优先级
    int cnt, sz;  // 重复计数、子树大小
} tr[N];

// 宏定义：简化节点访问（可选，仅为代码简洁）
#define u(x) tr[x]
#define l(x) tr[x].l
#define r(x) tr[x].r

// 更新子树大小：当前节点大小 = 左子树大小 + 右子树大小 + 自身计数
void pushup(int u) {
    u(u).sz = u(l(u)).sz + u(r(u)).sz + u(u).cnt;
}

// 创建新节点：初始化键值、随机优先级、计数与大小
int new_node(int key) {
    u( ++ idx).key = key;
    u(idx).val = rand(); // 随机优先级（确保平衡性）
    u(idx).sz = u(idx).cnt = 1;
    return idx;
}

// 初始化树堆：创建两个边界节点（负无穷、正无穷），避免边界判断
void build() {
    new_node(-INF), new_node(INF);
    root = 1, tr[1].r = 2; // 根节点指向负无穷，其右孩子指向正无穷
    pushup(root);
}

// 右旋操作（Zig）
void zig(int& u) {
    int v = l(u);
    l(u) = r(l(u));
    r(v) = u;
    u = v;
    pushup(u);
    pushup(r(u));
}

// 左旋操作（Zag）
void zag(int& u) {
    int v = r(u);
    r(u) = l(r(u));
    l(v) = u;
    u = v;
    pushup(u);
    pushup(l(u));
}

// 插入操作
void insert(int& u, int key) {
    if (!u) u = new_node(key);
    else if (u(u).key == key) u(u).cnt ++ ;
    else if (u(u).key < key) {
        insert(r(u), key);
        if (u(r(u)).val > u(u).val) zag(u);
    } else {
        insert(l(u), key);
        if (u(l(u)).val > u(u).val) zig(u);
    }
    pushup(u);
}

// 删除操作
void remove(int& u, int key) {
    if (!u) return ;
    else if (u(u).key == key) {
        if (u(u).cnt > 1) u(u).cnt -- ;
        else {
            if (l(u) || r(u)) {
                if (!r(u) || u(l(u)).val > u(r(u)).val) {
                    zig(u);
                    remove(l(u), key);
                } else {
                    zag(u);
                    remove(r(u), key);
                }
            } else u = 0;
        }
    }
    else if (u(u).key > key) remove(l(u), key);
    else remove(r(u), key);
    pushup(u);
}

// 按键值查排名
int find_rank_by_val(int u, int key) {
    if (!u) return 1;
    else if (u(u).key == key) return u(l(u)).sz + 1;
    else if (u(u).key > key)  return find_rank_by_val(l(u), key);
    return u(l(u)).sz + u(u).cnt + find_rank_by_val(r(u), key);
}

// 按排名查键值
int find_val_by_rank(int u, int rank) {
    if (!u) return INF;
    else if (u(l(u)).sz >= rank) return find_val_by_rank(l(u), rank);
    else if (u(l(u)).sz + u(u).cnt >= rank) return u(u).key;
    return find_val_by_rank(r(u), rank - u(l(u)).sz - u(u).cnt);
}

// 查找前驱
int find_prev(int u, int key) {
    if (!u) return -INF;
    else if (u(u).key >= key) return find_prev(l(u), key);
    return max(u(u).key, find_prev(r(u), key));
} 

// 查找后继
int find_next(int u, int key) {
    if (!u) return INF;
    else if (u(u).key <= key) return find_next(r(u), key);
    return min(u(u).key, find_next(l(u), key));
}

int main() {
    build(); // 初始化树堆

    cin >> n;
    while (n -- ) {
        int opt, x;
        cin >> opt >> x;
        switch (opt) {
            case 1: insert(root, x); break;
            case 2: remove(root, x); break;
            case 3: cout << find_rank_by_val(root, x) - 1 << endl; break;
            case 4: cout << find_val_by_rank(root, x + 1) << endl; break;
            case 5: cout << find_prev(root, x) << endl; break;
            case 6: cout << find_next(root, x) << endl; break;
        }
    }

    return 0;
}
```

## 时间复杂度

| 操作               | 平均时间复杂度 | 说明                                                     |
| ------------------ | -------------- | -------------------------------------------------------- |
| 插入 `Insert`      | $O(log n)$     | 随机优先级确保树高为 $O(logn)$，遍历与旋转次数均为对数级 |
| 删除 `Delete`      | $O(logn)$      | 同理，调整过程（旋转）与遍历次数均为对数级               |
| 排名查询 `Rank`    | $O(logn)$      | 从根到叶遍历，路径长度为树高 $O(logn)$                   |
| 第 k 小查询 `k-th` | $O(logn)$      | 基于子树大小导航，路径长度为对数级                       |
| 前驱/后继查询      | $O(logn)$      | 遍历路径长度为树高，比较操作次数为常数级                 |
