# 稀疏表

ST 表一般用来处理 RMQ 问题，也就是通过二进制的性质在 $\Theta(NlogN)$ 的预处理后， $\Theta(1)$ 的回答一个区间内的极值。



### 预处理:

我们定义一个二维数组 $f$，$f_{i, j}$ 表示从 $i$ 开始长度为 $2^j$ 这个区间内的极值。

- 对于 $j = 0$（区间长度 $2^0 = 1$）：$f_{i,0} = a_i$（元素本身的值）。
- 对于 $j > 0$：将区间 $[i, i + 2^j - 1]$ 分成两个长度为 $2^{j-1}$ 的区间：
    $f_{i,j} = \max(f_{i,j-1}, f_{i + 2^{j-1},j-1})$

```cpp
int k = floor(log(n) / log(2));
    for (int j = 0 ; j <= k; ++ j)
        for (int i = 1; i + (1 << j) - 1 <= n; ++ i) {
            if (!j) f[i][j] = a[i];
            else f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
```



### 查询:

我们已经处理出了数组 $f$，我们就可以通过两个值直接覆盖区间 $[l, r]$。

```cpp
int RMQ(int l, int r) {
    int k = floor(log(r - l + 1) / log(2));
    return max(f[l][k], f[r - (1 << k) + 1][k]);
}
```
