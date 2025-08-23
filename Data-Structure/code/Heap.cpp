#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int n;

template<typename T>
struct Heap {
    int s;
    T a[N];

    void down(int u) {
        int t = u;
        if (2 * u <= s && a[2 * u] > a[t]) t = 2 * u;
        if (2 * u + 1 <= s && a[2 * u + 1] > a[t]) t = 2 * u + 1;
        if (t != u) {
            swap(a[u], a[t]);
            down(t);
        }
    }

    void up(int u) {
        int t = u;
        while (t > 1 && a[t / 2] < a[t]) {
            swap(a[t / 2], a[t]);
            t /= 2;
        }
    }

    void push(T x) {
        a[ ++ s] = x;
        up(s);
    }

    void pop() {
        if (s) {
            swap(a[1], a[s -- ]);
            down(1);
        }
    }

    T top() {
        return a[1];
    }
};

Heap<int> h;

int main() {
    cin >> n;
    
    while (n -- ) {
        int opt, x;
        cin >> opt;
        if (opt == 1) {
            cin >> x;
            h.push(x);
        } 
        else if (opt == 2) h.pop();
        else cout << h.top() << endl;
    }

    return 0;
}