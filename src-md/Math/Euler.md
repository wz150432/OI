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

## 3. 容斥原理证明欧拉函数通用公式

### 3.1 回顾容斥原理基本形式

对于有限集合 $A_1, A_2, \dots, A_r$，其并集的元素个数满足：

$$
|A_1 \cup A_2 \cup \cdots \cup A_r| = \sum_{1 \leq i \leq r} |A_i| - \sum_{1 \leq i < j \leq r} |A_i \cap A_j| + \sum_{1 \leq i < j < k \leq r} |A_i \cap A_j \cap A_k| - \cdots + (-1)^{m+1} \sum_{1 \leq i_1 < \cdots < i_m \leq r} |A_{i_1} \cap \cdots \cap A_{i_m}| + \cdots + (-1)^{r+1} |A_1 \cap \cdots \cap A_r|
$$

核心思想：先累加单个集合的大小，再减去两个集合的交集（避免重复计数），再加上三个集合的交集（修正过度减去），以此类推。

### 3.2 定义“与 $n$ 不互质的数的集合”

设 $n$ 的所有不同质因数为 $p_1, p_2, \dots, p_r$，定义集合：

$$
A_i = \{ x \in [1, n] \mid p_i \mid x \} \quad (i=1,2,\dots,r)
$$

即 $A_i$ 是“1 到 $n$ 中能被 $p_i$ 整除的数”的集合。

显然，与 $n$ 不互质的数都属于这些集合的并集（因为不互质意味着至少能被 $n$ 的一个质因数整除），即：

$$
\text{不与 } n \text{ 互质的数的个数} = |A_1 \cup A_2 \cup \cdots \cup A_r|
$$

而欧拉函数是“与 $n$ 互质的数的个数”，因此：

$$
\phi(n) = n - |A_1 \cup A_2 \cup \cdots \cup A_r| \tag{1}
$$

### 3.3 计算单个集合与集合交集的大小

要应用容斥原理，需先计算 $|A_i|$ 和 $|A_{i_1} \cap A_{i_2} \cap \cdots \cap A_{i_m}|$（ $m$ 个集合的交集）。

#### （1）单个集合的大小 $|A_i|$

$A_i$ 是 1 到 $n$ 中能被 $p_i$ 整除的数，这类数的形式为 $p_i, 2p_i, 3p_i, \dots, k p_i$，其中 $k p_i \leq n$。

因此最大的 $k$ 是 $\lfloor \frac{n}{p_i} \rfloor$。

又因为 $p_i$ 是 $n$ 的质因数（ $n = p_i^{k_i} \cdot \text{其他质因数}$ ），所以 $p_i \mid n$，即 $\lfloor \frac{n}{p_i} \rfloor = \frac{n}{p_i}$。

故：

$$
|A_i| = \frac{n}{p_i} \tag{2}
$$

#### （2） $m$ 个集合的交集大小 $|A_{i_1} \cap A_{i_2} \cap \cdots \cap A_{i_m}|$

交集 $A_{i_1} \cap \cdots \cap A_{i_m}$ 是“1 到 $n$ 中能同时被 $p_{i_1}, p_{i_2}, \dots, p_{i_m}$ 整除的数”的集合。

由于 $p_{i_1}, \dots, p_{i_m}$ 是互不相同的质数，它们的最小公倍数 $\text{lcm}(p_{i_1}, \dots, p_{i_m}) = p_{i_1} \cdot p_{i_2} \cdot \cdots \cdot p_{i_m}$ （质数互质，最小公倍数为乘积）。

因此，交集中的数是能被 $p_{i_1} p_{i_2} \dots p_{i_m}$ 整除的数，形式为 $k \cdot (p_{i_1} \dots p_{i_m})$，其中 $k \cdot (p_{i_1} \dots p_{i_m}) \leq n$。

同理，最大的 $k$ 是 $\lfloor \frac{n}{p_{i_1} \dots p_{i_m}} \rfloor$，而 $p_{i_1} \dots p_{i_m} \mid n$ （因为 $n$ 包含这些质因数），故：

$$
|A_{i_1} \cap \cdots \cap A_{i_m}| = \frac{n}{p_{i_1} p_{i_2} \dots p_{i_m}} \tag{3}
$$

### 3.4 代入容斥原理推导欧拉函数

将（2）（3）代入容斥原理公式，计算 $|A_1 \cup \cdots \cup A_r|$：

$$
\begin{aligned}
|A_1 \cup \cdots \cup A_r| &= \sum_{1 \leq i \leq r} \frac{n}{p_i} - \sum_{1 \leq i < j \leq r} \frac{n}{p_i p_j} + \sum_{1 \leq i < j < k \leq r} \frac{n}{p_i p_j p_k} - \cdots + (-1)^{r+1} \frac{n}{p_1 p_2 \dots p_r} \\
&= n \left( \sum_{1 \leq i \leq r} \frac{1}{p_i} - \sum_{1 \leq i < j \leq r} \frac{1}{p_i p_j} + \sum_{1 \leq i < j < k \leq r} \frac{1}{p_i p_j p_k} - \cdots + (-1)^{r+1} \frac{1}{p_1 p_2 \dots p_r} \right)
\end{aligned}
$$

将上式代入（1）式，计算 $\phi(n)$：

$$
\begin{aligned}
\phi(n) &= n - n \left( \sum \frac{1}{p_i} - \sum \frac{1}{p_i p_j} + \cdots + (-1)^{r+1} \frac{1}{p_1 \dots p_r} \right) \\
&= n \left[ 1 - \sum \frac{1}{p_i} + \sum \frac{1}{p_i p_j} - \sum \frac{1}{p_i p_j p_k} + \cdots + (-1)^r \frac{1}{p_1 p_2 \dots p_r} \right]
\end{aligned}
$$

### 3.5 关联乘积展开式

观察括号内的表达式，它恰好是乘积 $\prod_{i=1}^{r} \left(1 - \frac{1}{p_i}\right)$ 的展开式。

以 $r=2$ 为例：

$$
\left(1 - \frac{1}{p_1}\right) \left(1 - \frac{1}{p_2}\right) = 1 - \frac{1}{p_1} - \frac{1}{p_2} + \frac{1}{p_1 p_2}
$$

与括号内一致；

以 $r=3$ 为例：

$$
\left(1 - \frac{1}{p_1}\right) \left(1 - \frac{1}{p_2}\right) \left(1 - \frac{1}{p_3}\right) = 1 - \left( \frac{1}{p_1} + \frac{1}{p_2} + \frac{1}{p_3} \right) + \left( \frac{1}{p_1 p_2} + \frac{1}{p_1 p_3} + \frac{1}{p_2 p_3} \right) - \frac{1}{p_1 p_2 p_3}
$$

也与括号内一致。

一般地，对任意 $r$，有：

$$
\prod_{i=1}^{r} \left(1 - \frac{1}{p_i}\right) = 1 - \sum \frac{1}{p_i} + \sum \frac{1}{p_i p_j} - \cdots + (-1)^r \frac{1}{p_1 p_2 \dots p_r}
$$

因此，欧拉函数的通用公式最终得证：

$$
\phi(n) = n \cdot \prod_{i=1}^{r} \left(1 - \frac{1}{p_i}\right)
$$

### 3.6 验证示例

以 $n=6$ 为例：

$6$ 的质因数分解为 $2^1 \times 3^1$，代入公式得：

$$
\phi(6) = 6 \times \left(1 - \frac{1}{2}\right) \times \left(1 - \frac{1}{3}\right) = 6 \times \frac{1}{2} \times \frac{2}{3} = 2
$$

与定义一致（1 和 5 与 6 互质）。

以 $n=12$ 为例：

$12 = 2^2 \times 3^1$，代入公式得：

$$
\phi(12) = 12 \times \left(1 - \frac{1}{2}\right) \times \left(1 - \frac{1}{3}\right) = 12 \times \frac{1}{2} \times \frac{2}{3} = 4
$$

与实际情况一致（1, 5, 7, 11 与 12 互质）。

## 4. 计算单个欧拉函数的值

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



## 5. 使用欧拉筛法的高效计算

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
            if (i % primes[j] == 0) { // primes[j] 不是最小质因数了
                // 不是最小质因数说明已经乘过(primes[j] - 1) 只需要把n拓展乘上primes[j]即可
                phi[i * primes[j]] = primes[j] * phi[i];
                break;
            }
            // 是最小质因数
            // n乘上的primes[j]和因子项除的primes[j]抵消了,只用乘上(primes[j] - 1)即可
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