#include <iostream>
#include <cstring>

using namespace std;

const int N = 510;
const int M = 1e4 + 10;
const int INF = 0x3f3f3f3f;

int n, m, k;
int d[N], tmp[N];

struct node {
    int a, b, w;
}g[M];

int bellman_ford() {
    memset(d, 0x3f, sizeof d);
    d[1] = 0;

    for (int i = 1; i <= k; i ++ ) {
        memcpy(tmp, d, sizeof d);
        for (int j = 1; j <= m; j ++ ) {
            int dist = tmp[g[j].a] + g[j].w;
            if (dist < d[g[j].b])
                d[g[j].b] = dist;
        }
    }

    return d[n];
}

int main() {
    cin >> n >> m >> k;

    for (int i = 1; i <= m; i ++ ) {
        int a, b, c;
        cin >> a >> b >> c;
        g[i] = {a, b, c};
    }

    int t = bellman_ford();

    if (t >= INF / 2) puts("Impossible");
    else cout << d[n] << " " ;

    return 0;
}