# The Process of Pair Checking

When developing algorithms, ensuring correctness is paramount—especially when optimizing beyond brute-force solutions. Pair checking (or "stress testing") is a powerful technique to validate that an optimized solution behaves identically to a trusted brute-force approach across diverse inputs. Here's a step-by-step guide to implementing this process.


## Core Components of Pair Checking

1. **Brute-force Solution**: A straightforward, guaranteed-correct implementation (may be slow but serves as the "truth source").  
2. **Optimized Solution**: The faster solution whose correctness needs verification.  
3. **Random Data Generator**: A program to produce diverse test cases covering edge cases and typical scenarios.  
4. **Automation Script**: A script to repeatedly run both solutions on generated data, compare outputs, and flag discrepancies.  


## I. Automation Scripts

These scripts automate the testing loop: generating data, running both solutions, comparing results, and stopping on failures.

### Shell Script (Linux)
```sh
#!/bin/bash
g++ my.cpp -std=c++11 -o my # solution
g++ bf.cpp -std=c++11 -o bf # brute-force precedure
g++ rand.cpp -std=c++11 -o rand # data generator

t=1
while [ $t -lt 1000000 ]; do
    printf "CASE%d:\n" $t
    
    # '<' Input '>' Output will overwrite the original data. If you don't want to overwrite, use '<<' Input '>>' Output

    
    ./rand > rand.in # data generated into rand.in file
    
    ./bf < rand.in > bf.out # The output from brute-force precedure input into bf.out file
    
    time ./my < rand.in > my.out # The output from solution input into my.out file, also display running time
    
    # -Z ignore the differences the trailling spaces
    if diff -Z bf.out my.out; then 
        echo "AC\n"
    else 
        echo "WA\n"
        cat rand.in # showing the input data. It optional and recommanded only for small data
        break;
    
    fi # the end of if statement
    
    let "t = $t + 1"
done
```

### C++ Script (Windows)
```cpp
#include <chrono>
#include <cstdio>

using namespace std;

int c;

int main() {
    system("g++ my.cpp -std=c++11 -o my.exe");
    system("g++ rand.cpp -std=c++11 -o rand.exe");
    system("g++ bf.cpp -std=c++11 -o bf.exe");
    
    
    while (c <= 1000000) {
        system("rand.exe > rand.in");
        system("bf.exe < rand.in > bf.out");
        
        double st = clock();
        system("test.exe < rand.in > test.out");
        double ed = clock();
        
        if (system("fc test.out bf.out > nul")) {
            printf("#CASE%d: WA, cost time: %.0lfms\n", ++ c, ed - st);
            break;
        }
        printf("#CASE%d: AC, cost time: %.0lfms\n", ++ c, ed - st);
    }

    return 0;
}
```

*Note: The Windows script can be adapted for Linux by replacing `fc` with `diff` and adjusting executable extensions.*


## II. Writing a Random Data Generator

A robust data generator ensures test cases cover diverse scenarios (e.g., small/large inputs, edge cases like empty sets or maximum values). Below are foundational tools and examples.

### Base Generator Utilities
```cpp
#include<cstdlib>
#include <ctime>

using namespace std;

typedef long long ll;
// Since the range of the rand function Windows system is [0 - 32767],  for data with a larger number range, it may be necessary to multiply several times
// But Linux like systems the range of the rand function is 0 to 2147483647, be sure to avoid having the generated data overflow
// The following code genrates number in range from 0 to n - 1. If you want to get negative numbers, you can substract n from the numbers in range from 0 to 2n

int ri(int n) {
    return 1ll * rand() * rand() % n;
}

ll rll(ll n) {
    return 1ll * rand() * rand() % n;
}

int main() {
    srand(time(0));
    
    return 0;
}
```

### Example 1: Generate a Tree (n Nodes, n-1 Edges)
```cpp
int n = ri(100000);

for (int i = 2 ; i <= n ; i ++ )  {
    int p = ri(i - 1) + 1;
    int val = ri(1000000000) + 1;
    printf("%d %d %d\n", p, i, val);
}
```

### Example 2: Generate a Connected Undirected Graph (n Nodes, m Edges)
*Ensures no multiple edges or self-loops*
```cpp
typedef pair<int, int> PII;
PII e[N];
map<PII, bool> vis;

for (int i = 1 ; i < n ; i ++ ) {
    int p = ri(i) + 1;
    e[i] = {p, i + 1};
    vis[e[i]] = vis[{i + 1, p}] = 1;
}

for (int i = n ; i <= m ; i ++ ) {
    int x = -2e9, y = -2e9;
    while (x == y || vis[{x, y}])
        x = ri(n) + 1, y = ri(n) + 1;
    
    e[i] = {x, y};
    vis[e[i]] = vis[{y, x}] = 1;
}

random_shuffle(e + 1, e + m + 1);
for (int i = 1 ; i <= m ; i ++ ) 
    printf("%d %d\n", e[i].first, e[i].second);
```


## How to Use This Workflow

1. **Prepare Implementations**: Write your optimized solution (`my.cpp`) and a brute-force version (`bf.cpp`).  
2. **Build the Generator**: Create `rand.cpp` to produce test cases relevant to your problem (e.g., graphs, arrays, or custom structures).  
3. **Run the Script**: Execute the automation script. It will:  
   - Compile all programs.  
   - Generate test cases.  
   - Run both solutions on each case.  
   - Compare outputs. If they differ, it stops and shows the failing input.  
4. **Debug**: Use the failing input to identify where your optimized solution deviates from the brute-force result.  


This approach is invaluable for competitive programming, algorithm development, or any scenario where correctness must be verified across countless edge cases. By automating the process, you can test thousands of cases efficiently, ensuring your solution is robust.