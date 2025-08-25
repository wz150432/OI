# Fast Multiplication and Fast Power: Essential Tools for Safe Large-Number Arithmetic

In competitive programming and mathematical computations, handling large numbers often leads to a critical problem: overflow. Even with C++'s `long long` type, which can hold values up to approximately 9.2e18, multiplying large numbers or computing high exponents can easily exceed these limits. **Fast Multiplication** is not actually "fast" in the traditional sense, it provides safe alternatives for working with large values.

## Fast Multiplication: Safety Through Decomposition

Fast multiplication (also called binary multiplication) is a technique to compute `(a * b) % mod` without overflow, even when `a` and `b` are near the limits of `long long`.

### The Problem with Regular Multiplication

Direct multiplication of large values fails because the intermediate result exceeds the storage capacity of `long long`:

```cpp
inta = 1e18;
long long b = 1e18;
long long product = (a * b) % 1000000007; // Overflow occurs before mod!
```

This code produces incorrect results because `a * b` (1e36) overflows `long long` before the modulus operation is applied.

### How Fast Multiplication Works

Instead of multiplying directly, fast multiplication decomposes the operation into addition and bit shifting, applying the modulus at each step to keep values small:

```cpp
#include <iostream>

using namespace std;

const int p = 1e9 + 7;

int mul(int a, int b) {
    int res = 0;
    for ( ; b ; b >>= 1) {
        if (b & 1) res = (long long)(res + a) % p;
        a = (long long)(a + a) % p;
    }

    return res;
}

int main() {
    long long a, b;
    cin >> a >> b;

    cout << mul(a % p, b % p);

    return 0;
}
``` 

### Key Characteristics:
- Time complexity: $O(log b)$ - slower than direct multiplication but safe
- Purpose: Prevent overflow when multiplying large numbers under modulus
- Tradeoff: Sacrifices speed for safety with large values

## Fast Power: Efficient Exponentiation

Fast power (or exponentiation by squaring) computes `(a^b) % mod` efficiently, reducing the time complexity from $O(b)$ to $O(log b)$. When combined with fast multiplication, it becomes a powerful tool for handling extremely large exponents safely.

### The Limitations of Naive Exponentiation

A naive approach to compute `a^b` requires repeated multiplication, which is inefficient for large exponents and risks overflow:

```cpp
int naive_pow(int a, int b, int p) {
    for (int i = 1; i <= b; i ++ )
        a = (long long) a * a % p;
    
    return a;
}
```

### How Fast Power Works

Fast power leverages the mathematical properties of exponents to reduce the number of multiplications:

Every positive integer can be expressed as a sum of powers of 2, which is essentially its binary form. For example, 13 in binary is 1101, which translates to:  
13 = 8 + 4 + 1 = 2³ + 2² + 2⁰  

When calculating a base raised to this exponent (e.g., a¹³), we use the property of exponents that a^(x+y) = a^x × a^y. This lets us rewrite the expression using the binary components:  
a¹³ = a^(8+4+1) = a⁸ × a⁴ × a¹  

The key insight is that each term (a¹, a², a⁴, a⁸, ...) is the square of the previous term (a² = (a¹)², a⁴ = (a²)², etc.). By iterating through the bits of the exponent's binary form, we can compute these terms on-the-fly and multiply them into the result only when the corresponding bit is set (i.e., equals 1).

```cpp
#include <iostream>

using namespace std;

const int p = 1e9 + 7;

typedef long long ll;

int qpow(int a, int b) {
    int res = 1;
    for ( ; b ; b >>= 1) {
        if (b & 1) res = (ll)(res * a) % p;
        a = (ll)(a * a) % p;
    }

    return res;
}

int main() {
    int a, b;
    cin >> a >> b;

    cout << qpow(a, b);

    return 0;
}
```

### Key Characteristics:
- Time complexity: $O(log b)$ - drastically faster than naive approach
- Purpose: Efficiently compute large powers under modulus
- Advantage: When paired with fast multiplication, eliminates overflow risks

## Conclusion

Fast multiplication and fast power are not about raw speed—they're about **enabling computations that would otherwise be impossible** due to overflow or inefficiency. 

- Fast multiplication trades $O(1)$ time for $O(log b)$ time to prevent overflow in large-number multiplication
- Fast power reduces exponentiation from $O(n)$ to $O(log n)$ time, which is critical for large exponents
- Together, they form a powerful combination for safe modular arithmetic with large numbers

In competitive programming, understanding when to apply these techniques is essential. Use regular arithmetic when possible, but keep these tools in your toolkit for when numbers get too large to handle with standard operations.