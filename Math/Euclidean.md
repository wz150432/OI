# Euclidean Algorithm and Extended Extended Extended Extended Euclidean Algorithm in C++

## 1. The Euclidean Algorithm (GCD Calculation)

### 1.1 Fundamental Concept
The Euclidean algorithm is an efficient method for computing the Greatest Common Divisor (GCD) of two integers. It's based on the principle that:

`gcd(a, b) = gcd(b, a % b)`

This process continues until the second number becomes 0, at which point the first number is the GCD.

### Implementation in C++

```cpp
#include <iostream>

using namespace std;

int a, b;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    cin >> a >> b;

    cout << gcd(a, b);

    return 0;
}
```

## 2. The Extended Euclidean Algorithm

### 2.1 Core Idea
The Extended Euclidean Algorithm not only finds the GCD of two numbers but also determines coefficients (x, y) that satisfy Bézout's identity:

`a * x + b * y = gcd(a, b)`

NOTE : **The case where a and b are both zero is mathematical error**

### 2.2 C++ Implementation

```cpp
#include <iostream>

using namespace std;

int a, b;

int exgcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int main() {
    cin >> a >> b;

    int x, y;
    exgcd(a, b, x, y);

    cout << x << " " << y << endl;

    return 0;
}
```

## 3. Time Complexity Analysis

Both algorithms have a time complexity of $O(log(min(a, b)))$, making them very efficient even for large numbers. This is significantly better than the naive approach of checking all potential divisors.

## 4. Recommended Exercises