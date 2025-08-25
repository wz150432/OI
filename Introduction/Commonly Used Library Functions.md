# Concise Guide to Common Programming Tools

Programming often relies on reusable tools to simplify tasks. Below is a streamlined breakdown of essential functions and I/O operations, organized by use case—no code, just key details.


## 1. Data Manipulation
- **swap(a, b)**: Exchanges values of two variables (works for all basic types like int, char).  
- **floor(x)**: Rounds down to the largest integer ≤ x (e.g., 3.8→3, -2.1→-3).  
- **ceil(x)**: Rounds up to the smallest integer ≥ x (e.g., 3.2→4, -2.9→-2).  
- **log(x)**: Calculates natural logarithm (base e) of positive x.  
- **log10(x)**: Calculates base-10 logarithm of positive x.  
- **pw(x, n)**: Computes xⁿ (often optimized as "fast power" for large n, paired with modulus for safety).  


## 2. String Handling
- **getline(cin, s)**: Reads an entire line (including spaces) into string s (avoids stopping at whitespace like `cin >> s`).  
- **substr(pos, len)**: Extracts a substring from s—starts at index `pos` (0-based) and takes `len` characters (omits `len` to take until end).  
- **stoi()**: Converts a numeric string (e.g., "123") to int; use `stoll()` for long long, `stof()` for float.  
- **tolower(c)**: Converts a single uppercase character c to lowercase (e.g., 'A'→'a').  
- **toupper(c)**: Converts a single lowercase character c to uppercase (e.g., 'b'→'B').  


## 3. Binary-Related (C++ Built-ins)
- **__builtin_ctz(x)**: Counts trailing zeros in x’s binary form (x > 0; e.g., 8=1000→3 zeros).  
- **__builtin_popcount(x)**: Counts "1"s (set bits) in x’s binary form (32-bit int; use `__builtin_popcountll()` for 64-bit long long).  


## 4. Input/Output (I/O)
### Core Tools
- **cin >> x**: Reads one data piece (int, string, etc.) into x (stops at whitespace; slower than `scanf`).  
- **cout << x**: Prints x to console (slower than `printf`, no format specifiers needed).  
- **scanf/printf**: Faster C-style I/O (needs format specifiers to match data types).  

### Key Format Specifiers (for scanf/printf)
| Specifier | Use Case                  | Example Outcome          |
|-----------|---------------------------|--------------------------|
| %d        | int                       | 42→"42"                  |
| %lld      | long long                 | 12345678901→"12345678901"|
| %c        | char                      | 'a'→"a"                  |
| %s        | string (char array)       | "test"→"test"            |
| %lf       | double                    | 3.14→"3.14"              |
| %.xlf     | double (x decimal places) | %.2lf→3.1415→"3.14"      |
| %0md      | int (pad 0s to m width)   | %05d→42→"00042"          |
| %-md      | int (left-align to m width)| %-5d→42→"42   "         |

### freopen()
Redirects stdin/stdout to files:  
- `freopen("1.in", "r", stdin)`: Read input from "1.in" (instead of keyboard).  
- `freopen("1.out", "w", stdout)`: Save output to "1.out" (instead of console).  


## 5. Memory Initialization
- **memset(a, value, sizeof a)**: Initializes a memory block (array `a`) with `value`. Common values: 0, -1, 0x3f (large positive), 0xff (all bits 1).  