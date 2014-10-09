#include <stdio.h>
#include <math.h>

const double eps = 1e-14;

int main()
{
    int n, i, m, k;
    double a, t, p, S = 0;
    freopen("shooter.in",  "r", stdin);
    freopen("shooter.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    for(i = 0; i < n; i++)
    {
        scanf("%lf", &p);
        t = pow(1 - p, m);
        if(i + 1 == k)
        {
            a = t;
        }
        S += t;
    }
    if(S <= eps)
    {
        printf("0\n");
    } else {
        printf("%.13lf\n", a / S);
    }
    return 0;
}
