#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int n;

template<typename T>
struct Queue {
    int head, tail;
    T a[N];

    Queue() {
        head = tail = 0;
    }

    void push(T x) {
        a[tail ++ ] = x;
    }

    void pop() {
        if (head < tail) head ++ ;
    }

    bool empty() {
        return head == tail;
    }

    T front() {
        return a[head];
    }
};

Queue<int> q;

int main() {
    cin >> n;

    while (n -- ) {
        int opt, x;
        cin >> opt;
        if (opt == 1) {
            cin >> x;
            q.push(x);
        } 
        else if (opt == 2) q.pop();
        else if (opt == 3) cout << (q.empty() ? "YES" : "NO") << endl;
        else cout << q.front() << endl;
    }

    return 0;
}