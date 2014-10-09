#include <stdio.h>

int A[100];
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
    int n = -1, s = 0, i, j, prev = 1, ans = 0;
    freopen("part2num.in",  "r", stdin);
    freopen("part2num.out", "w", stdout);
    do
    {
        scanf("%d+", &A[++n]);
        s += A[n];
    }
    while(!feof(stdin));
    for(i = 0; i < n; i++)
    {
        ans += C(s, prev) - C(s, A[i]);
        s -= (prev = A[i]);
    }
    printf("%d\n", ans);
    return 0;
}
