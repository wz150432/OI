# 常用C++函数

编程通常依赖可复用工具来简化任务。以下是按使用场景组织的核心函数和I/O操作的精要说明——无代码，仅关键细节。

## 1. 数据操作

- **abs(x)**：返回 $x$ 的绝对值 $x$ 属于 *int* ; `llabs()`用于 *long long*，`fabs()`用于 *double*

- **swap(a, b)**：交换两个变量的值（适用于所有基本类型如 *int*、*char*）
- **floor(x)**：向下取整，返回 $\le x$ 的最大整数（例：`3.8 → 3`，`-2.1 → -3`）
- **ceil(x)**：向上取整，返回 $\ge x$ 的最小整数（例：`3.2 → 4`，`-2.9 → -2`）
- **log(x)**：计算正数 $x$ 的自然对数（以 $e$ 为底）
- **log10(x)**：计算正数 $x $的常用对数（以 $10$ 为底）
- **pow(x, n)**：计算 $x^n$（对于大 $n$ 通常使用"快速幂"优化，常配合模运算确保安全）

## 2. 字符串处理

- **getline(cin, s)**：读取整行到字符串 $s$ 中
- **substr(pos, len)**：从字符串s中提取子串——从索引 `pos`（0起始）开始，取`len`个字符（省略 `len` 则取到末尾）
- **stoi()**：将数字字符串（如"123"）转换为 *int* ；`stoll()`用于 *long long*，`stof()`用于 *float*
- **tolower(c)**：将单个大写字符 $c$ 转换为小写（例：`'A' → 'a'`）
- **toupper(c)**：将单个小写字符 $c$ 转换为大写（例：`'b' → 'B'`）

## 3. 二进制相关（C++内置函数）

- **__builtin_ctz(x)**：计算 $x$ 二进制形式中末尾零的个数（$x \gt 0$，例如： $8 = (1000)_2 \to 3$ 个 $0$）
- **__builtin_popcount(x)**：计算 $x$ 二进制形式中 `1` 的个数
- **__builtin_clz(x)**：计算 $x$ 二进制中**前导零个数**（$x\gt 0$，例如 $8=(1000)^2 \to 3$ 个 $0$）。
- **__builtin_parity(x)**：判断 $x$ 二进制中 $1$ 的个数**奇偶性**（`odd → 1`，`even → 0`）。

## 4. 输入/输出（I/O）

### 核心工具

- **cin >> x**：读取一个数据片段（*int*、*string*等）到 $x$ 中（在空格, 制表符，换行符处停止）
- **cout << x**：将 $x$ 输出
- **scanf/printf**：更快的C风格I/O（需要格式说明符匹配数据类型）
- **stringstream** 重载了 `<<` 和 `>>` 运算符，用法与 `cout`/`cin` 一致。一般当使用完 `getline` 且不知道这一行有多少元素时使用。例如 `stringstream ss(str)` ，我们可以通过 `ss` 取出 `str`中的元素，例如： `ss >> x` 。

### 关键格式说明符（用于scanf/printf）

| 说明符  | 使用场景                 | 示例结果                    |
| ------- | ------------------------ | --------------------------- |
| `%d`    | `int`                    | 42 → "42"                   |
| `%lld`  | `long long`              | 12345678901 → "12345678901" |
| `%c`    | `char`                   | 'a' → "a"                   |
| `%s`    | `string`（字符数组）     | "test" → "test"             |
| `%lf`   | `double`                 | 3.14 → "3.14"               |
| `%.xlf` | `double` （保留x位小数） | 3.1415 → "3.14"             |
| `%0md`  | `int` （补0至m宽度）     | 42→"00042"                  |
| `%-md`  | `int` （左对齐至m宽度）  | 42→"42   "                  |

### freopen()

将标准输入/输出重定向到文件：

- `freopen("1.in", "r", stdin)`：从"1.in"读取输入（替代键盘）
- `freopen("1.out", "w", stdout)`：保存输出到"1.out"（替代控制台）

## 5. 排序

- **sort(first, last)**：对 $[first, last)$ 区间元素排序（默认升序），支持自定义比较函数。适用于数组、动态数组等可迭代容器。
- **lower_bound(first, last, val)**：在有序 $[first, last)$ 中找**第一个 $\ge$ val** 的迭代器，不存在则返回 `last`。
- **upper_bound(first, last, val)**：在有序 $[first, last)$ 中找**第一个 $\gt$ val** 的迭代器，不存在则返回 `last`。
- **reverse(first, last)**：反转 $[first, last)$ 区间元素（如字符串 "abc"→"cba"）。
- **next_permutation(first, last)**：生成当前序列的**下一个字典序排列**（需初始有序），返回 *bool*（无下一个则 `false`）。

## 6. 初始化和复制

- **memset(a, value, sizeof a)**：用`value`初始化内存块（数组`a`）。常用值：0、-1、0x3f、0xff
- **memcpy(destination, src, size)**：从 `src `复制 `size` 字节到 `destination`（比手动循环快，需确保内存不重叠）。