# Sparse Table: Efficient Range Queries with O(1) Lookup  

In competitive programming and data analysis, we often need to answer range queries (like "what's the maximum value in this interval?") efficiently. While segment trees and binary indexed trees (Fenwick trees) are popular, the **Sparse Table** data structure stands out for its simplicity and speed—offering $O(1)$ query time after $O(n log n)$ preprocessing.  

Let’s dive into how Sparse Tables work, their implementation, and why they’re a go-to for static arrays (arrays that don’t change after initialization).  


## What Is a Sparse Table?  
A Sparse Table is a precomputed table that allows us to answer range queries (e.g., range maximum, minimum, or gcd) in constant time. It’s built on the idea of **precomputing answers for intervals of length $2^j$** and combining these precomputed results to answer arbitrary range queries.  

### Key Idea:  
For any interval $[l, r]$, we can find the largest $k$ such that $2^k \leq (r - l + 1)$. The interval $[l, r]$ can then be covered by two overlapping intervals of length $2^k$:  
- One starting at $l$ (covers $[l, l + 2^k - 1]$)  
- One ending at $r$ (covers $[r - 2^k + 1, r]$)  

The answer for $[l, r]$ is the combination (e.g., max, min) of the precomputed answers for these two intervals.  


## How to Build a Sparse Table  
Let’s focus on **range maximum queries (RMQ)** as an example. The steps generalize to other idempotent operations (operations where applying them multiple times doesn’t change the result, like min or gcd).  


### 1. Preprocessing: Building the Table  
We define a 2D array $f[i][j]$, where:  
- $i$ is the starting index of the interval.  
- $j$ represents the length of the interval as $2^j$.  

Thus, $f[i][j]$ stores the maximum value in the interval $[i, i + 2^j - 1]$.  

#### Recurrence Relation:  
- For $j = 0$ (interval length $2^0 = 1$): $f[i][0] = a[i]$ (the value itself).  
- For $j > 0$: Split the interval $[i, i + 2^j - 1]$ into two intervals of length $2^{j-1}$:  
  $
  f[i][j] = \max\left(f[i][j-1],\ f\left[i + 2^{j-1}\right][j-1]\right)
  $ 


### 2. Querying: Answering Range Maximum Queries  
To find the maximum in $[l, r]$:  
1. Compute $k = \lfloor \log_2(r - l + 1) \rfloor$ (the largest power of 2 fitting in the interval length).  
2. The result is the maximum of the two overlapping intervals:  
   $
   \max\left(f[l][k],\ f\left[r - 2^k + 1\right][k]\right)
   $  


## Full Implementation (C++)  
Here’s a complete Sparse Table implementation for range maximum queries:  

```cpp
#include <iostream>

using namespace std;

const int N = 2e5 + 10, M = 20;

int n, q;
int a[N];
int f[N][M];

int RMQ(int l, int r) {
    int k = floor(log(r - l + 1) / log(2));
    return max(f[l][k], f[r - (1 << k) + 1][k]);
}

int main() {
    cin >> n;

    for (int i = 1; i <= n; i ++ ) cin >> a[i];

    int k = floor(log(n) / log(2));
    for (int j = 0 ; j <= k; j ++ )
        for (int i = 1; i + (1 << j) - 1 <= n; i ++ ) {
            if (!j) f[i][j] = a[i];
            else f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }

    cin >> q;

    while (q -- ) {
        int l, r;
        cin >> l >> r;
        cout << RMQ(l, r) << endl;
    }

    return 0;
}
```


## Time Complexity Analysis  
- **Preprocessing**: $O(n \log n)$. We fill a table of size $n \times \log n$, with each entry computed in $O(1)$ time.  
- **Query**: $O(1)$. Each query combines two precomputed intervals, requiring constant time.  


## When to Use Sparse Tables  
Sparse Tables shine in scenarios where:  
- The array is **static** (no updates after initialization). They are not efficient for dynamic arrays (use segment trees instead).  
- Queries are **idempotent** (e.g., max, min, gcd, lcm). For non-idempotent operations (e.g., sum), overlapping intervals would lead to incorrect results.  
- You need **fast query times** $O(1)$ and can afford $O(n log n)$ preprocessing.  


## Advantages Over Other Structures  
| Structure       | Preprocessing Time | Query Time | Handles Updates? |  
|-----------------|--------------------|------------|------------------|  
| Sparse Table    | $O(n log n)$        | $O(1)$       | No               |  
| Segment Tree    | $O(n)$               | $O(log n)$   | Yes              |  
| Naive Approach  | $O(1)$               | $O(n)$       | N/A              |  


## Example Walkthrough  
Let’s say we have an array $a = [3, 1, 4, 2, 5]$.  

1. **Preprocessing**:  
   - $j = 0$ (length 1): $f[i][0] = a[i] \implies [3, 1, 4, 2, 5]$  
   - $j = 1$ (length 2): $f[i][1] = \max(a[i], a[i + 1]) \implies [3, 4, 4, 5]$  
   - $j = 2$ (length 4): $f[i][2] = \max(f[i][1], f[i + 2][1]) \implies [4, 5]$  

2. **Query $[1, 4]$** (values [3, 1, 4, 2]):  
   - Length = 4, so $k = \log_2(4) = 2$.  
   - Result = $\max(f[1][2], f[4 - 4 + 1][2]) = \max(f[1][2], f[1][2]) = 4$.  


## Key Takeaways  
- Sparse Tables are ideal for static arrays and idempotent range queries.  
- Preprocessing takes $O(n log n)$ time, but queries are $O(1)$.  
- The core idea is precomputing intervals of length $2^j$ and combining them to answer arbitrary ranges.  

Next time you need to handle range max/min queries on a static array, give Sparse Tables a try—they’re simple to implement and blazingly fast!

## Recomended Exercises 