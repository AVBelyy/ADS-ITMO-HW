#include <stdio.h>

int n;
char S[17];

void gen(int len, int prev)
{
    if(len == n)
    {
        printf("%s\n", S);
        return;
    }
    S[len] = '0';
    gen(len + 1, 0);
    if(prev != 1)
    {
        S[len] = '1';
        gen(len + 1, 1);
    }
}

int main()
{
    int i, f1 = 1, f2 = 2;
    freopen("vectors.in",  "r", stdin);
    freopen("vectors.out", "w", stdout);
    scanf("%d", &n);
    for(i = 2; i <= n; i++)
    {
        int f3 = f1 + f2;
        f1 = f2;
        f2 = f3;
    }
    printf("%d\n", f2);
    gen(0, 0);
    return 0;
}
