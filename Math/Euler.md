# Euler's Totient Function: A Concise Guide with Euler Sieve

## 1. Definition
Euler's Totient Function $\phi(n)$ counts integers $1 \leq k \leq n$ where $\gcd(k,n)=1$.  

Examples:
- $\phi(6) = 2$ (1, 5 are coprime with 6)
- $\phi(7) = 6$ (All 1-6 are coprime with prime 7)


## 2. Key Formulas
- For prime $p$: $\phi(p) = p-1$
- For prime power $p^k$: $\phi(p^k) = p^k - p^{k-1}$
- For coprime $m,n$: $\phi(mn) = \phi(m)\phi(n)$
- General formula: If $n = p_1^{k_1}p_2^{k_2}...p_r^{k_r}$, then:  
  $\phi(n) = n \prod_{i=1}^r \left(1-\frac{1}{p_i}\right)$


## 3. Efficient Calculation with Euler function value
Direct calculation of Euler's totient function $\phi(n)$ with $O(\sqrt{n})$ time complexity.

### C++ Implementation
```cpp
#include <iostream>

using namespace std;

int n;

int euler(int x) {
    int res = x;
    for (int i = 2; i <= x / i ; i ++ ) {
        if (x % i == 0) {
            while (x % i == 0) x /= i;
            res = res / i * (i - 1);
        }
    }
    if (x != 1) res = res / x * (x - 1);

    return res;
}

int main() {
    cin >> n;

    cout << euler(n);

    return 0;
}
```

## 4. Efficient Calculation with Euler Sieve
Euler Sieve (linear sieve) computes $\phi(n)$ for all $1 \leq n \leq N$ in $O(N)$ time by leveraging prime factorization during sieve execution.

### C++ Implementation
```cpp
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
```

Output:
```
phi(1) = 1
phi(2) = 1
phi(3) = 2
phi(4) = 2
phi(5) = 4
phi(6) = 2
phi(7) = 6
phi(8) = 4
phi(9) = 6
phi(10) = 4
```