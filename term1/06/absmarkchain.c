#include <stdlib.h>
#include <stdio.h>
#include <math.h>

const double eps = 1e-16;

double P[400][400], Q[400][800], R[400][400], QR[400][400];
double A[400];
int Rs[400], RsCnt = 0;
int Qs[400], QsCnt = 0;

/*int T[4][4] = {{1,5,9,3},
               {2,6,10,4},
               {3,7,1,6},
               {4,8,2,5}};*/

void Johann_Carl_Friedrich_Gauss(int o)
{
    int i, j, I = -1;
    for(i = o; i < QsCnt; i++)
    {
        if(fabs(Q[i][o]) > eps)
        {
            if(i > o)
            {
                for(j = 0; j < 2 * QsCnt; j++)
                {
                    double swp_vrbl = Q[o][j];
                    Q[o][j] = Q[i][j];
                    Q[i][j] = swp_vrbl;
                }
                I = o;
            } else {
                I = i;
            }
            break;
        }
    }
    for(i = o + 1; i < QsCnt; i++)
    {
        double t = Q[i][o] / Q[I][o];
        for(j = 0; j < 2 * QsCnt; j++)
        {
            Q[i][j] -= t * Q[I][j];
        }
    }
}

void Wilhelm_Jordan(int o)
{
    int i, j;
    for(i = 0; i < o; i++)
    {
        double p = Q[QsCnt - 1 - o][QsCnt - 1 - i];
        for(j = QsCnt; j < 2 * QsCnt; j++)
        {
            Q[QsCnt - 1 - o][j] -= p * Q[QsCnt - 1 - i][j];
        }
    }
    double t = Q[QsCnt - 1 - o][QsCnt - 1 - o];
    for(i = QsCnt; i < 2 * QsCnt; i++)
    {
        Q[QsCnt - 1 - o][i] /= t;
    }
}

void QR_Multiply()
{
    int i, j, k;
    for(i = 0; i < QsCnt; i++)
    {
        for(j = 0; j < RsCnt; j++)
        {
            double s = 0.0;
            for(k = 0; k < QsCnt; k++)
            {
                s += Q[i][k + QsCnt] * R[k][j];
            }
            QR[i][j] = s;
        }
    }
}

int compare(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

int main()
{
    int n, i, j, m;
    freopen("absmarkchain.in",  "r", stdin);
    freopen("absmarkchain.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(i = 0; i < m; i++)
    {
        int a, b;
        double p;
        scanf("%d%d%lf", &a, &b, &p);
        P[a - 1][b - 1] = p;
        if(a == b && p == 1.0)
        {
            Rs[RsCnt++] = a - 1;
        }
    }
    qsort(Rs, RsCnt, sizeof(int), compare);
    for(i = 0; i < Rs[0]; i++)
    {
        Qs[QsCnt++] = i;
    }
    for(i = 0; i < RsCnt - 1; i++)
    {
        for(j = Rs[i] + 1; j < Rs[i + 1]; j++)
        {
            Qs[QsCnt++] = j;
        }
    }
    for(i = Rs[RsCnt - 1] + 1; i < n; i++)
    {
        Qs[QsCnt++] = i;
    }
    for(i = 0; i < QsCnt; i++)
    {
        for(j = 0; j < QsCnt; j++)
        {
            Q[i][j] = -P[Qs[i]][Qs[j]];
            if(i == j) Q[i][j]++;
        }
        Q[i][i + QsCnt] = 1.0;
        for(j = 0; j < RsCnt; j++)
        {
            R[i][j] = P[Qs[i]][Rs[j]];
        }
    }
    for(i = 0; i < QsCnt; i++)
    {
        Johann_Carl_Friedrich_Gauss(i);
    }
    for(i = 0; i < QsCnt; i++)
    {
        Wilhelm_Jordan(i);
    }
    QR_Multiply();
    for(i = 0; i < RsCnt; i++)
    {
        double e = 1;
        for(j = 0; j < QsCnt; j++)
        {
            e += QR[j][i];
        }
        A[Rs[i]] = e / n;
    }
    for(i = 0; i < n; i++)
    {
        printf("%.8lf\n", A[i]);
    }
    for(i = 0; i < QsCnt; i++)
    {
        putchar('\n');
        for(j = 0; j < RsCnt; j++)
        {
            printf("%.8lf\n", QR[i][j]);
        }
    }
    return 0;
}
