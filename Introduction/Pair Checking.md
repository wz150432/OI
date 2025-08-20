# The Process of Pair Checking

- ### First of all, there is a brute-force procedure that guarantees correctness, and there is also a solution whose correctness is unknown.
- ### Then there is a file written according to this problem, used to generate random data
- ### Write a shell script or a cpp file (not recommended) to test the correction of the solution

#

## I. Script writing:
### shell script (runs on Linux systems):
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

### cpp script(runs on Windows systems):
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

If you want the code above to run on Linux, you can refer to the initial code for modifications.

#
#
## II. Writing Random Data Files
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
    srand(time(0);
    
    return 0;
}
```

Generate an undirected graph with $n$ nodes and $n - 1$ edges.
```cpp
int n = ri(100000);

for (int i = 2 ; i <= n ; i ++ )  {
    int p = ri(i - 1) + 1;
    int val = ri(1000000000) + 1;
    printf("%d %d %d\n", p, i, val);
}
```

Generate an undirected graph with $n$ nodes and $m$ edges without multiple edges and self-loops, and it must be connected.
```cpp
typedef pair<int, int> PII;
PII e[N];
map<PII, bool> vis;

for (int i = 1 ; i < n ; i ++ ) {
    int p = ri(i) + 1;
    e[i] = {p, i + 1};
    vis[e[i]] = vis[{i + 1, p)] = 1;
}

for (int i = n ; i <= m ; i ++ ) {
    int x = -2e9, y = -2e9;
    while (x == y || vis[{x, y}])
        x = ri(n) + 1, y = ri(n) + 1;
    
    e[i] = {x, y}
    vis[e[i] = vis[{y, x] = 1;
}

random_shuffle(e + 1, e + m + 1);
for (int i = 1 ; i <= m ; i ++ ) 
    printf("%d %d\n", e[i].first, e[i].second);
```
