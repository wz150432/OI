# Dijkstra's Algorithm: A Comprehensive Guide

Dijkstra's algorithm is a fundamental graph traversal and shortest path-finding algorithm that has revolutionized the field of computer science since its conception by Edsger W. Dijkstra in 1956. This powerful algorithm efficiently finds the shortest path from a starting node to all other nodes in a graph with non-negative edge weights.

## How Dijkstra's Algorithm Works

At its core, Dijkstra's algorithm operates on a greedy principle, always expanding the shortest known path first. Here's a step-by-step breakdown of its operation:

1. Initialize a priority queue to keep track of nodes to visit
2. Set the distance to the starting node as 0 and all other nodes as infinity
3. While the priority queue is not empty:
   - Extract the node with the smallest known distance
   - For each neighbor of this node, calculate the tentative distance
   - If this tentative distance is less than the currently known distance, update it
4. Once the queue is empty, we have the shortest paths from the start to all nodes

## Implementation Example

Here's a cpp implementation of Dijkstra's algorithm using a priority queue:

```cpp
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

typedef pair<int, int> PII;

int n, m;
int d[N];
bool vis[N];
vector<PII> ve[N];

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
        for (auto [v, w] : ve[u]) {
            if (d[v] > dist + w) {
                d[v] = dist + w;
                q.push({d[v], v});
            }
        }
    }

    return d[n] == INF ? -1 : d[n];
}

int main() {
    cin >> n >> m;

    while (m -- ) {
        int a, b, w;
        cin >> a >> b >> w;
        ve[a].push_back({b, w});
    }

    int t = dijkstra();
    if (t == -1) puts("Impossible");
    else cout << t;

    return 0;
}
```


## Time Complexity Analysis

The time complexity of Dijkstra's algorithm depends on the data structures used:

- With a binary heap: $O((V + E) log V)$, where V is the number of vertices and E is the number of edges
- With a Fibonacci heap: $O(V log V + E)$ (theoretically optimal but rarely used in practice)

The algorithm performs best on sparse graphs where E is much smaller than V².

## Limitations and Alternatives

While powerful, Dijkstra's algorithm has limitations:

- It cannot handle graphs with negative edge weights
- It finds shortest paths from a single source only

For graphs with negative weights, Bellman-Ford algorithm is a better choice. For finding shortest paths between all pairs of nodes, Floyd-Warshall algorithm or running Dijkstra's from each node may be appropriate depending on the graph structure.

## Recommended Exercises

