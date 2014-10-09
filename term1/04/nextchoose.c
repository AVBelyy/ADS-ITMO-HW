#include <stdio.h>

int C[10000];

int main()
{
    int n, i, j, k, flag = 0;
    freopen("nextchoose.in",  "r", stdin);
    freopen("nextchoose.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for(i = 0; i < k; i++)
    {
        scanf("%d", &C[i]);
    }
    for(i = k - 1; i >= 0; i--)
    {
        if(C[i] < n - (k - i - 1))
        {
            flag = 1;
            C[i]++;
            for(j = i + 1; j < k; j++)
            {
                C[j] = C[i] + (j - i);
            }
            break;
        }
    }
    if(flag)
    {
        for(i = 0; i < k; i++)
        {
            printf("%d ", C[i]);
        }
        printf("\n");
    } else {
        printf("-1\n");
    }
    return 0;
}
