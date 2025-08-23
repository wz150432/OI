#include <iostream>

using namespace std;

const int N = 1e5 + 10;
const int INF = 2e9 + 10;

int n;
int root, idx;

struct treap {
    int l, r;
    int key, val;
    int cnt, sz;
}tr[N];

#define u(x) tr[x]
#define l(x) tr[x].l
#define r(x) tr[x].r

void pushup(int u) {
    u(u).sz = u(l(u)).sz + u(r(u)).sz + u(u).cnt;
}

int new_node(int key) {
    u( ++ idx).key = key;
    u(idx).val = rand();
    u(idx).sz = u(idx).cnt = 1;
    return idx;
}

void build() {
    new_node(-INF), new_node(INF);
    root = 1, tr[1].r = 2;
    pushup(root);
}

void zig(int& u) {
    int v = l(u);
    l(u) = r(l(u));
    r(v) = u;
    u = v;
    pushup(u);
    pushup(r(u));
}

void zag(int& u) {
    int v = r(u);
    r(u) = l(r(u));
    l(v) = u;
    u = v;
    pushup(u);
    pushup(l(u));
}

void insert(int& u, int key) {
    if (!u) u = new_node(key);
    else if (u(u).key == key) u(u).cnt ++ ;
    else if (u(u).key < key) {
        insert(r(u), key);
        if (u(r(u)).val > u(u).val) zag(u);
    } else {
        insert(l(u), key);
        if (u(l(u)).val > u(u).val) zig(u);
    }
    pushup(u);
}

void remove(int& u, int key) {
    if (!u) return ;
    else if (u(u).key == key) {
        if (u(u).cnt > 1) u(u).cnt -- ;
        else {
            if (l(u) || r(u)) {
                if (!r(u) || u(l(u)).val > u(r(u)).val) {
                    zig(u);
                    remove(l(u), key);
                } else {
                    zag(u);
                    remove(r(u), key);
                }
            } else u = 0;
        }
    }
    else if (u(u).key > key) remove(l(u), key);
    else remove(r(u), key);
    pushup(u);
}

int find_rank_by_val(int u, int key) {
    if (!u) return 1;
    else if (u(u).key == key) return u(l(u)).sz + 1;
    else if (u(u).key > key)  return find_rank_by_val(l(u), key);
    return u(l(u)).sz + u(u).cnt + find_rank_by_val(r(u), key);
}

int find_val_by_rank(int u, int rank) {
    if (!u) return INF;
    else if (u(l(u)).sz >= rank) return find_val_by_rank(l(u), rank);
    else if (u(l(u)).sz + u(u).cnt >= rank) return u(u).key;
    return find_val_by_rank(r(u), rank - u(l(u)).sz - u(u).cnt);
}

int find_prev(int u, int key) {
    if (!u) return -INF;
    else if (u(u).key >= key) return find_prev(l(u), key);
    return max(u(u).key, find_prev(r(u), key));
} 

int find_next(int u, int key) {
    if (!u) return INF;
    else if (u(u).key <= key) return find_next(r(u), key);
    return min(u(u).key, find_next(l(u), key));
}

int main() {
    build();

    cin >> n;

    while (n -- ) {
        int opt, x;
        cin >> opt >> x;
        if (opt == 1) insert(root, x);
        if (opt == 2) remove(root, x);
        if (opt == 3) cout << find_rank_by_val(root, x) - 1 << endl;
        if (opt == 4) cout << find_val_by_rank(root, x + 1) << endl;
        if (opt == 5) cout << find_prev(root, x) << endl;
        if (opt == 6) cout << find_next(root, x) << endl;
    }

    return 0;
}