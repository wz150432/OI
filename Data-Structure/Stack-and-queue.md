# Stack and Queue: Essential Linear Data Structures with C++ Implementations  

Linear data structures—where elements follow a sequential order—are the backbone of programming. Among them, **Stacks** and **Queues** stand out for their simplicity and wide use in algorithms (e.g., depth-first search for stacks, breadth-first search for queues). This post breaks down their core concepts, operations, and template-based C++ implementations, using your code as a practical reference.


## 1. Stack: Last-In-First-Out (LIFO)  
A stack is a "one-ended" structure where elements are added and removed from the **same end** (called the "top"). Think of a stack of plates: you can only add a new plate on top or take the top plate off.  

### Key Property: LIFO  
The last element inserted is the first one to be removed. Formally:  
$$
\text{Insert Order: } e_1 \rightarrow e_2 \rightarrow e_3 \quad \Rightarrow \quad \text{Remove Order: } e_3 \rightarrow e_2 \rightarrow e_1
$$  


### Core Operations  
All stack operations run in **O(1)** time (constant time), as they only modify or access the top element.  

| Operation | Description                                  | Edge Case Handling               |
|-----------|----------------------------------------------|-----------------------------------|
| `push(x)` | Add element `x` to the top of the stack.     | None (assumes array size is sufficient). |
| `pop()`   | Remove the top element from the stack.       | Do nothing if the stack is empty. |
| `top()`   | Return the top element (without removing it).| Undefined if empty (handled by user logic). |
| `empty()` | Check if the stack has no elements.          | Returns `true` if empty, `false` otherwise. |


### Template-Based Stack Implementation  
Your code uses a template to support any data type (e.g., `int`, `double`, `string`). We’ll walk through it with explanations:  

```cpp
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
```


## 2. Queue: First-In-First-Out (FIFO)  
A queue is a "two-ended" structure where elements are added to one end (the "tail") and removed from the other (the "head"). Think of a line at a store: the first person to join is the first to be served.  

### Key Property: FIFO  
The first element inserted is the first one to be removed. Formally:  
$$
\text{Insert Order: } e_1 \rightarrow e_2 \rightarrow e_3 \quad \Rightarrow \quad \text{Remove Order: } e_1 \rightarrow e_2 \rightarrow e_3
$$  


### Core Operations  
Like stacks, all queue operations run in **O(1)** time—they only modify the head or tail.  

| Operation   | Description                                  | Edge Case Handling               |
|-------------|----------------------------------------------|-----------------------------------|
| `push(x)`   | Add element `x` to the tail of the queue.    | None (assumes array size is sufficient). |
| `pop()`     | Remove the element from the head of the queue.| Do nothing if the queue is empty. |
| `front()`   | Return the head element (without removing it).| Undefined if empty (handled by user logic). |
| `empty()`   | Check if the queue has no elements.          | Returns `true` if empty, `false` otherwise. |


### Template-Based Queue Implementation  
Your queue uses "circular array" logic (implicitly, via `head` and `tail` pointers) to avoid wasting space. Here’s the breakdown:  

```cpp
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
```


## 3. Key Differences Between Stack and Queue  
Understanding when to use each is critical. Here’s a side-by-side comparison:  

| Aspect                | Stack                          | Queue                          |
|-----------------------|--------------------------------|--------------------------------|
| Order Principle       | LIFO (Last-In-First-Out)       | FIFO (First-In-First-Out)      |
| Access Ends           | Single end (top)               | Two ends (head = remove, tail = add) |
| Core Methods          | `push()`, `pop()`, `top()`     | `push()`, `pop()`, `front()`   |
| Common Use Cases      | - Function call stacks<br>- Undo/redo features<br>- DFS algorithm | - Task scheduling<br>- Printer queues<br>- BFS algorithm |


## Final Thoughts  
Stacks and queues are foundational because of their simplicity and efficiency. Your template-based implementations are clean and reusable—they leverage C++’s generic programming to work with any data type, making them perfect for competitive programming or small projects.  

The next time you need to manage elements in a sequential order, ask: *Do I need LIFO (stack) or FIFO (queue)?* This simple question will guide you to the right tool!