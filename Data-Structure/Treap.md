# Treap: Merging BSTs and Heaps for Balanced Performance  

A **Treap** (tree + heap) is a versatile data structure that combines the ordered properties of a **binary search tree (BST)** with the self-balancing capabilities of a **heap**. This hybrid design ensures efficient average-case performance for insertion, deletion, and advanced queries like rank or predecessor/successor lookup—all in $O(\log n)$ time.  


## Key Properties of a Treap  
A Treap maintains two critical properties for each node:  

1. **BST Property**: For any node with key \(k\):  
   - All keys in the left subtree are \(< k\).  
   - All keys in the right subtree are \(> k\).  

2. **Max-Heap Property**: Each node has a random priority value, and for any node:  
   $$
   \text{priority}(u) \geq \text{priority}(\text{left child of } u) \quad \text{and} \quad \text{priority}(u) \geq \text{priority}(\text{right child of } u)
   $$  

This dual property guarantees balance. The randomness of priorities prevents worst-case skewed trees (unlike unbalanced BSTs), ensuring $O(\log n)$ average height.  


## Core Components  

### 1. Node Structure  
Each node stores:  
- `key`: Value for BST ordering.  
- `val` (priority): Random value for heap balancing.  
- `l`/`r`: Pointers to left/right children.  
- `cnt`: Count of duplicate keys.  
- `sz`: Size of the subtree rooted at this node (for rank queries).  

```cpp
struct treap {
    int l, r;    // Children
    int key, val; // BST key and heap priority
    int cnt, sz;  // Duplicate count and subtree size
} tr[N];
```


### 2. Rotations: Preserving Balance  
When insertions/deletions disrupt the heap property, **rotations** (zig/zag) rebalance the tree while maintaining BST order.  

#### Zig (Right Rotation)  
Fixes when a left child has higher priority than its parent:  
```cpp
void zig(int& u) {
    int v = l(u);          // v = left child of u
    l(u) = r(v);           // u's left = v's right
    r(v) = u;              // v's right = u
    u = v;                 // v becomes new root of the subtree
    pushup(u);             // Update subtree sizes
    pushup(r(u));
}
```

#### Zag (Left Rotation)  
Fixes when a right child has higher priority than its parent:  
```cpp
void zag(int& u) {
    int v = r(u);          // v = right child of u
    r(u) = l(v);           // u's right = v's left
    l(v) = u;              // v's left = u
    u = v;                 // v becomes new root of the subtree
    pushup(u);             // Update subtree sizes
    pushup(l(u));
}
```


### 3. Insertion  
To insert a key \(k\):  
1. Traverse the tree like a BST to find the insertion point.  
2. Create a new node with a random priority.  
3. Rotate upward if the new node’s priority violates the heap property.  

```cpp
void insert(int& u, int key) {
    if (!u) u = new_node(key); // Create new node if position is empty
    else if (tr[u].key == key) tr[u].cnt++; // Increment duplicate count
    else if (tr[u].key < key) { // Insert into right subtree
        insert(tr[u].r, key);
        if (tr[tr[u].r].val > tr[u].val) zag(u); // Rotate left if needed
    } else { // Insert into left subtree
        insert(tr[u].l, key);
        if (tr[tr[u].l].val > tr[u].val) zig(u); // Rotate right if needed
    }
    pushup(u); // Update subtree size
}
```


### 4. Deletion  
To delete a key \(k\):  
1. Traverse to the node with key \(k\).  
2. If duplicates exist, decrement `cnt`.  
3. If the node is internal, rotate it downward (using the child with higher priority) until it becomes a leaf, then remove it.  

```cpp
void remove(int& u, int key) {
    if (!u) return; // Key not found
    if (tr[u].key == key) {
        if (tr[u].cnt > 1) tr[u].cnt--; // Decrement duplicate count
        else {
            if (tr[u].l || tr[u].r) { // Node has children
                // Rotate with child of higher priority
                if (!tr[u].r || tr[tr[u].l].val > tr[tr[u].r].val) {
                    zig(u);
                    remove(tr[u].l, key);
                } else {
                    zag(u);
                    remove(tr[u].r, key);
                }
            } else u = 0; // Remove leaf node
        }
    }
    else if (tr[u].key > key) remove(tr[u].l, key); // Search left
    else remove(tr[u].r, key); // Search right
    pushup(u); // Update subtree size
}
```


### 5. Advanced Queries  

#### Rank of a Key  
The rank of \(k\) is the number of elements \(< k\) plus 1:  
```cpp
int find_rank_by_val(int u, int key) {
    if (!u) return 1;
    if (tr[u].key == key) return tr[tr[u].l].sz + 1;
    if (tr[u].key > key) return find_rank_by_val(tr[u].l, key);
    return tr[tr[u].l].sz + tr[u].cnt + find_rank_by_val(tr[u].r, key);
}
```

#### k-th Smallest Element  
To find the \(k\)-th smallest element, use subtree sizes to navigate:  
```cpp
int find_val_by_rank(int u, int rank) {
    if (!u) return INF;
    if (tr[tr[u].l].sz >= rank) return find_val_by_rank(tr[u].l, rank);
    if (tr[tr[u].l].sz + tr[u].cnt >= rank) return tr[u].key;
    return find_val_by_rank(tr[u].r, rank - tr[tr[u].l].sz - tr[u].cnt);
}
```

#### Predecessor and Successor  
- **Predecessor**: Largest element \(< k\):  
  ```cpp
  int find_prev(int u, int key) {
      if (!u) return -INF;
      if (tr[u].key >= key) return find_prev(tr[u].l, key);
      return max(tr[u].key, find_prev(tr[u].r, key));
  }
  ```  

- **Successor**: Smallest element \(> k\):  
  ```cpp
  int find_next(int u, int key) {
      if (!u) return INF;
      if (tr[u].key <= key) return find_next(tr[u].r, key);
      return min(tr[u].key, find_next(tr[u].l, key));
  }
  ```

## Full Implementation  

```cpp
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
```

## Time Complexity  
- **Insert/Delete**: $O(\log n)$ average case. The random priorities ensure the tree height is $O(\log n)$ with high probability.  
- **Rank/Value Queries**: $O(\log n)$, as they traverse the tree from root to leaf.  


## Why Choose Treaps?  
- **Simplicity**: Easier to implement than AVL or red-black trees, with no complex rebalancing rules.  
- **Efficiency**: Matches the average-case performance of balanced BSTs for all operations.  
- **Flexibility**: Natively handles duplicates and supports order statistics (rank, k-th element).  

Treaps are a staple in competitive programming and systems requiring fast, dynamic data management—proof that combining two classic structures can yield something greater than the sum of its parts!