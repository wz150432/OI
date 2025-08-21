#include <iostream>

using namespace std;

const int N = 1010;

int n, m;
int f[N];

int main() {
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i ++ ) {
        int v, w;
        cin >> v >> w;
        for (int j = m ; j >= v ; j -- ) 
            f[j] = max(f[j], f[j - v] + w);
    }

    cout << f[m];

    return 0;
}