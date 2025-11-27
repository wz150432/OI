# exKMP ($Z$ 函数)

我们知道 KMP 算法，他基于 $[1, x]$ 区间前缀和后缀相等的最大长度 $ne_i$ 做到 $O(M + N)$ 快速匹字串。ne 是 next 的缩写。

exKMP 可以线性的求出 $\forall x \in [0, n]$ ，$[0, n]$ 与 $[x, n]$ 的最长公共前缀的长度  $ne_i$。 首先我们先假设我们已经知道了 $0\sim x - 1$ 的 $ne$ 函数的值。我们让其中长度最长的下标为 $k$，根据定义我们很容易发现 $[0, ne_k - 1]$ 等于 $[k, k + ne_k - 1]$ ，我们让 $p = k + ne_k - 1$ ，$[x - k, ne_k - 1]$ 等于 $[x, p]$ ，因为他是前\者的子集。我们让 $l = ne_{x-k}$，如果 $l > p-x$ 我们暴力扫，其他情况 $ne_k=l$。



```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 2e7 + 10;

ll res1, res2;
ll z[N], p[N];
string s1, s2;

void Z(string a, ll v[]) {
    int n = a.size();
    v[0] = n;
    int p = 0, k = 1, l;
    while (p + 1 < n && a[p + 1] == a[p]) p ++ ;
    v[1] = p;
    for (int i = 2; i < n; ++ i) {
        p = k + v[k] - 1;
        l = v[i - k];
        if (l > p - i) {
            int j = max(0, p - i + 1);
            while (i + j < n && a[i + j] == a[j]) j ++ ;
            v[i] = j;
            k = i;
        } else v[i] = l;
    }
}

void exKMP(string a, string b, ll v[], ll v1[]) {
    int n = a.size(), m = b.size();
    int p = 0, k = 0, l;
    while (p < n && p < m && a[p] == b[p]) p ++ ;
    v[0] = p;
    for (int i = 1; i < n; ++ i) {
        p = k + v[k] - 1;
        l = v1[i - k];
        if (l > p - i) {
            int j = max(0, p - i + 1);
            while (i + j < n && j < m && a[i + j] == b[j]) j ++ ;
            v[i] = j;
            k = i;
        } else v[i] = l;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> s1 >> s2;
    
    Z(s2, z), exKMP(s1, s2, p, z);

    for (int i = 0; i < s2.size(); ++ i)
        res1 ^= (i + 1) * (z[i] + 1);
    cout << res1 << endl;
    for (int i = 0; i < s1.size(); ++ i)
        res2 ^= (i + 1) * (p[i] + 1);
    cout << res2 << endl;
    
    return 0;
}
```



我们其实只用计算一次，我们很容易想到给出一个字符串 b + a，这样构造出的就直接可以计算出上面代码一样的效果，虽然上面的代码更容易让人理解，但是显然下面的代码时更好的模板。



```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 2e7;

int n, m;
ll res1, res2;
int z[N << 1];
string a, b;


void Z(string s){
    int l = 0; // 最优匹配下标，等价于上面的k
    for (int i = 1; i < n + m; ++ i) {
        // 相互约束的条件，等价于上面的 if (l > p - i) 的特判
        if (l + z[l] > i) z[i] = min(z[i - l], l + z[l] - i); 
        while (i + z[i] < n + m && s[z[i]] == s[i + z[i]]) z[i] ++ ;
        if (i + z[i] > l + z[l]) l = i;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> a >> b;
    n = a.size(), m = b.size();

    Z(b + a);
    res1 ^= 1ll * (m + 1);
    for (int i = 1; i < m; ++ i) 
        res1 ^= 1ll * (min(z[i], m - i) + 1) * (i + 1);

    for (int i = 0; i < n; ++ i) 
        res2 ^= 1ll * (min(z[i + m], m) + 1) * (i + 1);

    cout << res1 << endl << res2 << endl;

    return 0;
}
```

