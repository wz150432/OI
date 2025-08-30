# Dijkstra算法

**Dijkstra **算法是一种基础的图遍历和最短路径查找算法，自1956年由艾兹赫尔·戴克斯特拉（Edsger W. Dijkstra）提出以来，彻底改变了计算机科学领域。这一强大算法能高效地找到带非负边权图中从起始节点到所有其他节点的最短路径。

## 1. 工作原理

将结点分成两个集合：已确定最短路长度的点集（记为 $S$ 集合）的和未确定最短路长度的点集（记为 $T$ 集合）。一开始所有的点都属于 $T$ 集合。 

1. 初始化  $d(start) = 0$，其他点的 $d$ 均为 $+\infty$。 然后重复这些操作：
2. 从 $T$ 集合中，选取一个最短路长度最小的结点，移到 $S$ 集合中。 
3. 对那些刚刚被加入 $S$ 集合的结点的所有出边执行松弛操作。 
4.  $T$ 集合为空，结束。

## 2. 代码实现

以下是普通的 **Dijkstra** 算法：

```cpp
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

const int N = 510, INF = 0x3f3f3f3f;

int n, m;		// 顶点数n, 边数m
int g[N][N]; 	// 邻接矩阵
int d[N];		// 存储源点到各顶点的最短距离
bool vis[N];	// 标记是否已加入集合S

int dijkstra() {
    // 初始化所有距离为无穷大
    memset(d, 0x3f, sizeof d);
	
    // 让起点到自己的距离为0
    d[1] = 0;
    for (int i = 1 ; i <= n ; i ++ ) {
        // 找到目前集合T中最小的边
        int t = -1;
        for (int j = 1 ; j <= n ; j ++ )
            if (!vis[j] && (t == -1 || d[t] > d[j])) 
                t = j;
		//将点t加入集合S
        vis[t] = 1;

        // 对所有出边进行松弛操作
        for (int j = 1 ; j <= n ; j ++ )
            if (!vis[j])
                d[j] = min(d[t] + g[t][j], d[j]);
    }

    if (d[n] == INF) return -1;
    return d[n];
}

int main() {
    cin >> n >> m;

    memset(g, 0x3f, sizeof g);

    for (int i = 1 ; i <= m ; i ++ ) {
        int a, b, w;
        cin >> a >> b >> w;
        g[a][b] = min(w, g[a][b]);
    }

    cout << dijkstra();

    return 0;
}
```



以下是使用优先队列的 **Dijkstra **算法：

```cpp
#include <iostream>
#include <cstring>
#include <queue> 
#include <vector> // 其实queue里面包含了vector头文件

using namespace std;

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

typedef pair<int, int> PII;

int n, m;               // 顶点数n, 边数m
int d[N];               // 存储源点到各顶点的最短距离
bool vis[N];            // 标记是否已加入集合S
vector<PII> ve[N];      // 邻接表存储图结构

int dijkstra() {
    // 创建最小堆优先队列，按距离从小到大排序
    priority_queue<PII, vector<PII>, greater<PII>> q;
    
    // 初始化所有距离为无穷大
    memset(d, 0x3f, sizeof d);
    
    // 设置起点距离为0，并加入队列
    d[1] = 0;
    q.push({0, 1});

    while (!q.empty()) {
        // 找到目前集合T中最小的边
        auto [dist, u] = q.top();
        q.pop();
        
        // 如果该顶点已经是集合S的元素，跳过
        if (vis[u]) continue;
        
        //将当前顶点加入集合S
        vis[u] = 1;
        
        // 遍历当前顶点的所有出边
        for (auto [v, w] : ve[u]) {
            // 松弛操作：如果找到更短的路径
            if (d[v] > dist + w) {
                d[v] = dist + w;    // 更新距离
                q.push({d[v], v});  // 将新距离加入队列
            }
        }
    }

    // 返回终点n的最短距离，若不可达返回-1
    return d[n] == INF ? -1 : d[n];
}

int main() {
    cin >> n >> m;

    // 构建图的邻接表
    while (m -- ) {
        int a, b, w;
        cin >> a >> b >> w;
        ve[a].push_back({b, w}); // 添加从a到b的边，权值为w
    }

    int t = dijkstra();
    if (t == -1) puts("Impossible");
    else cout << t;

    return 0;
}
```

## 3.时间复杂度分析

**Dijkstra** 算法的时间复杂度取决于所使用的数据结构：

- 朴素做法： $O(V^2)$，其中 $V$ 是顶点数

- 使用二叉堆：$O((V + E) log V)$，其中 $E$ 是边数
- 使用斐波那契堆：$O(V log V + E)$（理论最优但实际较少使用）

## 4.局限性与替代方案

虽然功能强大，但 **Dijkstra** 算法存在以下局限：

- 无法处理带负边权的图
- 仅能查找单源最短路径

对于带负权重的图，**bellman-ford** 算法是更好的选择。对于查找所有节点对之间的最短路径，根据图结构可选择弗洛伊德-沃舍尔算法或从每个节点运行 **Dijkstra** 算法。
