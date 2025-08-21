#include <iostream>

using namespace std;

int n;

int euler(int x) {
    int res = x;
    for (int i = 2; i <= x / i ; i ++ ) {
        if (x % i == 0) {
            while (x % i == 0) x /= i;
            res = res / i * (i - 1);
        }
    }
    if (x != 1) res = res / x * (x - 1);

    return res;
}

int main() {
    cin >> n;

    cout << euler(n);

    return 0;
}