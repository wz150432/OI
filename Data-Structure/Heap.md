# A Practical Guide to Heaps: Concepts, Implementations, and Code  
Heaps are a foundational **complete binary tree-based data structure** optimized for efficient access to the "extreme" element (maximum or minimum). They power algorithms like heap sort and priority queues, and their simplicity makes them a staple in coding interviews and real-world applications. This post breaks down heap fundamentals, covers both max-heaps and min-heaps, and includes a reusable C++ implementation.


## 1. What Is a Heap?  
A heap is defined by two core properties:  
1. **Complete Binary Tree**: All levels are fully filled except possibly the last, which is left-aligned. This allows efficient array-based storage (no pointers needed).  
2. **Heap Property**: A strict rule governing parent-child relationships, which splits heaps into two types:  

   - **Max-Heap**: For every node $u$, the value of $u$ is **greater than or equal to** the values of its children. Formally:  
  $value(u) \geq value(\text{left child of } u) \quad \text{and} \quad value(u) \geq value(\text{right child of } u)$  
  The root holds the **maximum element** of the heap.  

   - **Min-Heap**: For every node $u$, the value of $u$ is **less than or equal to** the values of its children. Formally:  
     $value(u) \leq value(\text{left child of } u) \quad \text{and} \quad value(u) \leq value(\text{right child of } u)$  
     The root holds the **minimum element** of the heap.


## 2. Array-Based Heap Representation  
Since heaps are complete binary trees, we can store them in arrays using **1-based indexing** (simplifies parent/child calculations). For a node at index $i$:  
- Left child index: $2i$  
- Right child index: $2i + 1$  
- Parent index: $\lfloor i/2 \rfloor$ (integer division) 

## 3. Core Heap Operations  
All heap operations rely on two helper functions to restore the heap property after modifications: `down()` (adjust a node downward) and `up()` (adjust a node upward). We’ll explain both for max-heaps and min-heaps.


### 3.1 Helper 1: `down(int u)` – Fix a Node by Moving It Down  
Use `down()` when a node violates the heap property by being "too small" (max-heap) or "too large" (min-heap). It swaps the node with its appropriate child and recurses until the property is restored.  

#### Max-Heap `down()` Logic:  
1. Let $\text{largest} = u$ (track the index of the largest value among $u$ and its children).  
2. If the left child exists and is larger than $\text{largest}$, update $\text{largest}$ to the left child’s index.  
3. If the right child exists and is larger than $\text{largest}$, update $\text{largest}$ to the right child’s index.  
4. If $\text{largest} \neq u$, swap the values at $u$ and $\text{largest}$, then call `down(largest)` to fix the new position.  

#### Min-Heap `down()` Logic:  
Replace "largest" with "smallest" and compare for smaller values instead:  
1. Let $\text{smallest} = u$.  
2. If the left child exists and is smaller than $\text{smallest}$, update $\text{smallest}$.  
3. If the right child exists and is smaller than $\text{smallest}$, update $\text{smallest}$.  
4. Swap and recurse if $\text{smallest} \neq u$.  


### 3.2 Helper 2: `up(int u)` – Fix a Node by Moving It Up  
Use `up()` when a node violates the heap property by being "too large" (max-heap) or "too small" (min-heap). It swaps the node with its parent and repeats until the property is restored.  

#### Max-Heap `up()` Logic:  
While the node has a parent ($u > 1$) and the node’s value is larger than its parent’s value:  
1. Swap the node with its parent.  
2. Update $u$ to the parent’s index ($u = \lfloor u/2 \rfloor$).  

#### Min-Heap `up()` Logic:  
While the node has a parent ($u > 1$) and the node’s value is smaller than its parent’s value:  
1. Swap the node with its parent.  
2. Update $u$ to the parent’s index.  


### 3.3 Key Operations (Max-Heap & Min-Heap)  
All operations run in $O(\log n)$ time, as they traverse the heap’s height ($\log n$ for a complete binary tree with $n$ nodes).  

| Operation       | Max-Heap Steps                                                                 | Min-Heap Steps                                                                 |
|-----------------|--------------------------------------------------------------------------------|--------------------------------------------------------------------------------|
| `push(x)`       | 1. Append $x$ to the end of the array ($a[++s] = x$).<br>2. Call `up(s)` to fix the heap property. | 1. Append $x$ to the end of the array ($a[++s] = x$).<br>2. Call `up(s)` to fix the heap property. |
| `pop()`         | 1. Swap the root ($a[1]$) with the last element ($a[s]$).<br>2. Shrink the heap ($s--$).<br>3. Call `down(1)` to fix the heap property. | 1. Swap the root ($a[1]$) with the last element ($a[s]$).<br>2. Shrink the heap ($s--$).<br>3. Call `down(1)` to fix the heap property. |
| `top()`         | Return the root value ($a[1]$) – the maximum element.                     | Return the root value ($a[1]$) – the minimum element.                     |


## 4. C++ Heap Implementation (Template)  
Below is a generic implementation that supports max-heaps. It uses templates to work with any comparable data type (e.g., `int`, `double`).  

```cpp
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
```


## 5. Recommended Exercises
