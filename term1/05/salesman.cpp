#include <iostream>
#include <stdint.h>
#include <stdio.h>

using namespace std;

#define INF     1E16

int G[18][18];
int C[18];
uint64_t W[18][18];

uint64_t d[1<<18][18];

int main()
{
    int n, m;
    freopen("salesman.in",  "r", stdin);
    freopen("salesman.out", "w", stdout);
    scanf("%d%d", &n, &m);
    //n++;
    for(int i = 0; i < m; i++)
    {
        int a, b;
        uint64_t w;
        cin >> a >> b >> w;
        G[a - 1][C[a - 1]++] = b - 1;
        G[b - 1][C[b - 1]++] = a - 1;
        W[a - 1][b - 1] = W[b - 1][a - 1] = w;
    }
    for(int mask = 0; mask < 1<<n; mask++)
    {
        for(int i = 0; i < n; i++)
        {
            d[mask][i] = INF;
        }
    }
    for(int i = 0; i < n; i++)
    {
        d[0][i] = 0;
    }
    for(int mask = 0; mask < 1<<n; mask++)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < C[i]; j++)
            {
                int v = G[i][j];
                uint64_t w = W[i][v];
                if((mask & (1 << v)) != 0)
                {
                    uint64_t t = d[mask - (1<<v)][v] + w;
                    if(d[mask][i] > t)
                    {
                        d[mask][i] = t;
                    }
                }
            }
        }
    }
    uint64_t ans = INF;
    for(int i = 0; i < n; i++)
    {
        if(ans > d[(1<<n) - 1 - (1<<i)][i])
        {
            ans = d[(1<<n) - 1 - (1<<i)][i];
        }
    }
    if(ans > 1E12)
    {
        printf("%d\n", -1);
    } else {
        cout << ans << endl;
    }
    return 0;
}
