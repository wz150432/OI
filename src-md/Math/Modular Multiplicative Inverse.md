# 模逆元精讲

在信息学竞赛（OI）中，模逆元是解决“分数取模”问题的核心工具——当需要计算 $\frac{a}{b} \mod m$ 时，直接除法无法在模意义下进行，此时需将其转化为 $a \times b^{-1} \mod m$（其中 $b^{-1}$ 是 $b$ 模 $m$ 的逆元）。本文将从**完全剩余系、缩系**的基础概念出发，严格证明欧拉定理与小费马定理，再详细讲解拓展欧几里得求逆元的原理，最后推导 $O(n)$ 预处理逆元的公式，帮你彻底掌握模逆元。

## 一、基础概念：理解逆元的“前世今生”

在讲定理前，必须先明确三个核心概念：**模逆元**、**完全剩余系**、**缩系（简化剩余系）**，这是后续证明的基石。

### 1.1 模逆元的定义与存在条件

若整数 $a$ 和 $m$ 满足 $\gcd(a, m) = 1$（即 $a$ 与 $m$ 互质），则存在唯一的整数 $x$ 使得： 
$a \times x \equiv 1 \pmod{m}$ 
此时称 $x$ 为 $a$ 模 $m$ 的**乘法逆元**，记为 $a^{-1} \mod m$。

> 关键结论：$a$ 模 $m$ 的逆元存在 **当且仅当** $\gcd(a, m) = 1$。 
> 反证：若 $\gcd(a, m) = d > 1$，假设逆元 $x$ 存在，则 $a x = k m + 1$。两边除以 $d$ 得 $\frac{a}{d}x = k \frac{m}{d} + \frac{1}{d}$，左边是整数，右边不是整数，矛盾。

### 1.2 完全剩余系（Complete Residue System, CRS）

模 $m$ 的**完全剩余系**是指由 $m$ 个整数构成的集合，其中每个整数模 $m$ 的余数互不相同，且恰好覆盖 $0, 1, 2, ..., m-1$。  

例如：$m=5$ 的一个完全剩余系是 $\{0,1,2,3,4\}$，也可以是 $\{5,6,7,8,9\}$（模 5 后余数仍不重复且覆盖所有可能）。

**核心性质**：若 $S$ 是模 $m$ 的完全剩余系，且 $\gcd(k, m) = 1$，则 $\{k \times s + t \mid s \in S\}$（$t$ 为任意整数）也是模 $m$ 的完全剩余系。 
（通俗说：对完全剩余系中每个元素乘一个与 $m$ 互质的数，再加任意数，结果仍是完全剩余系）

### 1.3 缩系（简化剩余系，Reduced Residue System, RRS）

模 $m$ 的**缩系**是完全剩余系中所有与 $m$ 互质的元素构成的子集。  

例如：$m=5$ 的完全剩余系 $\{0,1,2,3,4\}$ 中，与 5 互质的元素是 $\{1,2,3,4\}$，因此这是 $m=5$ 的一个缩系；$m=6$ 的缩系是 $\{1,5\}$（$1$ 和 $5$ 与 $6$ 互质）。

缩系的大小由**欧拉函数** $\phi(m)$ 定义：$\phi(m)$ 表示 $1 \sim m$ 中与 $m$ 互质的整数个数，因此缩系恰好有 $\phi(m)$ 个元素。

**核心性质**：若 $S$ 是模 $m$ 的缩系，且 $\gcd(k, m) = 1$，则 $\{k \times s \mod m \mid s \in S\}$ 也是模 $m$ 的缩系。 
（证明：① 因 $\gcd(k, m)=1$ 且 $\gcd(s, m)=1$，故 $\gcd(k s, m)=1$，元素仍在缩系中；② 若 $k s_1 \equiv k s_2 \pmod{m}$，则 $s_1 \equiv s_2 \pmod{m}$（$k$ 与 $m$ 互质可约去），元素互不重复，因此是缩系）。

## 二、欧拉定理：逆元存在的理论基石

欧拉定理是连接“幂运算”与“逆元”的关键，其证明完全依赖缩系的性质。

### 2.1 欧拉定理的表述

若 $\gcd(a, m) = 1$，则： 
$a^{\phi(m)} \equiv 1 \pmod{m}$  

其中 $\phi(m)$ 是欧拉函数，$\phi(m) = 1\sim m$ 中与 $m$ 互质的数的个数。

### 2.2 基于缩系的严格证明

设模 $m$ 的一个缩系为 $S = \{r_1, r_2, ..., r_{\phi(m)}\}$（共 $\phi(m)$ 个元素）。 
由缩系的核心性质：因 $\gcd(a, m) = 1$，集合 $T = \{a r_1 \mod m, a r_2 \mod m, ..., a r_{\phi(m)} \mod m\}$ 也是模 $m$ 的缩系。

既然 $S$ 和 $T$ 都是模 $m$ 的缩系，它们本质是**同一组元素的不同排列**（缩系元素唯一且个数固定）。因此，两组元素的乘积模 $m$ 相等： 
$r_1 \times r_2 \times ... \times r_{\phi(m)} \equiv (a r_1) \times (a r_2) \times ... \times (a r_{\phi(m)}) \pmod{m}$

右边整理得：$a^{\phi(m)} \times (r_1 \times r_2 \times ... \times r_{\phi(m)}) \pmod{m}$。 
将左右两边的“缩系元素乘积”记为 $P = r_1 r_2 ... r_{\phi(m)}$，则等式变为： 
$P \equiv a^{\phi(m)} \times P \pmod{m}$

因 $P$ 中每个 $r_i$ 与 $m$ 互质，故 $P$ 与 $m$ 互质（互质数的乘积仍互质）。根据“模运算消去律”（若 $\gcd(P, m)=1$，则 $P x \equiv P y \pmod{m} \implies x \equiv y \pmod{m}$），两边约去 $P$ 得： 
$1 \equiv a^{\phi(m)} \pmod{m}$  

欧拉定理得证！

### 2.3 欧拉定理与逆元的关系

由欧拉定理 $a^{\phi(m)} \equiv 1 \pmod{m}$，可变形为： 
$a \times a^{\phi(m)-1} \equiv 1 \pmod{m}$  

对比逆元的定义 $a \times x \equiv 1 \pmod{m}$，可得： 
$a^{-1} \equiv a^{\phi(m)-1} \pmod{m}$  

这说明：当 $\gcd(a, m)=1$ 时，$a$ 的逆元可通过计算 $a$ 的 $\phi(m)-1$ 次幂模 $m$ 得到——这就是“快速幂求逆元”的理论依据。

### 2.4代码实现

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, p;

int qpow(int a, int b) {
    int res = 1;
    for (; b ; b >>= 1) {
        if (b & 1) res = 1ll * res * a % p;
        a = 1ll * a * a % p;
    }
    return res;
}

int get_euler(int n) {
    int res = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            res = res / i * (i - 1);
        }
    }
    if (n > 1) res = res / n * (n - 1);
    return res;
}

int main() {
    cin >> n >> p;
    cout << qpow(n, get_euler(p) - 1) << endl;

    return 0;
}
```



## 三、小费马定理：欧拉定理的特殊情况

当 $m$ 是**质数**时，欧拉函数 $\phi(m)$ 有更简单的形式，此时欧拉定理简化为小费马定理，是 OI 中最常用的逆元求解工具之一。

### 3.1 小费马定理的表述

若 $p$ 是质数，且 $\gcd(a, p) = 1$（即 $a$ 不是 $p$ 的倍数），则： 
$a^{p-1} \equiv 1 \pmod{p}$

### 3.2 证明：基于欧拉定理的特例

因 $p$ 是质数，$1\sim p$ 中与 $p$ 互质的数是 $1, 2, ..., p-1$，共 $p-1$ 个，故 $\phi(p) = p-1$。 
代入欧拉定理 $a^{\phi(p)} \equiv 1 \pmod{p}$，直接得： 
$a^{p-1} \equiv 1 \pmod{p}$  

小费马定理得证！

### 3.3 小费马定理求逆元

同理，将小费马定理变形： 
$a \times a^{p-2} \equiv 1 \pmod{p}$  

因此，当 $p$ 是质数时，$a$ 的逆元为： 
$a^{-1} \equiv a^{p-2} \pmod{p}$  

例如：求 $3$ 模 $7$ 的逆元，计算 $3^{7-2} = 3^5 = 243$，$243 \mod 7 = 243 - 34 \times 7 = 243 - 238 = 5$，验证 $3 \times 5 = 15 \equiv 1 \pmod{7}$，正确。

### 3.4 代码实现

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, p;

int qpow(int a, int b) {
    int res = 1;
    for (; b ; b >>= 1) {
        if (b & 1) res = 1ll * res * a % p;
        a = 1ll * a * a % p;
    }
    return res;
}

int main() {
    cin >> n >> p;
    cout << qpow(n, p - 2) << endl;

    return 0;
}
```



## 四、拓展欧几里得算法：不依赖质数的逆元求解

欧拉/小费马定理求逆元需计算幂运算（快速幂 $O(log m)$），但拓展欧几里得算法（`Exgcd`）可直接求解逆元，且**不要求 $m$ 是质数**，只需 $\gcd(a, m)=1$。

### 4.1 拓展欧几里得算法的核心：求解线性方程

欧几里得算法（辗转相除法）用于求 $\gcd(a, b)$，而拓展欧几里得算法在此基础上，还能求解满足以下方程的整数解 $(x, y)$：
$a x + b y = \gcd(a, b)$  

**定理**：方程 $a x + b y = c$ 有解当且仅当 $\gcd(a, b) \mid c$（即 $c$ 是 $\gcd(a, b)$ 的倍数）。

### 4.2 拓展欧几里得的递归证明与实现

我们通过递归推导拓展欧几里得的解：

#### Base Case（递归终止条件）
当 $b = 0$ 时，$\gcd(a, 0) = a$，此时方程变为 $a x + 0 \times y = a$，显然解为 $x=1, y=0$（或 $y$ 为任意整数，通常取 $y=0$）。

#### 递归步骤
假设我们已求出方程 $b x_1 + (a \mod b) y_1 = \gcd(b, a \mod b)$ 的解 $(x_1, y_1)$。 
由欧几里得算法，$\gcd(a, b) = \gcd(b, a \mod b)$，因此： 
$b x_1 + (a \mod b) y_1 = \gcd(a, b)$  

注意到 $a \mod b = a - \left\lfloor \frac{a}{b} \right\rfloor \times b$（$\left\lfloor \frac{a}{b} \right\rfloor$ 表示 $a$ 除以 $b$ 的商，即代码中的 `a//b`），代入上式： 
$b x_1 + \left( a - \left\lfloor \frac{a}{b} \right\rfloor \times b \right) y_1 = \gcd(a, b)$  

展开并整理含 $a$ 和 $b$ 的项： 
$a y_1 + b \left( x_1 - \left\lfloor \frac{a}{b} \right\rfloor \times y_1 \right) = \gcd(a, b)$  

对比原方程 $a x + b y = \gcd(a, b)$，可得原方程的解为： 
$x = y_1, \quad y = x_1 - \left\lfloor \frac{a}{b} \right\rfloor \times y_1$  

这就完成了递归推导——通过求解子问题的解 $(x_1, y_1)$，可反推出原问题的解 $(x, y)$。

### 4.3 用拓展欧几里得求逆元

逆元的定义是：找到 $x$ 使得 $a x \equiv 1 \pmod{m}$，即存在整数 $k$ 使得 $a x = k m + 1$，整理为： 
$a x - m k = 1$  

令 $y = -k$，则方程变为 $a x + m y = 1$。  

根据拓展欧几里得的定理：  
- 若 $\gcd(a, m) = 1$，则方程有解，此时 $x$ 就是 $a$ 模 $m$ 的逆元；  
- 若 $\gcd(a, m) \neq 1$，则方程无解，逆元不存在（与前文逆元存在条件一致）。

#### 求解步骤
1. 调用拓展欧几里得算法，求解 $a x + m y = 1$ 的解 $x$；  
2. 由于 $x$ 可能为负数，需将其调整为正余数：$x_{\text{逆元}} = (x \mod m + m) \mod m$（加 $m$ 再模 $m$ 可确保结果在 $[0, m-1]$ 内）。

#### 例子：求 3 模 7 的逆元
方程为 $3x + 7y = 1$，调用 `Exgcd`：  
- 递归到 $b=0$：$a=7, b=0$，解 $x_1=1, y_1=0$；  
- 回溯：$a=3, b=7$，$\left\lfloor 3/7 \right\rfloor=0$，则 $x=y_1=0$，$y=x_1 - 0 \times y_1=1$，方程变为 $3 \times 0 +7 \times1=7 \neq1$（继续递归）；  
- 实际递归过程：$Exgcd(7,3) \to Exgcd(3,1) \to Exgcd(1,0)$，最终得到 $x=5, y=-2$（验证 $3 \times5 +7 \times(-2)=15-14=1$）；  
- 调整 $x$ 为正：$5 \mod7=5$，即逆元为 5，与前文结果一致。

#### 对应代码解析
```cpp
int exgcd(int a, int b, int& x, int& y) {
    if (!b) { // base case: b=0时，解为x=1, y=0
        x = 1;
        y = 0;
        return a; // 返回gcd(a,b)
    }
    int g = exgcd(b, a % b, y, x); // 递归求解子问题，注意y和x交换
    y -= a / b * x; // 按推导公式更新y
    return g; // 返回gcd
}

int main() {
    cin >> n >> p;
    int x, y;
    int g = exgcd(n, p, x, y);
    if (g != 1) cout << "Inverse doesn't exist" << endl; // gcd≠1，逆元不存在
    else cout << (x % p + p) % p << endl; // 调整x为正余数
    return 0;
}
```

## 五、O(n) 递推预处理逆元：批量求解的高效方法

当需要求解 `1~n` 所有数的逆元时（如组合数批量计算），快速幂或 `Exgcd` 需 $O(n log m)$ 时间，而 $O(n)$ 递推方法可大幅优化效率。以下是公式的详细推导与证明。

### 5.1 前提假设

通常$ O(n)$ 预处理逆元的场景中，$m$ 是**质数**（记为 `MOD`），且 $n < MOD$（确保 `1~n` 都与 MOD 互质，逆元存在）。我们需要预处理 $inv[1], inv[2], ..., inv[n]$，其中 $inv[i]$ 是 $i$ 模 MOD 的逆元。

### 5.2 核心公式推导

对于任意 $i \in [2, n]$，考虑 MOD 除以 $i$ 的带余除法： 
$MOD = k \times i + r \quad (0 < r < i)$  

其中 $k = \left\lfloor \frac{MOD}{i} \right\rfloor$（即代码中的 `MOD//i`），$r = MOD \mod i$（即代码中的 `MOD%i`）。  

将等式两边**模 MOD**（因 $MOD \equiv 0 \pmod {MOD}$），得： 
$0 \equiv k \times i + r \pmod{MOD}$  

移项整理，将含 $r$ 的项移到左边： 
$r \equiv -k \times i \pmod{MOD}$  

此时，两边同时乘以 $inv[i] \times inv[r]$（因 $i$ 和 $r$ 都小于 MOD，且 MOD 是质数，故 $inv[i]$ 和 $inv[r]$ 存在）： 
$r \times inv[i] \times inv[r] \equiv -k \times i \times inv[i] \times inv[r] \pmod{MOD}$  

利用逆元的性质 $x \times inv[x] \equiv 1 \pmod{MOD}$，化简两边：  
- 左边：$r \times inv[r] \times inv[i] \equiv 1 \times inv[i] = inv[i]$；  
- 右边：$-k \times i \times inv[i] \times inv[r] \equiv -k \times 1 \times inv[r] = -k \times inv[r]$。  

因此，等式简化为： 
$inv[i] \equiv -k \times inv[r] \pmod{MOD}$  

代入 $k = \left\lfloor \frac{MOD}{i} \right\rfloor$ 和 $r = MOD \mod i$，得： 
$inv[i] = \left( MOD - \left\lfloor \frac{MOD}{i} \right\rfloor \right) \times inv[MOD \mod i] \mod MOD$  

> 为什么用 $MOD - \left\lfloor \frac{MOD}{i} \right\rfloor$ 替代 $-k$？ 
> 因 $-k \mod MOD = MOD - k$（当 $k > 0$ 时），这样可确保结果为正数，避免负号导致的错误（如 $k=3, MOD=7$，$-3 \mod7=4=7-3$）。

### 5.3 对应代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;
const int MOD = 1e9 + 7; // 质数
int inv[N];

int main() {
    int n;
    cin >> n;
    inv[0] = inv[1] = 1; // inv[0]无意义，仅为初始化；inv[1]=1
    for (int i = 2; i <= n; i ++ ) {
        // 公式：inv[i] = (MOD - MOD//i) * inv[MOD%i] % MOD
        inv[i] = (1ll * (MOD - MOD / i) * inv[MOD % i]) % MOD;
    }
    for (int i = 1; i <= n; i ++ )
        cout << inv[i] << endl;
    return 0;
}
```

- 注意 `1ll` 强制转换：避免 $(MOD - MOD/i)$ 与 $inv[MOD%i]$ 的乘积溢出（如 MOD=1e9+7，两者乘积可达 1e18，需用 long long 存储后再取模）。

## 六、总结：不同逆元方法的适用场景

| 方法               | 时间复杂度   | 适用条件                        | 场景                       |
| ------------------ | ------------ | ------------------------------- | -------------------------- |
| 快速幂（小费马）   | $O(log MOD)$ | MOD 是质数，`gcd(a,MOD) = 1`    | 单个数逆元（如 `a mod p`） |
| 快速幂（欧拉定理） | $O(log MOD)$ | `gcd(a,MOD) = 1`（MOD 任意）    | 单个数逆元（MOD 非质数）   |
| 拓展欧几里得       | $O(log MOD)$ | `gcd(a,MOD) = 1`（MOD 任意）    | 单个数逆元（需判断存在性） |
| $O(n) $递推        | $O(n)$       | MOD 是质数，需批量求 `1~n` 逆元 | 组合数批量计算、多组查询   |



## 例题

[P3811](https://www.luogu.com.cn/problem/P3811)

[P5431](https://www.luogu.com.cn/problem/P5431)



## 推荐的练习

[P12028](https://www.luogu.com.cn/problem/P12028)
