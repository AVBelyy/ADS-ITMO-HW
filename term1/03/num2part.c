#include <stdio.h>

int D[101][101];

int C(int n, int k)
{
    int i, ans = 1;
    if(D[n][k])
    {
        return D[n][k];
    }
    for(i = k; i <= n / 2; i++)
    {
        ans += C(n - i, i);
    }
    return D[n][k] = ans;
}

int main()
{
    int n, i, j, k, prev = 1;
    freopen("num2part.in",  "r", stdin);
    freopen("num2part.out", "w", stdout);
    scanf("%d%d", &n, &k);
    while(n > 0)
    {
        for(j = n; j >= prev; j--)
        {
            int K = C(n, prev) - C(n, j);
            if(k >= K)
            {
                k -= K;
                n -= j;
                prev = j;
                printf("%d", j);
                putchar(n ? '+' : '\n');
            }
        }
    }
    return 0;
}
