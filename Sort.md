# Optimized Explanation of 3 Common Sorting Algorithms (Code Unchanged)
- ### Quick Sort: Generally $O(nlogn)$, worst-case $O(n^2)$ (optimized by choosing middle pivot to reduce worst-case probability)
- ### Merge Sort: $O(nlogn)$ (stable sorting, suitable for scenarios requiring order preservation of equal elements)
- ### Heap Sort: $O(nlogn)$ (in-place sorting, minimal extra space consumption)


## I. Quick Sort
### Core Principle (Optimized Interpretation)
Based on the **divide-and-conquer idea**, the key to optimizing efficiency lies in **pivot selection**:
- Choosing the **middle element** (instead of fixed first/last element) as the pivot effectively avoids the worst-case $O(n^2)$ time complexity caused by extremely sorted (ascending/descending) arrays.
- The partitioning process uses double pointers to alternately scan from both ends: elements smaller than the pivot are moved to the left, and elements larger than the pivot to the right, ensuring clear division of the array.

### Code (Unchanged)
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n;
int a[N];

void quick_sort(int l, int r) {
    if (l >= r) return ;
    int i = l - 1, j = r + 1, x = a[l + r >> 1];
    while (i < j) {
        while (a[ ++ i] < x);
        while (a[ -- j] > x);
        if (i < j) swap(a[i], a[j]);
    }

    quick_sort(l, j), quick_sort(j + 1, r);
}

int main() {
    cin >> n;

    for (int i = 1; i <= n; i ++ ) cin >> a[i];

    quick_sort(1, n);

    for (int i = 1; i <= n; i ++ ) cout << a[i] << " " ;

    return 0;
}
```

### Supplementary Optimization Notes
- The expression `l + r >> 1` is equivalent to `(l + r) / 2`, but uses bitwise operations for faster calculation (note: no overflow for arrays within the range of $1e5$ elements).
- The double pointers `i` and `j` start from `l-1` and `r+1` respectively, and use pre-increment/decrement (`++i`/`--j`) to avoid redundant initial checks, improving scanning efficiency.


## II. Merge Sort
### Core Principle (Optimized Interpretation)
The core advantage of merge sort lies in **stable sorting and guaranteed $O(nlogn)$ time complexity**:
- The "divide" step splits the array into two halves, and recursively sorts each half—this process ensures that subarrays are always sorted before merging.
- The "merge" step uses a temporary array `tmp` to combine two sorted subarrays, which is the key to maintaining stability (equal elements retain their original relative order).

### Code (Unchanged)
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n;
int a[N], tmp[N];

void merge_sort(int l, int r) {
    if (l >= r) return ;

    int mid = l + r >> 1;
    merge_sort(l, mid), merge_sort(mid + 1, r);

    int i = l, j = mid + 1, cnt = 0;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) tmp[cnt ++ ] = a[i ++ ];
        else tmp[cnt ++ ] = a[j ++ ];
    }

    while (i <= mid) tmp[cnt ++ ] = a[i ++ ];
    while (j <= r) tmp[cnt ++ ] = a[j ++ ];

    for (int i = l; i <= r; i ++ ) a[i] = tmp[i - l];
}

int main() {
    cin >> n;

    for (int i = 1; i <= n; i ++ ) cin >> a[i];

    merge_sort(1, n);

    for (int i = 1; i <= n; i ++ ) cout << a[i] << " " ;

    return 0;
}
```

### Classic Extension: Inversion Pair Count (Code Unchanged)
An inversion pair refers to a pair of elements where **index $i < j$ but value $a[i] > a[j]$**. The merge sort process can naturally count inversion pairs by leveraging the order of merged subarrays:
```cpp
while (i <= mid && j <= r) {
    if (a[i] <= a[j]) tmp[cnt ++ ] = a[i ++ ];
    else {
        tmp[cnt ++ ] = a[j ++ ];
        res += i - mid + 1; // All remaining elements in the left subarray form inversion pairs with a[j-1]
    }
}
```


## III. Heap Sort
### Core Principle (Optimized Interpretation)
Heap sort relies on the **max-heap structure** and optimizes space by using "in-place adjustment":
1. **Heap Construction**: Starting from the last non-leaf node ( $\lfloor \frac {n}{2} \rfloor$ ), perform a "downward adjustment" to convert the array into a max-heap (parent node value ≥ child node value)—this step ensures the root is the maximum element.
3. **Sorting Process**: Swap the root (max element) with the last element of the current heap, then reduce the heap size and re-adjust the new root downward. Repeating this places max elements at the end in turn, forming an ascending order.

### Code (Unchanged)
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, s;
int a[N];

void down(int u) {
    int t = u;
    if (2 * u <= s && a[t] < a[2 * u]) t = 2 * u;
    if (2 * u + 1 <= s && a[t] < a[2 * u + 1]) t = 2 * u + 1;
    if (t != u) {
        swap(a[t], a[u]);
        down(t);
    }
}

int main() {
    cin >> n;

    for (int i = 1; i <= n; i ++ ) cin >> a[i];

    s = n;
    for (int i = n / 2 ; i ; i -- ) down(i);

    while (s) {
        down(1);
        swap(a[1], a[s -- ]);
    }

    for (int i = 1 ; i <= n ; i ++ ) cout << a[i] << " " ;

    return 0;
}
```
### Key Optimization Reminder
- The variable `s` represents the current size of the heap, avoiding repeated array slicing and achieving in-place sorting (space complexity $O(1)$ ).
- The `down` function is the core: it always selects the largest element among the current node and its children for swapping, ensuring the heap property is maintained after each adjustment.
