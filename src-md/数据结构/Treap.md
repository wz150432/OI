# Treap

这是一种将 BST 和 Heap 结合的一种平衡树。随机的堆值确保时间复杂度为 $\Theta(log n)$ ，避免了斜树的最坏情况，每个阶段需要同时满足 BST 和 Heap 的性质。  



### 节点的基本信息

```cpp
struct treap {
    int s[2];    // 左右孩子指针
    int key, val; // 二叉搜索树键值与堆优先级
    int cnt, sz;  // 重复计数与子树大小
} tr[N];
```


### 旋转操作:
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



## 例题

[P3369](https://www.luogu.com.cn/problem/P3369)
