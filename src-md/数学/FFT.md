# 快速傅里叶变换（FFT）

多项式乘法的朴素做法是系数逐项相乘，时间复杂度为 $O(n^2)$，而**快速傅里叶变换（FFT）** 借助"系数→点值→系数"的转换，将复杂度降至 $O(n\log n)$。下面结合数学原理和代码实现，完整解析FFT的核心逻辑。

## 一、FFT的分治思想：多项式的奇偶分解与单位根

### 1. 多项式的奇偶拆分
对于 $n-1$ 次多项式 $f(x) = \sum_{i=0}^{n-1} a_i x^i$，按**下标奇偶性**拆分为两个子多项式：
- 偶次项子多项式：$G(x) = a_0 + a_2 x + a_4 x^2 + \dots$
- 奇次项子多项式：$H(x) = a_1 + a_3 x + a_5 x^2 + \dots$

因此，原多项式可表示为：
$$ f(x) = G(x^2) + x \cdot H(x^2) $$

### 2. 单位根的引入（蝶形运算的核心）

为了让"分治"后的子问题快速合并，FFT引入**$n$ 次单位根** $\omega_n$，满足 $\omega_n^n = 1$，由欧拉公式得：
$$ \omega_n = e^{\frac{2\pi i}{n}} = \cos\frac{2\pi}{n} + i\sin\frac{2\pi}{n} $$

单位根有两个关键性质（支撑分治合并）：
- **周期性**：$\omega_n^{k + n} = \omega_n^k$
- **对称性**：$\omega_n^{k + \frac{n}{2}} = -\omega_n^k$（因 $\omega_n^{\frac{n}{2}} = -1$）

### 3. 分治合并：单位根代入后的蝶形公式
假设计算 $f(x)$ 在 $n$ 个单位根处的点值（$x = \omega_n^0, \omega_n^1, \dots, \omega_n^{n-1}$）。结合多项式奇偶拆分，代入 $x = \omega_n^k$（$k \in [0, \frac{n}{2}]$）：

$$
\begin{align*}
f(\omega_n^k) &= G\left( (\omega_n^k)^2 \right) + \omega_n^k \cdot H\left( (\omega_n^k)^2 \right) \\
&= G\left( \omega_{\frac{n}{2}}^k \right) + \omega_n^k \cdot H\left( \omega_{\frac{n}{2}}^k \right)
\end{align*}
$$

再代入 $x = \omega_n^{k + \frac{n}{2}}$（利用单位根对称性 $\omega_n^{\frac{n}{2}} = -1$）：

$$
\begin{align*}
f\left( \omega_n^{k + \frac{n}{2}} \right) &= G\left( (\omega_n^{k + \frac{n}{2}})^2 \right) + \omega_n^{k + \frac{n}{2}} \cdot H\left( (\omega_n^{k + \frac{n}{2}})^2 \right) \\
&= G\left( \omega_n^{2k + n} \right) - \omega_n^k \cdot H\left( \omega_n^{2k + n} \right) \\
&= G\left( \omega_{\frac{n}{2}}^k \right) - \omega_n^k \cdot H\left( \omega_{\frac{n}{2}}^k \right)
\end{align*}
$$

这意味着：**只要知道 $G$ 和 $H$ 在 $\omega_{\frac{n}{2}}^k$ 处的点值，就能同时算出 $f$ 在 $\omega_n^k$ 和 $\omega_n^{k + \frac{n}{2}}$ 处的点值**——这就是"蝶形运算"的数学基础，也是FFT分治合并的核心。

## 二、位逆序：从递归到迭代的优化

递归版FFT思路直观，但递归栈和重复计算影响效率。工程中常用**迭代版FFT**，"位逆序置换"是迭代的核心。

### 二进制翻转的由来
递归分治时，多项式不断按奇偶拆分，最终拆分为单个元素。观察最终"单个元素的顺序"，会发现其与原始顺序存在**"二进制位逆序"**的关系（如 $n=8$ 时，索引 `1(001)` 的逆序是 `4(100)`，`3(011)` 的逆序是 `6(110)`）。

因此，迭代FFT的第一步是**位逆序置换**——将原始系数数组按"二进制位逆序"重排，让后续迭代合并能模拟递归拆分顺序。

### 代码中高效生成位逆序表
代码通过递推高效生成位逆序表：
```cpp
rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bits - 1));
```
- `i >> 1` 去掉 $i$ 的最低位，`rev[i >> 1]` 是"去掉最低位后的逆序"
- `(i & 1)` 取出 $i$ 的最低位，左移 `bits-1` 位后，将"最低位"放到"最高位"
- 两者结合，得到 $i$ 的完整二进制逆序

## 三、逆FFT：从点值变回系数

当通过FFT得到两个多项式的点值后，将点值相乘（得到乘积多项式的点值），还需**逆FFT**将点值转换回系数。

### 数学推导：单位根的正交性
已知乘积多项式的点值 $y_k = f(\omega_n^k) \cdot g(\omega_n^k)$（$k=0,1,\dots,n-1$），构造辅助多项式 $A(x) = \sum_{i=0}^{n-1} y_i x^i$，代入 $x = \omega_n^{-k}$：

$$
A(\omega_n^{-k}) = \sum_{i=0}^{n-1} y_i \omega_n^{-ik} = \sum_{i=0}^{n-1} \left( \sum_{j=0}^{n-1} a_j \omega_n^{ij} \right) \omega_n^{-ik}
$$

交换求和顺序后：

$$
A(\omega_n^{-k}) = \sum_{j=0}^{n-1} a_j \sum_{i=0}^{n-1} (\omega_n^{j - k})^i
$$

令 $S(\omega_n^\alpha) = \sum_{i=0}^{n-1} (\omega_n^\alpha)^i$，由等比数列求和与单位根性质：
- 若 $\alpha \equiv 0 \pmod{n}$，则 $S(\omega_n^\alpha) = n$
- 若 $\alpha \not\equiv 0 \pmod{n}$，则 $S(\omega_n^\alpha) = 0$

因此，只有 $j = k$ 时内层求和非零，即：
$$ A(\omega_n^{-k}) = n \cdot a_k $$

这说明：**对 $y_k$ 做一次"以 $\omega_n^{-1}$ 为单位根的FFT（正变换）"，再除以 $n$，就能得到原系数 $a_k$**。

### 代码实现：逆FFT的简化
代码中，逆FFT通过"单位根取共轭 + 正FFT + 除以长度"实现：
```cpp
fft(a, -1);  // inv = -1时，单位根为cos(PI/mid) - i*sin(PI/mid)（即共轭）
```
逆变换后除以 `tot`（对应推导中的"$n$"），并通过 `+0.5` 四舍五入消除浮点误差。

## 四、代码与数学的一一对应（完整代码解析）

结合代码，看数学推导如何落地：

```cpp
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

const double PI = acos(-1);

int n, m;
int tot, bits;
vector<int> rev;

void fft(vector<complex<double>> &a, int inv) {
    for (int i = 0; i < tot; i ++ ) 
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    
    for (int mid = 1 ; mid < tot ; mid <<= 1) {
        complex<double> w1(cos(PI / mid), inv * sin(PI / mid)); 
        for (int i = 0 ; i < tot ; i += 2 * mid) {
            complex<double> wk(1, 0);
            for (int j = 0 ; j < mid ; j ++ , wk *= w1) {
                auto x = a[i + j], y = wk * a[i + j + mid];
                a[i + j] = x + y, a[i + j + mid] = x - y;
            }
        }
    }
}

int main() {
    cin >> n >> m;
    vector<complex<double>> a(n + 1);
    vector<complex<double>> b(m + 1);

    for (int i = 0; i <= n; i ++ ) {
        int x;
        cin >> x;
        a[i]= complex<double>(x, 0);
    }

    for (int i = 0; i <= m; i ++ ) {
        int x;
        cin >> x;
        b[i] = complex<double>(x, 0);
    }
 
    bits = ceil(log2(n + m + 1));
    tot = 1 << bits;
    rev.resize(tot), a.resize(tot), b.resize(tot);
    for (int i = 0; i < tot; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bits - 1));

    fft(a, 1), fft(b, 1);
    for (int i = 0; i < tot; i ++ ) a[i] *= b[i];
    fft(a, -1);

    for (int i = 0; i <= n + m; i ++ )
        cout << (int)(a[i].real() / tot + 0.5) << " ";

    return 0;
}
```

- **位逆序与分治**：`rev` 数组和 `swap` 操作，对应"迭代模拟递归拆分顺序"
- **蝶形运算与单位根**：三层循环中，`w1` 是主单位根，`wk` 是当前蝶形单元的单位根，`x+y` / `x-y` 对应分治合并公式
- **逆FFT的实现**：`inv = -1` 时单位根取共轭，完成"点值→系数"转换，除以 `tot` 对应推导中"$A(\omega_n^{-k}) = n \cdot a_k$"

## 五、总结：从数学到代码的闭环

FFT的核心是"用分治思想+单位根性质，将系数乘法的高复杂度转换为点值乘法的低复杂度"。代码则将这一思想拆解为：
1. 位逆序置换：优化递归到迭代的过程
2. 蝶形运算：利用单位根快速合并分治结果
3. 逆变换修正：将点值转换回系数



## 例题

[P3803](https://www.luogu.com.cn/problem/P3803)



## 推荐的练习

[P1919](https://www.luogu.com.cn/problem/P1919)

[UVA12298](https://www.luogu.com.cn/problem/UVA12298)
