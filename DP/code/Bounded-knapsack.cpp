#include <iostream>
#include <deque>

using namespace std;

const int N = 1e5 + 10;

int n, m;
int f[N], g[N], f1[N][N];
int w[N], v[N], s[N];
    
void brute_force() {
    for (int i = 1 ; i <= n ; i ++ )
        for (int j = 0 ; j <= m ; j ++ )
            for (int k = 0 ; k <= s[i] ; k ++ )
                if (j >= k * v[i])
                    f1[i][j] = max(f1[i][j], f1[i - 1][j - k * v[i]] + k * w[i]);

    cout << f1[n][m] << endl;
}

void binary_optimization() {
    for (int i = 1 ; i <= n ; i ++ ) {
        int ss = 1;
        while (ss < s[i]) {
            int vv = ss * v[i];
            int ww = ss * w[i];
            s[i] -= ss;
            ss <<= 1;
            for (int j = m ; j >= vv ; j -- )
                f[j] = max(f[j], f[j - vv] + ww);
        }
        if (s[i]) {
            int vv = s[i] * v[i];
            int ww = s[i] * w[i];
            for (int j = m ; j >= vv ; j -- )
                f[j] = max(f[j], f[j - vv] + ww);
        }
    }

    cout << f[m];
}

void monotonic_queue_optimization() {
    deque<int> q;
    for (int i = 1 ; i <= n ; i ++ ) {
        memcpy(g, f, sizeof f);
        for (int j = 0 ; j < v[i] ; j ++ ) {
            q.clear();
            for (int k = j ; k <= m ; k += v[i]) {
                if (!q.empty() && q.front() < k - s[i] * v[i]) q.pop_front();
                if (!q.empty()) f[k] = max(f[k], g[q.front()] + (k - q.front()) / v[i] * w[i]);
                while (!q.empty() && g[q.back()] - (q.back() - j) / v[i] * w[i] <= g[k] - (k - j) / v[i] * w[i]) q.pop_back();
                q.push_back(k);
            }
        }
    }

    cout << f[m] << endl;
}

int main() {
    cin >> n >> m;
    for (int i = 1 ; i <= n ; i ++ )
        cin >> v[i] >> w[i] >> s[i];

    brute_force();
    monotonic_queue_optimization();
    binary_optimization();

    return 0;
}