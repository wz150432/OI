# 对拍

在竞赛过程中，确保正确性至关重要——特别是在优化超越暴力解法时。对拍是一种强大的技术，用于验证优化解决方案在各种输入下与可信的暴力解法行为一致，还可以获得数据借此debug。以下是实施此流程的逐步流程。

## 对拍的核心要素

1. **暴力代码**：直接、保证正确的实现（可能较慢，但作为"正确答案的来源"）
2. **正解**：需要验证正确性的更快解决方案
3. **随机数据生成器**：生成涵盖边界情况和典型场景的多样化测试用例的程序
4. **自动化脚本**：重复运行两种解决方案、比较输出并在出现差异时标记的脚本

## I. 自动化脚本

这些脚本自动化测试循环：生成数据、运行两种解决方案、比较结果并在失败时停止。

### Shell 脚本 (Linux)

```sh
#!/bin/bash
g++ my.cpp -std=c++11 -o my # 解决方案
g++ bf.cpp -std=c++11 -o bf # 暴力过程
g++ rand.cpp -std=c++11 -o rand # 数据生成器

t=1
while [ $t -lt 1000000 ]; do
    printf "用例%d:\n" $t
    
    # '<' 输入 '>' 输出将覆盖原始数据。如果不想覆盖，使用 '<<' 输入 '>>' 输出
    
    ./rand > rand.in # 数据生成到 rand.in 文件
    
    ./bf < rand.in > bf.out # 暴力过程的输出到 bf.out 文件
    
    time ./my < rand.in > my.out # 解决方案的输出到 my.out 文件，同时显示运行时间
    
    # -Z 忽略尾随空格的差异
    if diff -Z bf.out my.out; then 
        echo "AC\n"
    else 
        echo "WA\n"
        cat rand.in # 显示输入数据。可选且建议仅适用于小数据
        break;
    
    fi # if 语句结束
    
    let "t = $t + 1"
done
```

$\newline$

### C++ 脚本 (Windows)

```cpp
#include <chrono>
#include <cstdio>

using namespace std;

int c;

int main() {
    system("g++ my.cpp -std=c++11 -o my.exe");
    system("g++ rand.cpp -std=c++11 -o rand.exe");
    system("g++ bf.cpp -std=c++11 -o bf.exe");
    
    
    while (c <= 1000000) {
        system("rand.exe > rand.in");
        system("bf.exe < rand.in > bf.out");
        
        double st = clock();
        system("test.exe < rand.in > test.out");
        double ed = clock();
        
        if (system("fc test.out bf.out > nul")) {
            printf("#用例%d: 错误, 耗时: %.0lfms\n", ++ c, ed - st);
            break;
        }
        printf("#用例%d: 通过, 耗时: %.0lfms\n", ++ c, ed - st);
    }

    return 0;
}
```

*注意：Windows 脚本可以通过将 `fc` 替换为 `diff` 并调整可执行文件扩展名来适应 Linux。*

$\newline$

## II. 编写随机数据生成器

强大的数据生成器确保测试用例涵盖多样化场景（例如，小/大输入、空集或最大值等边界情况）。以下是基础工具和示例。

### 基础生成器工具

```cpp
#include<cstdlib>
#include <ctime>

using namespace std;

typedef long long ll;
// 由于 Windows 系统中 rand 函数的范围是 [0 - 32767]，对于更大数值范围的数据，可能需要多次相乘
// 但 Linux 类系统中 rand 函数的范围是 0 到 2147483647，务必避免生成的数据溢出
// 以下代码生成从 0 到 n-1 范围的数字。如果需要负数，可以从 0 到 2n 范围的数字中减去 n

int ri(int n) {
    return 1ll * rand() * rand() % n;
}

ll rll(ll n) {
    return 1ll * rand() * rand() % n;
}

int main() {
    srand(time(0));
    
    return 0;
}
```

### 示例 1：生成树（n 个节点，n-1 条边）

```cpp
int n = ri(100000);

for (int i = 2 ; i <= n ; i ++ )  {
    int p = ri(i - 1) + 1;
    int val = ri(1000000000) + 1;
    printf("%d %d %d\n", p, i, val);
}
```

### 示例 2：生成连通无向图（n 个节点，m 条边）

*确保没有多重边或自环*

```cpp
typedef pair<int, int> PII;
PII e[N];
map<PII, bool> vis;

for (int i = 1 ; i < n ; i ++ ) {
    int p = ri(i) + 1;
    e[i] = {p, i + 1};
    vis[e[i]] = vis[{i + 1, p}] = 1;
}

for (int i = n ; i <= m ; i ++ ) {
    int x = -2e9, y = -2e9;
    while (x == y || vis[{x, y}])
        x = ri(n) + 1, y = ri(n) + 1;
    
    e[i] = {x, y};
    vis[e[i]] = vis[{y, x}] = 1;
}

random_shuffle(e + 1, e + m + 1);
for (int i = 1 ; i <= m ; i ++ ) 
    printf("%d %d\n", e[i].first, e[i].second);
```

## 如何使用此工作流程

1. **准备实现**：编写优化解决方案（`my.cpp`）和暴力版本（`bf.cpp`）
2. **构建生成器**：创建 `rand.cpp` 以生成与问题相关的测试用例（例如，图、数组或自定义结构）
3. **运行脚本**：执行自动化脚本。它将：
   - 编译所有程序
   - 生成测试用例
   - 在每个用例上运行两种解决方案
   - 比较输出。如果不同，则停止并显示失败的输入
4. **调试**：使用失败的输入来识别优化解决方案与暴力结果偏离的地方

这种方法可以高效地测试上万个用例，确保解决方案的正确性。