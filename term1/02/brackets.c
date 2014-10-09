#include <stdio.h>

int n;
char A[50];

void gen(int len, int depth)
{
    if(depth < 0) return;
    if(depth > 2 * n - len) return;
    if(len == 2 * n)
    {
        printf("%s\n", A);
        return;
    }
    A[len] = '(';
    gen(len + 1, depth + 1);
    A[len] = ')';
    gen(len + 1, depth - 1);
}

int main()
{
    freopen("brackets.in",  "r", stdin);
    freopen("brackets.out", "w", stdout);
    scanf("%d", &n);
    gen(0, 0);
    return 0;
}
