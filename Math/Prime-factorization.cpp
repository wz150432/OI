#include <iostream>

using namespace std;

int n;

void Prime_factorization(int n) {
    for (int i = 2 ; i <= n / i ; i ++ ) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) {
                n /= i;
                cnt ++;
            }
            cout << i << " " << cnt << endl;
        }
    }
    if (n != 1) cout << n << " " << 1;
}

int main() {
    cin >> n;

    Prime_factorization(n);

    return 0;
}