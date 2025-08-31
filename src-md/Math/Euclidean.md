# 欧几里得算法与扩展欧几里得算法（C++实现）

## 1. 欧几里得算法（最大公约数计算）

### 1.1 基本概念

欧几里得算法（又称辗转相除法）是一种计算两个整数最大公约数（GCD）的高效方法。它基于以下核心原理：

`gcd(a, b) = gcd(b, a % b)`

其中 `a % b` 表示 `a` 除以 `b` 的余数。这个过程持续迭代，直到第二个数变为 $0$，此时第一个数就是原来两个数的最大公约数。

### 1.2 辗转相除法的正确性证明

要证明 `gcd(a, b) = gcd(b, a % b)`，设 `d = gcd(a, b)`，`r = a % b`，则有：

1. **证明d是b和r的公约数**
   - 因为 `d | a`且`d | b`（d能整除a和b）
   - 由 `r = a - kb`（其中`k = ⌊a/b⌋`）
   - 所以 `d | (a - kb)`，即`d | r`
   - 故 $d$ 是 $b$ 和 $r$ 的公约数

2. **证明 gcd(b, r)是a和b的公约数**
   - 设`d' = gcd(b, r)`
   - 则`d'| b`且`d'| r`
   - 由`a = kb + r`，得`d'| a`
   - 故 $d'$ 是 $a$ 和 $b$ 的公约数

综上，`gcd(a, b)`与`gcd(b, a % b)`的公约数集合完全相同，因此它们的最大公约数必然相等。

### 1.3 C++实现

```cpp
#include <iostream>

using namespace std;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b);
    return 0;
}
```

## 2. 扩展欧几里得算法

### 2.1 核心思想

扩展欧几里得算法是欧几里得算法的推广，它不仅能计算 `a` 和 `b` 的最大公约数`d`，还能找到整数 `x` 和 `y`，使得它们满足**贝祖等式（Bézout's identity）**：

`a * x + b * y = d`（其中`d = gcd(a, b)`）

### 2.2 贝祖等式的存在性证明（裴蜀定理）

**定理**：对于任意整数`a, b`，存在整数`x, y`使得`a * x + b * y = gcd(a, b)`。

**证明**：
设 `S` 为所有形如 `ax + by` 的正整数集合，取其中最小的正整数 `s = ax₀ + by₀`。

1. **证明s是a和b的公约数**
   - 假设 $s$ 不能整除 $a$，则  `a = qs + r`（$0 \lt r \lt s$）
   - `r = a - qs = a - q(ax₀ + by₀) = a(1 - qx₀) + b(-qy₀)`
   - 这与  $s$ 是最小正整数的假设矛盾
   - 故 $s$ 能整除 $a$，同理 $s$ 能整除 $b$
   - 所以 $s$ 是 $a$ 和 $b$ 的公约数

2. **证明s是最大公约数**
   - 设 $d$ 为 $a$ 和 $b$ 的任意公约数，则 `d | (ax₀ + by₀)`，即`d | s`
   - 故 $s \ge d$，$s$ 就是最大公约数

综上，存在整数 $x$ , $y$ 使得 `ax + by = gcd(a, b)`。

### 2.3 递归求解方法

基于欧几里得算法的递归结构：

- **基本情况**：当 `b = 0` 时，`gcd(a, 0) = a`，此时 `x = 1, y = 0`
- **递归情况**：已知 `gcd(a, b) = gcd(b, a % b)`
  - 设 `gcd(b, a % b) = bx' + (a % b)y'`
  - 代入 `a % b = a - ⌊a/b⌋b`得：
    `bx' + (a - ⌊a/b⌋b)y' = ay' + b(x' - ⌊a/b⌋y')`
  - 故当前层的解为：`x = y'`, `y = x' - ⌊a/b⌋y'`

### 2.4 C++实现

```cpp
#include <iostream>

using namespace std;

int exgcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int main() {
    int a, b;
    cin >> a >> b;
    int x, y;
    int d = exgcd(a, b, x, y);
    // 最大公约数d, 以及一组特解 [x,y]
    cout << d << " " << x << " "  << y << endl;
    
    return 0;
}
```

## 3. 时间复杂度分析

两种算法的时间复杂度均为 $O(log(min(a, b)))$，这是因为每一步迭代中，余数至少会减小一半。即使对于极大的整数（如 $10^{18}$ 级别），该算法仍能高效运行。
