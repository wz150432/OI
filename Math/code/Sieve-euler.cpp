#include <cstdio>

using namespace std;

const int N = 1e5 + 10, M = 5010;

int n, cnt;
int primes[M], phi[M];
bool vis[N];

void sieve_euler(int n) {
    vis[1] = phi[1] = 1;
    for (int i = 2 ; i <= n ; i ++ ) {
        if (!vis[i]) {
            primes[ ++ cnt] = i;
            phi[i] = i - 1;
        }

        for (int j = 1 ; primes[j] <= n / i ; j ++ ) {
            vis[i * primes[j]] = 1;
            if (i % primes[j] == 0) {
                phi[i * primes[j]] = primes[j] * phi[i];
                break;
            }
            phi[i * primes[j]] = (primes[j] - 1) * phi[i];
        }
    }
}

int main() {
    scanf("%d", &n);

    sieve_euler(n);

    for (int i = 1; i <= n; i ++ ) 
        printf("phi(%d) = %d\n", i, phi[i]);

    return 0;
}