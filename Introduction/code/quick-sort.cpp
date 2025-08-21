#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int n;
int a[N];

void quick_sort(int l, int r) {
    if (l >= r) return ;

    int i = l - 1, j = r + 1, x = a[(l + r) >> 1];
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