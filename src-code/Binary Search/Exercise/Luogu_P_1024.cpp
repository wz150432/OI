#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

const double eps = 1e-4;
const double INF = 2e9;

int t, n, m;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    double a, b, c, d;
    cin >> a >> b >> c >> d;
    
    auto f = [&] (double x) {
        return a * pow(x, 3) + b * pow(x, 2) + c * x + d;
    };

    auto calc = [&] (double l, double r) {
        if (f(l) * f(r) > 0) return INF;

        while (r - l > eps) {
            double mid = (l + r) / 2;
            if (f(l) * f(mid) <= 0) r = mid;
            else if (f(mid) * f(r) < 0) l = mid;
            else return INF;
        }
        
        return r;
    };

    for (int i = -100; i < 100; i ++ ) {
        double root = calc(i, i + 1);
        if (root != INF)
            cout << fixed << setprecision(2) << root << " " ;
    }

    return 0;
}