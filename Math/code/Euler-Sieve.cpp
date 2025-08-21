#include <iostream>

using namespace std;

const int N = 1e5 + 10, M = 5010;

int n, cnt;
bool vis[N];
int primes[N];

void sieve(int n) {
    vis[1] = 1;
    for (int i = 2; i <= n; i ++ ) {
        if (!vis[i]) primes[ ++ cnt] = i;
        for (int j = 1; primes[j] <= n / i ; j ++ ) {
            vis[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    cin >> n;

    sieve(n);

    for (int i = 1; i <= cnt; i ++ ) cout << primes[i] << endl;

    return 0;
}