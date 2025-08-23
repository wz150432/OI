#include <iostream>
#include <queue>

using namespace std;

const int N = 1e5 + 10;

int n, m, cnt;
int a[N], d[N];
vector<int> ve[N];

void topsort() {
    queue<int> q;
    for (int i = 1 ; i <= n ; i ++ )
        if (!d[i])
            q.push(i);

    while (!q.empty()) {
        int u = q.front();
        a[ ++ cnt] = u;
        q.pop();
        for (int v : ve[u]) {
            d[v] -- ;
            if (!d[v])
                q.push(v);
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        ve[a].push_back(b);
        d[b] ++ ;
    }

    topsort();

    if (cnt != n) puts("Impossible");
    else {
        for (int i = 1; i <= n; i ++ ) 
            cout << a[i] << " " ;
    }

    return 0;
}