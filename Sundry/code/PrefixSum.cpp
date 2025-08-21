#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int n, q;
int a[N];
long long sum[N];

int main() {
    cin >> n >> q;

    for (int i = 1 ; i <= n ;  i ++ ){
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }

    while (q -- ) {
        int l, r;
        cin >> l >> r;
        cout << sum[r] - sum[l - 1] << endl;
    }

    return 0;
}