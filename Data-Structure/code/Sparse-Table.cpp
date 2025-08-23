#include <iostream>

using namespace std;

const int N = 2e5 + 10, M = 20;

int n, q;
int a[N];
int f[N][M];

int RMQ(int l, int r) {
    int k = floor(log(r - l + 1) / log(2));
    return max(f[l][k], f[r - (1 << k) + 1][k]);
}

int main() {
    cin >> n;

    for (int i = 1; i <= n; i ++ ) cin >> a[i];

    int k = floor(log(n) / log(2));
    for (int j = 0 ; j <= k; j ++ )
        for (int i = 1; i + (1 << j) - 1 <= n; i ++ ) {
            if (!j) f[i][j] = a[i];
            else f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }

    cin >> q;

    while (q -- ) {
        int l, r;
        cin >> l >> r;
        cout << RMQ(l, r) << endl;
    }

    return 0;
}