#include <iostream>

using namespace std;

typedef long long ll;

int a, b, p;

int mul(int a, int b, int) {
    int res = 0;
    for ( ; b ; b >>= 1) {
        if (b & 1) res = (ll)(res + a) % p;
        a = (ll)(a + a) % p;
    }
    return res;
}

int qpow(int a, int b, int p) {
    int res = 1;
    for ( ; b ; b >>= 1) {
        if (b & 1) res = mul(res, a, p);
        a = mul(a, a, p);
    }
    return res;
}

int main() {
    cin >> a >> b >> p;

    cout << qpow(a, b, p);

    return 0;
}