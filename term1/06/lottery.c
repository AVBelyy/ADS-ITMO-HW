#include <stdio.h>

int main()
{
    int n, i, m;
    double p, a, b, ans = 0;
    freopen("lottery.in",  "r", stdin);
    freopen("lottery.out", "w", stdout);
    scanf("%d%d", &n, &m);
    scanf("%lf%lf", &a, &b);
    p = 1 / a;
    for(i = 1; i < m; i++)
    {
        scanf("%lf", &a);
        ans += p * (1 - 1 / a) * b;
        p *= 1 / a;
        scanf("%lf", &b);
    }
    printf("%.13lf\n", n - ans - p * b);
    return 0;
}
