#include <stdio.h>

int C[31][31];

void gen_C()
{
    int i, j;
    for(i = 0; i <= 30; i++)
    {
        for(j = 0; j <= i; j++)
        {
            if(j == 0)
            {
                C[i][j] = 1;
            } else if(i == 0) {
                C[i][j] = 0;
            } else { 
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            }
        }
    }
}

int main()
{
    int n, i, j, N, k, m, ans = 0, prev = 0;
    freopen("choose2num.in",  "r", stdin);
    freopen("choose2num.out", "w", stdout);
    scanf("%d%d", &n, &k);
    gen_C();
    N = n - 1;
    for(i = k - 1; i >= 0; i--)
    {
        int t;
        scanf("%d", &t);
        t -= prev + 1;
        prev += t + 1;
        for(j = 0; j < t; j++)
        {
            ans += C[N--][i];
        }
        N--;
    }
    printf("%d\n", ans);
    return 0;
}
