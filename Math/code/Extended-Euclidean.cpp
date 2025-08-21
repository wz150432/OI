#include <iostream>

using namespace std;

int a, b;

int exgcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int main() {
    cin >> a >> b;

    int x, y;
    exgcd(a, b, x, y);

    cout << x << " " << y;

    return 0;
}