# BSGS

在数论问题中，我们经常会遇到这样的需求：给定整数 $a, b, p$，求最小的非负整数 $x$，使得 $a^x \equiv b \pmod{p}$ 。这个问题被称为**离散对数问题**，而BSGS（Baby Step Giant Step，大步小步法）就是解决该问题的经典算法。本文会分两部分讲解：适用于 $a$ 与 $p$ 互质的**朴素BSGS**，以及可处理任意情况的**扩展BSGS**，并结合代码深入分析实现细节。



## 一、问题背景与朴素BSGS的适用场景

首先明确问题边界：我们要求解的是同余方程 $a^x \equiv b \pmod{p}$ 的最小非负整数解 $x$。  
- 若 $a$ 与 $p$ **互质**，根据欧拉定理，$a^{\phi(p)} \equiv 1 \pmod{p}$，因此 $x$ 的周期不超过 $\phi(p) \leq p$，朴素BSGS可高效求解；  
- 若 $a$ 与 $p$ **不互质**，欧拉定理不再适用，需用扩展BSGS处理。


## 二、朴素BSGS算法：原理与实现
### 1. 核心思想：分块平衡复杂度
朴素BSGS的本质是“分块查找”，通过将 $x$ 拆分为“小步”和“大步”，把指数运算的遍历复杂度从 $O(p)$ 降至 $O(\sqrt{p})$。

#### 推导过程

设 $k = \lceil \sqrt{p} \rceil$（取根号后向上取整，通常写为 $\sqrt{p} + 1$ 避免浮点误差），将 $x$ 表示为 $x = i \cdot k - j$（其中 $1 \leq i \leq k$，$0 \leq j < k$）。 
代入方程 $a^x \equiv b \pmod{p}$： 
$
a^{i \cdot k - j} \equiv b \pmod{p}
$ 
两边同乘 $a^j$（因 $a$ 与 $p$ 互质，$a^j$ 存在逆元，等式仍成立）： 
$
a^{i \cdot k} \equiv b \cdot a^j \pmod{p}
$  

此时方程分为两部分：
- **小步（Baby Step）**：预处理所有 $j \in [0, k-1]$ 对应的 $b \cdot a^j \pmod{p}$，存入哈希表，键为结果值，值为 $j$（记录小步的索引）；  
- **大步（Giant Step）**：计算 $a^k \pmod{p}$（记为 $ak$），再遍历 $i \in [1, k]$ 计算 $ak^i \pmod{p}$（即 $a^{i \cdot k} \pmod{p}$），若该值在哈希表中存在，则对应的 $x = i \cdot k - j$ 就是解。

### 2. 朴素BSGS代码解析

```cpp
#include <bits/stdc++.h>

using namespace std;

int t, n, m;

int bsgs(int a, int b, int p) {
    if (b % p == 1 % p) return 0;

    int k = sqrt(p) + 1;
    unordered_map<int, int> hash;
    for (int i = 0, j = b % p; i < k; i ++ ) {
        hash[j] = i;
        j = 1ll * j * a % p;
    }

    int ak = 1;
    for (int i = 1; i <= k; i ++ ) ak = 1ll * ak * a % p;
    for (int i = 1, j = ak; i <= k; i ++ ) {
        if (hash.count(j)) return k * i - hash[j];
        j = 1ll * j * ak % p;
    }

    return -1;
}

int main() {
    int a, b, p;
    while (cin >> a >> b >> p, a || b || p) {
        int t = bsgs(a, b, p);
        if (t == -1) puts("No Solution");
        else cout << t << endl;
    }

    return 0;
}
```

#### 关键细节说明
- **边界处理**：`if (b % p == 1 % p) return 0` 对应 $a^0 = 1 \equiv b \pmod{p}$ 的情况，直接返回解 $x=0$；  
- **防溢出**：所有乘法都用 `1ll * ...` 强制转换为64位整数，避免32位int相乘溢出（如 $a=1e9, j=1e9$，相乘会超int范围）；  
- **哈希表选择**：用 `unordered_map` 而非 `map`，因为前者是哈希表，平均查询时间 $O(1)$，后者是红黑树，查询 $O(log k)$，在 $p$ 较大时 `unordered_map` 更快；  
- **分块大小**：`k = sqrt(p) + 1` 是为了确保覆盖所有可能的 $x$（因 $x \leq p$，而 $i \cdot k - j \leq k \cdot k - 0 = (sqrt(p)+1)^2 > p$，必能覆盖）。


### 3. 朴素BSGS的时间复杂度
- 小步预处理：遍历 $k$ 次，每次哈希表插入 $O(1)$，总 $O(k)$；  
- 大步查询：遍历 $k$ 次，每次哈希表查询 $O(1)$，总 $O(k)$；  
- 因 $k = O(\sqrt{p})$，整体时间复杂度为 $O(\sqrt{p})$。


## 三、扩展BSGS：处理a与p不互质的情况
朴素BSGS的致命局限是要求 $a$ 与 $p$ 互质，若不互质，$a^j$ 可能没有逆元，之前的推导不成立。扩展BSGS（exBSGS）通过**约分**将方程转化为 $a$ 与新模数互质的形式，从而复用朴素BSGS。

### 1. 核心思想：逐步约分，递归转化

#### 推导过程
目标：将方程 $a^x \equiv b \pmod{p}$ 转化为 $a^x \equiv b' \pmod{p'}$（其中 $gcd(a, p') = 1$）。

步骤1：处理边界情况
若 $b \equiv 1 \pmod{p}$，则 $x=0$（无论 $a$ 与 $p$ 是否互质）。

步骤2：计算最大公约数，判断无解
设 $d_1 = gcd(a, p)$：  

- 若 $d_1 \nmid b$，则方程无解（因左边 $a^x$ 是 $d_1$ 的倍数，右边 $b$ 不是，mod $p$ 下不可能相等）；  
- 若 $d_1 \mid b$，则将方程两边同时除以 $d_1$，得到：
  $
  \frac{a}{d_1} \cdot a^{x-1} \equiv \frac{b}{d_1} \pmod{\frac{p}{d_1}}
  $

步骤3：递归处理新方程 
令 $a_1 = \frac{a}{d_1}$，$b_1 = \frac{b}{d_1}$，$p_1 = \frac{p}{d_1}$，方程变为：
$
a_1 \cdot a^{x-1} \equiv b_1 \pmod{p_1}
$ 
重复步骤2，计算 $d_2 = gcd(a, p_1)$，继续约分，直到 $d_k = gcd(a, p_k) = 1$。此时方程变为： 
$
(a_1 \cdot a_2 \cdot \dots \cdot a_k) \cdot a^{x-k} \equiv b_k \pmod{p_k}
$ 
其中 $b_k = \frac{b_{k-1}}{d_k}$，$p_k = \frac{p_{k-1}}{d_k}$。

步骤4：用朴素BSGS求解 
因 $gcd(a, p_k) = 1$，$a$ 在 mod $p_k$ 下存在逆元。令 $C = a_1 \cdot a_2 \cdot \dots \cdot a_k$，则方程可改写为： 
$
a^{x-k} \equiv b_k \cdot C^{-1} \pmod{p_k}
$ 
用朴素BSGS求解该方程的解 $x' = x - k$，则原方程的解为 $x = x' + k$。

### 2. 扩展BSGS代码

代码中用到了扩展欧几里得算法（exgcd）求逆元，先回顾exgcd的作用：求 $ax + by = gcd(a, b)$ 的整数解，若 $gcd(a, b) = 1$，则 $x$ 是 $a$ 在 mod $b$ 下的逆元。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

int t, n, m;

int bsgs(int a, int b, int p) {
    if (b % p == 1 % p) return 0;

    int k = sqrt(p) + 1;
    unordered_map<int, int> hash;
    for (int i = 0, j = b; i < k; i ++ ) {
        hash[j] = i;
        j = 1ll * j * a % p;
    }

    int ak = 1;
    for (int i = 1; i <= k; i ++ ) ak = 1ll * ak * a % p;
    for (int i = 1, j = ak; i <= k; i ++ ) {
        if (hash.count(j)) return k * i - hash[j];
        j = 1ll * j * ak % p;
    }

    return -INF;
}

int exgcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int exbsgs(int a, int b, int p) {
    b = (b % p + p) % p;
    if (b == 1) return 0;
    
    int x, y;
    int d = exgcd(a, p, x, y);
    if (d > 1) {
        if (b % d) return -INF;
        exgcd(a / d, p / d, x, y);
        return exbsgs(a, (1ll * b / d * x) % (p / d) , p / d) + 1;
    }
    
    return bsgs(a, b, p);   
}

int main() {
    int a, b, p;
    while (cin >> a >> b >> p, a || b || p) {
        int t = exbsgs(a, b, p);
        if (t < 0) puts("No Solution");
        else cout << t << endl;
    }

    return 0;
}
```

#### 关键细节说明
- **b的预处理**：`b = (b % p + p) % p` 确保 $b$ 是非负数，避免负号导致的哈希表匹配错误；  
- **递归终止条件**：当 $d = gcd(a, p) = 1$ 时，调用朴素BSGS求解；  
- **逆元计算**：`exgcd(a/d, p/d, x, y)` 得到 $a/d$ 在 mod $p/d$ 下的逆元 $x$，因此 `(1ll * b/d * x) % (p/d)` 就是 $b/d \cdot (a/d)^{-1} \pmod{p/d}$，对应推导中的 $b_1 \cdot a_1^{-1}$；  
- **递归返回值**：`+1` 是因为每次约分对应 $x$ 减少1（原方程是 $a^{x-1}$），递归得到的是 $x-k$，需要加 $k$（这里每次递归加1，累计加 $k$）。

## 五、总结

- **朴素BSGS**：适用于 $a$ 与 $p$ 互质的离散对数问题，时间复杂度 $O(\sqrt{p})$，核心是分块查找；  
- **扩展BSGS**：通过逐步约分处理 $a$ 与 $p$ 不互质的情况，递归转化为朴素BSGS可解的形式，时间复杂度仍为 $O(\sqrt{p})$；  
- **应用场景**：数论题目中涉及“求指数”的问题，如模方程求解、密码学中的离散对数问题（OI中常见于NOIP提高组或省选难度题目）



## 例题

[P3846](https://www.luogu.com.cn/problem/P3846)

[P4195](https://www.luogu.com.cn/problem/P4195)



## 推荐的练习

[SP3105](https://www.luogu.com.cn/problem/SP3105)

[P3306](https://www.luogu.com.cn/problem/P3306)

[P2485](https://www.luogu.com.cn/problem/P2485)
