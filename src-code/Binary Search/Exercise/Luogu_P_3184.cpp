#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

int t, n, m;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int q; // q 次询问
    cin >> n >> q;

    vi arr(n); // n 个干草的位置
    for (auto& x : arr) cin >> x;

    sort(begin(arr), end(arr));

    while (q -- ) {
        int a, b, l, r;
        cin >> a >> b;

        // 第一个 >= a 的干草的位置 
        l = 0, r = n - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (arr[mid] >= a) r = mid;
            else l = mid + 1;
        }
        if (arr[r] < a) r ++ ;  
        int pos = r;     

        // 最后一个 <= b 的干草的位置
        l = 0, r = n - 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (arr[mid] <= b) l = mid;
            else r = mid - 1;
        }
        if (arr[l] > b) l -- ;

        cout << l - pos + 1 << endl;
    }
    

    return 0;
}