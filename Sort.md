# We will introduce 3 common sorting algorithm
- ### Quick Sort: Generally $O(nlogn)$ worst-case $O(n^2)$
- ### Merge Sort: $O(nlogn)$
- ### Heap Sort: $O(nlogn)$

## I. Quick Sort
### Be based on divide and conquer idea, choose a pivot number. Let the numbers on the left be less or equal to the pivot number and the numbers on the right be strictly greater than the pivot number.
### Generally, we choose the middle number as the pivot number for quick sort.

$\newline$  
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
$\newline \newline$
## II. Merge Sort
### Be based on divide and conquer idea, we first sort the left-hand side and right-hand seperatly then make them into ordered sequences. After that, we merged the two ordered sequences, that is why this sorting algorithm called merge sort.  
`5 4 3 | 2 1` -> `3 4 5 | 1 2` -> `1 2 3 4 5`

$\newline$
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

### It also has some classic usages, like finding the number of the inversion pairs, we can also use the binary index tree to find inversion pairs too.
`Inversion pair is the pair of the element in the sequence which i smaller than j but value of ith element is greater than value of jth element`
```cpp
while (i <= mid && j <= r) {
    if (a[i] <= a[j]) tmp[cnt ++ ] = a[i ++ ];
    else {
        tmp[cnt ++ ] = a[j ++ ];
        res += i - mid + 1;
    }
}
```

$\newline \newline$
## III. Heap sort
###  First of all, we need to perform downward operations from floor n divided by 2 to 1 a successfully build a heap. We use a max heap and continuously swap the top element of the heap with the last element in the current heap. This way the elements from 1 to n to be in ascending order in the end, and it really important to perform downward operation before swaping the element.

$\newline$
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
