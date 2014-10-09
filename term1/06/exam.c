#include <stdio.h>

int main()
{
    int k, i, n;
    double p, m, ans = 0;
    freopen("exam.in",  "r", stdin);
    freopen("exam.out", "w", stdout);
    scanf("%d%d", &k, &n);
    for(i = 0; i < k; i++)
    {
        scanf("%lf%lf", &p, &m);
        ans += p / n * m / 100;
    }
    printf("%.5lf", ans);
    return 0;
}
