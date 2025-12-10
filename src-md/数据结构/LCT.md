# Link Cut Tree

一种用来解决动态树问题的非常巧妙的数据结构，用 Splay 维护实链，动态实现实链剖分。Splay 维护的实链是原树中的一条路径，中序遍历 Splay 得到关于原树深度的序列。（不用担心出现点深度相同的情况，因为一个父节点只会有一条实边）且 Splay 中的根节点的父节点指向原树中这条链的父亲节点。

值得注意的是 LCT 中 Splay 维护的实链的根节点认父节点，但是父亲却不认儿子，也就是说这是一条虚边。由于虚实边是我们自己选择的，所以才确保了 LCT 的灵活性。

**虚边**我们可以笼统的目前暂不关注的边，而**实边**是当前要高频操作的边。虚实边的概念保证了时间复杂度的同时，也处理的多叉树的情况（Splay 是二叉树）。

## 重要概念

实边：对于一个点连向它所有儿子的边，我们自己选择一条边进行剖分，我们称被选择的边为实边

虚边：不是实边的其他边

实链：由实边组成的链



## 核心操作

### splay

将 $x$ 转到 splay 的根节点。

```cpp
void splay(int x) {
    int cnt = 0, r = x;
    tmp[ ++ cnt] = r;
    while (!isRoot(r)) tmp[ ++ cnt] = r = tr[r].p;
    while (cnt) pushdown(tmp[cnt -- ]);
    while (!isRoot(x)) {
        int y = tr[x].p, z = tr[y].p;
        if (!isRoot(y)) {
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}
```



## access

建立一条从根到 $x$ 的实链，并把 $x$ 转到 Splay 中的根节点，原本的右子树不会消失，而是变成了虚边。这样就保证了根节点就是实链中点序号最大的。强制让 $x$ 无实右儿子。

```cpp
void access(int x) {
    int y = 0, z = x;
    while (x) {
        splay(x);
        tr[x].s[1] = y;
        pushup(x);
        y = x;
        x = tr[x].p;
    }
    splay(z);
}
```



## isRoot

判断 $x$ 是不是其所在实链的根节点，根据定义没有父节点指向的节点就是虚边，而两个实链连接的方式就是通过一个虚边和一个实链的根节点。

```cpp
void isRoot(int x) {
    return tr[tr[x].p].s[0] != x && tr[tr[x].p].s[1] != x;
}
```



## makeRoot

使得 $x$ 成为其所在原树的根节点，注意 Splay 中的根节点和原树的根节点树不同。Splay 的结构仅仅改变中序遍历，但是不影响父子关系，比如就算 access 后把 $x$ 转到 Splay 的根节点，但是 $tr_x$ 的 $p$ 还是原来的 $p$。所以 reverse 才能让 $x$ 变成原树的根，因为我们 access 只包含 $x$ 到 $r$ 的路径不包含多余，所以 $x$ 一定是原树中深度最深的。

```cpp
void makeRoot(int x) {
    access(x);
    pushrev(x);
}
```



## findRoot

找到 $x$ 所在的原树的根节点，根节点的深度是最浅的，根据中序遍历应该在 Splay 最左侧的地方。

```cpp
int findRoot(int x) {
    access(x);
    while (tr[x].s[0]) {
        pushdown(x);
        x = tr[x].s[0];
    }
    splay(x);
    return x;
}
```



## link

在 $x$ 之间 $y$ 连一条边（如果不连通），当且仅当 $y$ 是一个独立其外的点，没有实边或者虚边连接以 $x$ 作为根的树。

```cpp
void link(int x, int y) {
    makeRoot(x);
    if (findRoot(y) != x) tr[x].p = y;
}
```



## cut

删除 $x$ 之间 $y$ 的一条边（如果存在），$y$ 必须是 $x$ 的后继才行。

```cpp
void cut(int x, int y) {
    makeRoot(x);
    if (findRoot(y) == x && tr[y].p == x && !tr[y].s[0]) {
        tr[x].s[1] = tr[y].p = 0;
        pushup(x);
    }
}
```



## split

建立 $x$, $y$ 路径的实链

```cpp
void split(int x, int y) {
    makeRoot(x);
    access(y); 
}
```





