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