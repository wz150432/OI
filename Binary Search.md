# Binary Search
## Time complexity $O(logn)$
- Interger binary search
- Real number binary seach

$\newline$
## I. Interger binary search
The check function should be written according to the requirements of the problem
$\newline$
we can divide the interval `[l, r]` into `[l, mid - 1]` and `[mid, r]`.
The most important thing is let `mid = (l + r + 1) >> 1` rathar than `mid = (l + r) >> 1`, this is for rigorous editing conditions
`l + 1 = r` if we use `mid = (l + r) >> 1` and check function return true. The program will gets into an infinite loop.
$\newline$
```cpp
int binary_search1() {
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }

    return r;
}
```
$\newline$
we can divide the interval `[l, r]` into `[l, mid]` and `[mid + 1, r]`.
The most important thing is let `mid = (l + r) >> 1` rathar than `mid = (l + r + 1) >> 1`, this is for rigorous editing conditions
`l + 1 = r` if we use `mid = (l + r + 1) >> 1` and check function return true. The program will enter an infinite loop.
$\newline$
```cpp
int binary_search2() {
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid
        else l = mid + 1;
    }

    return r;
}
```

## Real number binary search
First, we need to determine a precision, generally we have a precision that is two digits higher than the required one.
We think $10^{-x-2}$ digit is zero. x is the precision given by the problem.

```cpp
int binary_search3() {
    double none = 1e-8;
    int l = -100, r = 100;
    while (r - l > none) {
        int mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
}
```
