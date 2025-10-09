# 栈与队列基础应用

线性数据结构——元素按顺序排列——是编程的基石。其中，**栈（Stack）** 和 **队列（Queue）** 因其简洁性及在算法中的广泛应用（如栈用于深度优先搜索，队列用于广度优先搜索）而脱颖而出。

## 1. 栈：后进先出（LIFO）

栈是一种“单端”结构，元素的添加和移除都在**同一端**（称为“栈顶”）进行。可以想象一叠盘子：你只能将新盘子放在最上面，或者拿走最上面的盘子。

### 核心特性：LIFO

最后插入的元素将最先被移除。形式化表示为：
$$
\text{插入顺序: } e_1 \rightarrow e_2 \rightarrow e_3 \quad \Rightarrow \quad \text{移除顺序: } e_3 \rightarrow e_2 \rightarrow e_1
$$


### 核心操作

所有栈操作的时间复杂度均为 **O(1)**（常数时间），因为它们只修改或访问栈顶元素。

| 操作      | 描述                       | 边界情况处理                             |
| --------- | -------------------------- | ---------------------------------------- |
| `push(x)` | 将元素 `x` 添加到栈顶。    | 无（假设数组空间足够）。                 |
| `pop()`   | 移除栈顶元素。             | 如果栈为空，则不执行任何操作。           |
| `top()`   | 返回栈顶元素（不移除它）。 | 如果为空则行为未定义（由用户逻辑处理）。 |
| `empty()` | 检查栈是否没有元素。       | 如果为空返回 `true`，否则返回 `false`。  |


### 栈实现

c++ 代码：

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


## 2. 队列：先进先出（FIFO）

队列是一种“双端”结构，元素从一端（称为“队尾”）添加，从另一端（称为“队首”）移除。可以想象商店的排队：最先加入队伍的人将最先得到服务。

### 核心特性：FIFO

最先插入的元素将最先被移除。形式化表示为：
$$
\text{插入顺序: } e_1 \rightarrow e_2 \rightarrow e_3 \quad \Rightarrow \quad \text{移除顺序: } e_1 \rightarrow e_2 \rightarrow e_3
$$


### 核心操作

与栈类似，所有队列操作的时间复杂度均为 **O(1)** ——它们只修改队首或队尾。

| 操作      | 描述                       | 边界情况处理                             |
| --------- | -------------------------- | ---------------------------------------- |
| `push(x)` | 将元素 `x` 添加到队尾。    | 无（假设数组空间足够）。                 |
| `pop()`   | 移除队首的元素。           | 如果队列为空，则不执行任何操作。         |
| `front()` | 返回队首元素（不移除它）。 | 如果为空则行为未定义（由用户逻辑处理）。 |
| `empty()` | 检查队列是否没有元素。     | 如果为空返回 `true`，否则返回 `false`。  |


### 队列实现

c++ 代码：

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


## 3. 栈与队列的关键区别

理解何时使用哪种结构至关重要。以下是它们的对比：

| 方面         | 栈                                                           | 队列                                                  |
| ------------ | ------------------------------------------------------------ | ----------------------------------------------------- |
| 顺序原则     | LIFO (后进先出)                                              | FIFO (先进先出)                                       |
| 访问端       | 单端（栈顶）                                                 | 双端（队首 = 移除，队尾 = 添加）                      |
| 核心方法     | `push()`, `pop()`, `top()`                                   | `push()`, `pop()`, `front()`                          |
| 常见应用场景 | - 函数调用栈<br>- 撤销/重做功能<br>- 深度优先搜索（DFS）算法 | - 任务调度<br>- 打印队列<br>- 广度优先搜索（BFS）算法 |



## 例题

[B3614](https://www.luogu.com.cn/problem/B3614)

[P2201](https://www.luogu.com.cn/problem/P2201)

[P1449](https://www.luogu.com.cn/problem/P1449)

[P1540](https://www.luogu.com.cn/problem/P1540)

[B3616](https://www.luogu.com.cn/problem/B3616)



## 推荐的题目

[UVA540](https://www.luogu.com.cn/problem/UVA540)

[P10472](https://www.luogu.com.cn/problem/P10472)

[P10473](https://www.luogu.com.cn/problem/P10473)

[UVA1330](https://www.luogu.com.cn/problem/UVA1330)

[P1155](https://www.luogu.com.cn/problem/P1155)