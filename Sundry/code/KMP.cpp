#include <cstdio>

using namespace std;

const int N = 1e5 + 10, M = 1e6 + 10;

int n, m;
int ne[N];
char s[N], s1[N];

int main() {
    scanf("%d%s%d%s", &n, s + 1, &m, s1 + 1);

    for (int i = 2, j = 0 ; i <= n ; i ++ ) {
        while (j && s[i] != s[j + 1]) j = ne[j];
        if (s[i] == s[j + 1]) j ++ ;
        ne[i] = j;
    }

    for (int i = 1, j = 0 ; i <= m ; i ++ ) {
        while (j && s1[i] != s[j + 1]) j = ne[j];
        if (s1[i] == s[j + 1]) j ++ ;
        if (j == n) {
            printf("%d\n", i - n + 1);
            j = ne[j];
        }
    }

    return 0;
}