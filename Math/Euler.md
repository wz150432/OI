# 欧拉函数

## 1. 定义

欧拉函数 $\phi(n)$ 统计满足 $1 \leq k \leq n$ 且 $\gcd(k,n)=1$ 的整数 $k$ 的个数。

示例：

- $\phi(6) = 2$（1和5与6互质）
- $\phi(7) = 6$（1 - 6所有数都与质数7互质）

## 2. 关键公式

- 对于质数 $p$：$\phi(p) = p-1$
- 对于质数的幂 $p^k$：$\phi(p^k) = p^k - p^{k-1}$
- 对于互质的 $m,n$：$\phi(mn) = \phi(m)\phi(n)$
- 通用公式：如果 $n = p_1^{k_1}p_2^{k_2}...p_r^{k_r}$，那么： 
  $\phi(n) = n \prod_{i=1}^r \left(1-\frac{1}{p_i}\right)$

## 3. 计算单个欧拉函数的值

直接计算欧拉函数 $\phi(n)$，时间复杂度为 $O(\sqrt{n})$。

### C++ 实现

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

## 4. 使用欧拉筛法的高效计算

欧拉筛法（线性筛法）在筛法执行过程中利用质因数分解，在 $O(N)$ 时间内计算所有 $1 \leq n \leq N$ 的 $\phi(n)$ 值。

### C++ 实现

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

输出：

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