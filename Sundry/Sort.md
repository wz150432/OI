# Essential Programming Reference: Algorithms, Tools & Testing Workflows  

This guide compiles core programming knowledge—from sorting algorithms and fast math techniques to utility functions, I/O tools, and pair checking workflows—into a single, practical resource. It’s tailored for developers and competitive programmers aiming to strengthen their foundational skills.  


## 1. Optimized Breakdown of 3 Common Sorting Algorithms  
Sorting is a cornerstone of programming, and selecting the right algorithm depends on priorities like stability, space efficiency, or speed. Below are three widely used sorting methods, optimized for real-world performance.  

| Algorithm   | Time Complexity       | Key Advantage                          | Use Case                                  |  
|-------------|-----------------------|----------------------------------------|-------------------------------------------|  
| Quick Sort  | Avg: O(nlogn); Worst: O(n²) | Fast in practice; minimal extra space  | General-purpose sorting (e.g., numeric arrays) |  
| Merge Sort  | O(nlogn)              | Stable (preserves equal element order)  | Scenarios needing consistent order (e.g., sorting objects by multiple keys) |  
| Heap Sort   | O(nlogn)              | In-place (O(1) extra space)            | Memory-constrained systems (e.g., embedded devices) |  


### 1.1 Quick Sort  
#### Core Principle (Optimized Version)  
Quick Sort leverages the **divide-and-conquer** approach, with its biggest optimization focused on **pivot selection**—the key to avoiding slow worst-case behavior:  
- Instead of using a fixed first/last element as the pivot, pick the **middle element** (calculated via `l + r >> 1`, a faster bitwise alternative to `(l + r) / 2`). This nearly eliminates O(n²) time complexity (which plagues fixed-pivot setups for fully sorted arrays).  
- Partitioning uses two pointers (`i` and `j`) to split the array:  
  - `i` starts at `l - 1` and moves right until it finds an element ≥ pivot.  
  - `j` starts at `r + 1` and moves left until it finds an element ≤ pivot.  
  - If `i < j`, swap the elements to place smaller values left of the pivot and larger values right.  
- Recursively sort the left subarray (from `l` to `j`) and right subarray (from `j + 1` to `r`).  

#### Code (Unchanged for Practicality)  
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, a[N];

void quick_sort(int l, int r) {
    if (l >= r) return;
    int i = l - 1, j = r + 1, x = a[l + r >> 1];
    while (i < j) {
        while (a[ ++ i] < x);
        while (a[ -- j] > x);
        if (i < j) swap(a[i], a[j]);
    }
    quick_sort(l, j);
    quick_sort(j + 1, r);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++ ) cin >> a[i];
    quick_sort(1, n);
    for (int i = 1; i <= n; i ++ ) cout << a[i] << " ";
    return 0;
}
```

#### Key Optimization Notes  
- Bitwise operations like `l + r >> 1` are faster than arithmetic division and avoid overflow for arrays up to 1e5 elements.  
- Pre-increment/decrement (` ++ i`/` -- j`) skips redundant initial checks (e.g., no need to verify `a[l]` or `a[r]` first), speeding up the pointer scan.  


### 1.2 Merge Sort  
#### Core Principle (Optimized Version)  
Merge Sort’s biggest strengths are **stable sorting** (equal elements keep their original order) and a guaranteed O(nlogn) time complexity—thanks to its divide-and-merge workflow:  
- **Divide**: Recursively split the array into two halves (at `mid = l + r >> 1`) until each subarray has 1 element (naturally sorted).  
- **Merge**: Use a temporary array `tmp` to combine two sorted subarrays:  
  - Use two pointers (`i` for the left subarray, `j` for the right) to compare elements and add the smaller one to `tmp`.  
  - After one subarray is exhausted, append the remaining elements of the other to `tmp`.  
  - Copy `tmp` back to the original array to maintain sorted order.  

#### Code (Unchanged for Practicality)  
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, a[N], tmp[N];

void merge_sort(int l, int r) {
    if (l >= r) return;
    int mid = l + r >> 1;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);

    int i = l, j = mid + 1, cnt = 0;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) tmp[cnt ++ ] = a[i ++ ];
        else tmp[cnt ++ ] = a[j ++ ];
    }
    while (i <= mid) tmp[cnt ++ ] = a[i ++ ];
    while (j <= r) tmp[cnt ++ ] = a[j ++ ];

    for (int k = l; k <= r; k ++ ) a[k] = tmp[k - l];
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++ ) cin >> a[i];
    merge_sort(1, n);
    for (int i = 1; i <= n; i ++ ) cout << a[i] << " ";
    return 0;
}
```

#### Classic Extension: Inversion Pair Count  
An inversion pair is a pair of elements where `i < j` but `a[i] > a[j]`. Merge Sort can count these pairs naturally during the merge step—simply add the number of remaining elements in the left subarray when a right element is smaller:  
```cpp
// Add a "res" variable (initialized to 0) to store inversion count
while (i <= mid && j <= r) {
    if (a[i] <= a[j]) tmp[cnt ++ ] = a[i ++ ];
    else {
        tmp[cnt ++ ] = a[j ++ ];
        res += mid - i + 1; // All left elements from i to mid form pairs with a[j-1]
    }
}
```


### 1.3 Heap Sort  
#### Core Principle (Optimized Version)  
Heap Sort relies on a **max-heap** (a complete binary tree where parent nodes are ≥ children) and uses **in-place adjustment** to minimize extra space:  
1. **Heap Construction**: Start from the last non-leaf node (`n / 2`) and perform a "downward adjustment" (`down` function) to convert the array into a max-heap. This ensures the root (index 1) is the largest element.  
2. **Sorting Step**:  
   - Swap the root (max element) with the last element of the current heap (index `s`, where `s` is the heap size).  
   - Decrease the heap size (`s -- `) to exclude the sorted element.  
   - Re-run `down` on the new root to restore the max-heap property.  
   - Repeat until the heap size is 1—this leaves the array sorted in ascending order.  

#### Code (Unchanged for Practicality)  
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, s, a[N];

void down(int u) {
    int t = u; // t stores the index of the largest element (current node or children)
    if (2 * u <= s && a[t] < a[2 * u]) t = 2 * u;   // Compare with left child
    if (2 * u + 1 <= s && a[t] < a[2 * u + 1]) t = 2 * u + 1; // Compare with right child
    if (t != u) { // If current node is not the largest, swap and recurse
        swap(a[t], a[u]);
        down(t);
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++ ) cin >> a[i];
    s = n;

    // Build max-heap
    for (int i = n / 2; i ; i -- ) down(i);

    while (s) {
        down(1);
        swap(a[1], a[s ++ ]);
    }

    for (int i = 1; i <= n; i ++ ) cout << a[i] << " ";
    return 0;
}
```

#### Key Optimization Notes  
- The variable `s` tracks the current heap size, avoiding array slicing and enabling in-place sorting (O(1) extra space).  
- The `down` function is critical: it efficiently restores the max-heap by only swapping with the largest child, minimizing unnecessary operations.  