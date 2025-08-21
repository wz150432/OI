# The 0-1 Knapsack Problem: A Complete Guide with Dynamic Programming

The 0-1 knapsack problem is a classic combinatorial optimization challenge in computer science. Unlike the unbounded knapsack (where items can be reused), the "0-1" constraint means each item can be either **included (1)** or **excluded (0)** from the knapsack—no partial selections allowed.


## 1. Problem Definition
We are given two arrays:
- `weights[]`: Stores the weight of each item (e.g., `[2, 3, 4, 5]`).
- `values[]`: Stores the value of each corresponding item (e.g., `[3, 4, 5, 6]`).
- A knapsack with a maximum weight capacity `W` (e.g., `8`).

**Goal**: Select a subset of items such that their total weight does not exceed `W`, and their total value is maximized.


## 2. Dynamic Programming (DP) Approach
Brute-force methods (checking all subsets) have an exponential time complexity (`O(2ⁿ)`), which is infeasible for large `n`. Dynamic programming optimizes this by storing intermediate results to avoid redundant calculations.

### 2.1 DP Table Definition
Create a 2D DP table `dp[n + 1][W + 1]`, where:
- `dp[i][j]` = Maximum value achievable using the first `i` items and a knapsack capacity of `j`.

### 2.2 State Transition
For each item `i` (from 1 to `n`) and each possible capacity `j` (from 1 to `W`):
1. **Exclude item `i`**: `dp[i][j] = dp[i - 1][j]` (value remains the same as without item `i`).
2. **Include item `i`**: If `weights[i - 1] ≤ j` (item fits), `dp[i][j] = values[i - 1] + dp[i - 1][j - weights[i - 1]]` (add item `i`’s value to the best value of the remaining capacity).

The recurrence relation is:
```
if weights[i - 1] ≤ j
dp[i][j] = max(dp[i - 1][j], values[i - 1] + dp[i - 1][j - weights[i - 1]])

if weights[i - 1] > j
dp[i][j] = dp[i - 1][j]
```

### 2.3 Base Case
- `dp[0][j] = 0` (no items → total value = 0 for any capacity `j`).
- `dp[i][0] = 0` (capacity = 0 → no items can be added → total value = 0).


## 3. Example Walkthrough
Let’s use:
- `weights = [2, 3, 4, 5]`
- `values = [3, 4, 5, 6]`
- `W = 8`

### Step 1: Initialize DP Table
| Items (i) \ Capacity (j)      | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|-------------------------------|---|---|---|---|---|---|---|---|---|
| 0 (no items)                  | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 1 (weight = 2, value = 3)     | 0 | 0 | 3 | 3 | 3 | 3 | 3 | 3 | 3 |
| 2 (weight = 3, value = 4)     | 0 | 0 | 3 | 4 | 4 | 7 | 7 | 7 | 7 |
| 3 (weight = 4, value = 5)     | 0 | 0 | 3 | 4 | 5 | 7 | 8 | 9 | 9 |
| 4 (weight = 5, value = 6)     | 0 | 0 | 3 | 4 | 5 | 7 | 8 | 9 | 10 |

### Step 2: Final Result
`dp[4][8] = 10` → The maximum value is 10 (achieved by selecting items with weights 3 and 5, values 4 and 6).


## 4. Code Implementation (c++)
```cpp
#include <iostream>

using namespace std;

const int N = 1010;

int n, m; // n is number of items, m is maximum weight capacity
int v[N], w[N]; // v = values, w = weights
int f[N][N];

int main() {
    cin >> n >> m;
    
    for (int i = 1; i <= n; i ++ ) cin >> v[i] >> w[i];
    
    for (int i = 1; i <= n; i ++ )
        for (int j = 0; j <= m;  j ++ ) {
            f[i][j] = f[i - 1][j];
            if (j >= w[i]) 
                f[i][j] = max(f[i - 1][j], f[i - 1][j - w[i]] + v[i]);
        }
                
    cout << f[n][m];
    
    return 0;
}
```


## 5. Space Optimization
The 2D DP table can be optimized to a 1D array (`dp[W + 1]`) since each row `i` only depends on row `i - 1`. The optimized code:
```cpp 
#include <iostream>

using namespace std;

const int N = 1010;

int n, m;
int f[N];

int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i ++ ) {
        int v, w;
        cin >> v >> w;
        for (int j = m ; j >= w; j -- )
            f[j] = max(f[j], f[j - w] + v);
    }

    cout << f[m];

    return 0;
}
```

### Time Complexity
- Both versions: `O(n * W)` (two nested loops over `n` items and `W` capacity).

### Space Complexity
- 2D version: `O(n * W)`
- 1D version: `O(W)` (significant improvement for large `n`).


## 6. Recommended Exercises