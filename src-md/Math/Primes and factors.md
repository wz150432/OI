# 质数与约数

在信息学竞赛中，数论模块的核心在于对质数性质的理解与应用。本文将从最朴素的质数判定方法开始，逐步优化算法，并延伸至质因数分解及因子定理的推导与实现。

## 一、质数判定：从暴力到优化

### 1.1 质数的定义
质数（素数）是指大于 $1$ 的自然数中，除了 $1$ 和自身外没有其他正因数的数。即对于 $n > 1$，若不存在 $2 \leq d < n$ 使得 $d \mid n$，则 $n$ 为质数。

### 1.2 暴力判定算法
最直接的实现方式是根据定义，枚举所有可能的因子进行检查：

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;

bool isPrime(int x) 
    if (x < 2) return false;
    for (int i = 2; i <= n; i ++ )
        if (x % i == 0) 
            return false;
    return true;
}

int main() {
    cin >> n;
    if (isPrime(n)) cout << n << " is prime." << endl;
    else cout << n << " is not prime." << endl;
    
    return 0;
}
```

**时间复杂度**：$O(n)$。当 $x$ 达到 $10^6$ 时，单次判定需百万次循环，在多组测试数据下效率极低。

### 1.3 优化判定算法
通过数学性质优化枚举范围：若 $n$ 是合数，则其最小质因子一定不超过 $\sqrt{n}$。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;

bool isPrime(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i ++ )
        if (x % i == 0) 
            return false;
    return true;
}

int main() {
    cin >> n;
    if (isPrime(n)) cout << n << " is prime." << endl;
    else cout << n << " is not prime." << endl;
    
    return 0;
}
```

**正确性证明**

反证法：假设$n$是合数且所有因子均大于 $\sqrt{n}$，则任取因子对 $(d, n/d)$，必有 $d > \sqrt{n}$ 且 $n/d > \sqrt{n}$，相乘得$d \times (n/d) = n > \sqrt{n} \times \sqrt{n} = n$，矛盾。故合数必有不超过 $\sqrt{n}$ 的因子。

**时间复杂度**：$O(\sqrt{n})$，较暴力法大幅优化。例如 $x = 10^6$ 时，枚举次数从100万降至1000次。

### 1.4 进一步优化思路
对于更大的数（如 $10^{18}$），需使用Miller-Rabin概率性测试（结合费马小定理与二次探测），时间复杂度可降至 $O(k \log^3 n)$（$k$为测试轮数），但基础场景下 $O(\sqrt{n})$ 算法已足够。

## 二、质因数分解：算术基本定理的应用

### 2.1 算术基本定理
任何大于1的自然数$n$都可唯一分解为： 
$n = p_1^{a_1} \times p_2^{a_2} \times \dots \times p_k^{a_k}$
其中$p_1 < p_2 < \dots < p_k$为质数，$a_1, a_2, \dots, a_k$为正整数（指数）。

### 2.2 分解算法实现
基于质数判定的优化思路，枚举可能的质因子并计算指数：

```cpp
#include <bits/stdc++.h>

#define p first
#define s second

using namespace std;

const int N = 210;

typedef pair<int, int> PII;

int t, n, cnt;
PII prime[N];

void factorization(int n) {
    cnt = 0;
    for (int i = 2; i <= n / i; i ++ ) {
        if (n % i == 0) {
            prime[cnt] = {i, 0};
            while (n % i == 0) {
                prime[cnt].s ++ ;
                n /= i;
            }
            cnt ++ ;
        }
    }

    if (n != 1) prime[cnt ++ ] = {n, 1};
}

int main() {
    cin >> t;
    
    while (t -- ) {
        cin >> n;
        factorization(n);

        for (int i = 0; i < cnt; i ++ )
            cout << prime[i].p << "^" << prime[i].s << endl;

        puts("");
    }

    return 0;
}
```

**示例**：分解 $n = 12$ 时，过程为：  

1. $i=2$：$12 \% 2 = 0$，指数增至2（$12 = 2^2 \times 3$），$n$变为3  
2. $i=3$：$i \times i = 9 > 3$，循环结束  
3. 剩余$n=3 \neq 1$，添加质因子$(3, 1)$
最终结果：$2^2 \times 3^1$

**时间复杂度**：$O(\sqrt{n})$，实际运行中因$n$不断被除，效率优于理论值。

## 三、因子数与因子和定理

基于质因数分解结果，可推导出计算因子总数和总和的公式，这是OI中解决数论问题的关键工具。

### 3.1 因子数定理
**定理**：若 $n = p_1^{a_1} \times p_2^{a_2} \times \dots \times p_k^{a_k}$，则$n$的正因子总数为： 
$d(n) = (a_1 + 1) \times (a_2 + 1) \times \dots \times (a_k + 1)$

**证明**： 
每个因子可表示为 $p_1^{b_1} \times p_2^{b_2} \times \dots \times p_k^{b_k}$，其中 $0 \leq b_i \leq a_i$。 
对每个 $b_i$，有 $a_i + 1$ 种选择（从 $0$ 到 $a_i$），根据乘法原理，总因子数为各选择数的乘积。

### 3.2 因子和定理
**定理**：若 $n = p_1^{a_1} \times p_2^{a_2} \times \dots \times p_k^{a_k}$，则所有正因子之和为： 
$\sigma(n) = \prod_{i=1}^k \left( 1 + p_i + p_i^2 + \dots + p_i^{a_i} \right)$
利用等比数列求和公式简化： 
$\sigma(n) = \prod_{i=1}^k \frac{p_i^{a_i + 1} - 1}{p_i - 1}$

**证明**： 
展开乘积式时，每项为 $p_1^{b_1}p_2^{b_2}\dots p_k^{b_k}$（$0 \leq b_i \leq a_i$），恰好是所有因子，故总和为所有项之和。

### 3.3 代码实现（含模运算）
结合快速幂与模逆元优化计算：

```cpp
#include <bits/stdc++.h>

#define p first
#define s second

using namespace std;

const int N = 210;
const int MOD = 1e9 + 7;

typedef pair<int, int> PII;

int t, n, cnt;
PII prime[N];

void factorization(int n) {
    cnt = 0;
    for (int i = 2; i <= n / i; i ++ ) {
        if (n % i == 0) {
            prime[cnt] = {i, 0};
            while (n % i == 0) {
                prime[cnt].s ++ ;
                n /= i;
            }
            cnt ++ ;
        }
    }

    if (n != 1) prime[cnt ++ ] = {n, 1};
}

int qpow(int a, int b) {
    int res = 1;
    for ( ; b ; b >>= 1) {
        if (b & 1) res = (1ll * res * a) % MOD;
        a = (1ll * a * a) % MOD;
    }
    return res;
}

int main() {
    cin >> t;
    
    while (t -- ) {
        cin >> n;
        factorization(n);

        long long sum = 1, num = 1;
        for (int i = 0; i < cnt; i ++ ) {
            auto [p, s] = prime[i];
            sum = (sum * (qpow(p, s + 1) - 1 + MOD) % MOD * qpow(p - 1, MOD - 2) % MOD) % MOD;
            num = (num * (s + 1)) % MOD;
        }

        printf("The sum of factors is %lld and the number of factors is %lld\n", sum, num);
    }

    return 0;
}
```

**关键技巧**：  

- 模意义下的除法通过费马小定理转化为乘法：$a / b \equiv a \times b^{MOD-2} \mod MOD$（要求$MOD$为质数）。  
- 快速幂将等比数列求和的时间复杂度降至 $O(\log s)$。



## 例题

[P1075](https://www.luogu.com.cn/problem/P1075)

[B3715](https://www.luogu.com.cn/problem/B3715)

[约数个数](https://www.acwing.com/problem/content/872/)

[约数之和](https://www.acwing.com/problem/content/873/)



## 推荐的练习

[P1072](https://www.luogu.com.cn/problem/P1072)

[P1463](https://www.luogu.com.cn/problem/P1463)
