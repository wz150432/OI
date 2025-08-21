#include <iostream>
#include <cstring>

using namespace std;

const int N = 1010;
const int INF = 0x3f3f3f3f;

int n, m, q;
int d[N][N];

void floyd() {
    for (int k = 1; k <= n; k ++ )
        for (int i = 1; i <= n; i ++ )
            for (int j = 1; j <= n; j ++ )
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

int main() {
    cin >> n >> m >> q;

    memset(d, 0x3f, sizeof d);
    
    for (int i = 1; i <= n; i ++ ) d[i][i] = 0;
    
    while (m -- ) {
        int a, b, w;
        cin >> a >> b >> w;
        d[a][b] = min(d[a][b], w);
    }

    floyd();

    while (q -- ) {
        int a, b;
        cin >> a >> b;
        if (d[a][b] >= INF / 2) puts("impossible");
        else cout << d[a][b] << endl;
    }

    return 0;
}