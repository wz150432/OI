### Splay

这是一种比 Treap 更加常用的平衡树，而且也是其他数据结构的基础，感觉学起来还是比较简单的。



首先我们需要知道 Splay 有几个基础的操作：

1. 把一个节点转到一个点的下面
2. 左旋和右旋
3. 插入一个数字

其他的操作就是正常平衡树都有的操作



什么使得 Splay 的时间复杂度是 $\Theta (logN)$ 的呢？就是我们需要每次插入一个点的时候把他旋转到根节点。**值得注意的是我们常在左右两边设置两个哨兵保证边界问题**

具体证明请看 OI wiki



### 节点内需要存储的基本信息

```cpp
struct node {
    int p, val;
    int s[2], sz;
    
    void init(int _p, int _v) {
        p = _p;
        val = _v;
        sz = 1;
    }
};
```



### 旋转：

首先不得不说一下我们的左旋和右旋，现在的 OI 经过多年的进化已经可以用一个函数来进行两种旋转了，我之前都是写两个的 Zig 和 Zag 函数的。首先确定旋转并不影响中序遍历。

```cpp
void rotate(int x) {
	int y = tr[x].p, z = tr[y].p;
	int k = tr[y].s[1] == x;
	tr[x].p = z;
	tr[z].s[tr[z].s[1] == y] = x;
	tr[y].s[k] = tr[x].s[k ^ 1];
	tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y;
	tr[y].p = x;
	pushup(y), pushup(x);
}
```



### 找第 $k$ 大的数字

为什么我们能通过子树大小找到第 $k$ 大数。首先，一开始建树时子树大小可以直接判断出这个信息，因为建树是符合 BST 的规则。我们很容易发现找第 $k$ 大的数字也是按照中序查询的，由于旋转不影响中序遍历，所以正确。

```cpp
int find(int k) {
    int u = root;
    while (1) {
        if (tr[tr[u].s[0]].sz >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].sz + 1 == k) return u;
        else {
            k -= tr[tr[u].s[0]].sz + 1;
            u = tr[u].s[1];
        }
    }
    return -1;
}
```



### 插入

我们插入一个点最终要的就是把新加入的点直接旋转到根节点

```cpp
void insert(int v) {
    int u = root, p = 0;
    while (u) {
        p = u;
        u = tr[u].s[v > tr[u].val];
    }
    u = ++ idx;
    if (p) tr[p].s[v > tr[p].val] = u;
    tr[u].init(p, v);
    splay(u, 0);
}
```



### Splay 函数

Splay 函数就是 Splay 这个数据结构的精髓，我们可以通过这个函数把一个点旋转到一个点的下面，这时候我们需要分成两种情况，第一种情况，就是当这个节点是一条链的情况，我们需要旋转一次 $x$ 然后旋转一次他的父节点  $y$，如果是正常的情况我们只需要旋转两次 $x$ 就可以了。

```cpp
void splay(int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k) {
            if ((tr[z].s[1] == y) ^ (tr[y].s[1] == x)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if (!k) root = x;
}
```



我们当想要合并两个 splay 的时候用启发式合并能够做到 $\Theta(Nlog^2N)$ 的时间复杂度，启发式合并就是小的树合并在大的树上，插入时我们可以选择后序遍历，原因未知。

还有就是插入的时候如果空间允许的话最好不要复用节点，由于未知原因会跑的更慢。

```cpp
void dfs(int u, int b) {
    if (tr[u].s[0]) dfs(tr[u].s[0], b);
    if (tr[u].s[1]) dfs(tr[i].s[1], b);
    insert(tr[u].val. tr[u].id, b);
}
```



```cpp
void merge(int a, int b) {
    a = find(a), b = find(b);
    if (a != b) {
        if (tr[root[a]].sz > tr[root[b]].sz) swap(a, b);
        dfs(root[a], b);
        p[a] = b;
    }
}
```

