#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int n, q;
int a[N], b[N];

int main() {
    cin >> n >> q;

    for (int i = 1 ; i <= n ;  i ++ ){
        cin >> a[i];
        b[i] = a[i] - a[i - 1];
    }

    while (q -- ) {
        int l, r, d;
        cin >> l >> r >> d;
        b[l] += d, b[r + 1] -= d;
    }

    for (int i = 1 ; i <= n ; i ++ ) {
        b[i] += b[i - 1];
        cout << b[i] << " " ;
    }

    return 0;
}