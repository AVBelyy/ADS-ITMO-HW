#include <stdio.h>
#include <math.h>

const double eps = 1e-16;

int n;
double M[101][101], A[101];

void Johann_Carl_Friedrich_Gauss(int o)
{
    int i, j, I = -1;
    for(i = o; i < n; i++)
    {
        if(fabs(M[i][o]) > eps)
        {
            if(i > o)
            {
                for(j = 0; j < n; j++)
                {
                    double swp_vrbl = M[o][j];
                    M[o][j] = M[i][j];
                    M[i][j] = swp_vrbl;
                }
                I = o;
            } else {
                I = i;
            }
            break;
        }
    }
    for(i = o + 1; i < n; i++)
    {
        double t = M[i][o] / M[I][o];
        for(j = 0; j < n; j++)
        {
            M[i][j] -= t * M[I][j];
        }
    }
}

int main()
{
    int i, j;
    freopen("markchain.in",  "r", stdin);
    freopen("markchain.out", "w", stdout);
    scanf("%d", &n);
    for(i = 0; i <= n; i++)
    {
        M[0][i] = 1;
    }
    for(i = 0; i < n; i++)
    {
        for(j = 1; j <= n; j++)
        {
            scanf("%lf", &M[j][i]);
        }
    }
    for(i = 1; i <= n; i++)
    {
        M[i][i - 1]--;
    }
    n++;
    /*for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%lf ", M[i][j]);
        }
        putchar('\n');
    }*/
    for(i = 0; i < n; i++)
    {
        Johann_Carl_Friedrich_Gauss(i);
    }
    for(i = 0; i < n - 1; i++)
    {
        double t = 0;
        for(j = 0; j < i; j++)
        {
            t += M[n - 2 - i][n - 2 - j] * A[n - 2 - j];
        }
        A[n - 2 - i] = (M[n - 2 - i][n - 1] - t) / M[n - 2 - i][n - 2 - i];
    }
    for(i = 0; i < n - 1; i++)
    {
        printf("%.4lf\n", A[i]);
    }
    return 0;
}
