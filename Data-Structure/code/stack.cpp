#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int n;

template<typename T>
struct Stack {
    int idx;
    T a[N];

    bool empty() {
        return idx == 0;
    }

    void push(T x) {
        a[ ++ idx] = x;
    }

    void pop() {
        if (idx) idx -- ;
    }

    T top() {
        return a[idx];
    }
};

Stack<int> s;

int main() {
    cin >> n;

    while (n -- ) {
        int opt, x;
        cin >> opt;
        if (opt == 1) {
            cin >> x;
            s.push(x);
        } 
        else if (opt == 2) s.pop();
        else if (opt == 3) cout << (s.empty() ? "YES" : "NO") << endl;
        else cout << s.top() << endl;
    }

    return 0;
}