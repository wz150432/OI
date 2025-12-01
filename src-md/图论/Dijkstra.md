# Dijkstra算法

Dijkstra 算法是一种非负权图单源最短路算法。我们先将结点分成两个集合：已确定最短路长度的点集（记为 $S$ 集合）的和未确定最短路长度的点集（记为 $T$ 集合）。一开始所有的点都属于 $T$ 集合。 

1. 初始化  $d(start) = 0$，其他点的 $d$ 均为 $+\infty$。 然后重复这些操作：
2. 从 $T$ 集合中，选取一个最短路长度最小的结点，移到 $S$ 集合中。 
3. 对那些刚刚被加入 $S$ 集合的结点的所有出边执行松弛操作。 
4.  $T$ 集合为空，结束。

## 稠密图代码：

时间复杂度 $\Theta(V^2)$， $V$ 是节点数量。

```cpp
int dijkstra() {
    memset(d, 0x3f, sizeof d);
    d[1] = 0;
    for (int i = 1 ; i <= n ; ++ i) {
        int t = -1;
        for (int j = 1 ; j <= n ; ++ j)
            if (!vis[j] && (t == -1 || d[t] > d[j])) 
                t = j;
        
        vis[t] = 1;
        for (int j = 1 ; j <= n ; ++ j)
            if (!vis[j])
                d[j] = min(d[t] + g[t][j], d[j]);
    }

    if (d[n] == INF) return -1;
    return d[n];
}
```



## 稀疏图代码：

时间复杂度 $\Theta((V+E)logV)$，$E$ 是边的数量。

```cpp
int dijkstra() {
    priority_queue<PII, vector<PII>, greater<PII>> q;
    
    memset(d, 0x3f, sizeof d);
    d[1] = 0;
    q.push({0, 1});

    while (!q.empty()) {
        auto [dist, u] = q.top();
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        
        for (auto [v, w] : ve[u])
            if (d[v] > dist + w) {
                d[v] = dist + w;
                q.push({d[v], v});
            }
    }

    return d[n] == INF ? -1 : d[n];
}
```
