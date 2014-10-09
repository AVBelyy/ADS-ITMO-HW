#include <stdio.h>

#define MALO    0
#define MNOGO   100500

int P1[100000], P2[100000];
int used[100001];

int main()
{
    int n, i, j, t, prev, flag;
    freopen("nextperm.in",  "r", stdin);
    freopen("nextperm.out", "w", stdout);
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &t);
        P1[i] = P2[i] = t;
    }
    prev = MNOGO;
    flag = 0;
    for(i = n - 1; i >= 0; i--)
    {
        if(P1[i] > prev)
        {
            flag = 1;
            int next;
            for(j = 0; j < i; j++)
            {
                used[P1[j]] = 1;
            }
            for(j = P1[i] - 1; j >= 1; j--)
            {
                if(!used[j])
                {
                    next = j;
                    break;
                }
            }
            P1[i] = next;
            used[next] = 1;
            for(j = n; j >= 1; j--)
            {
                if(!used[j])
                {
                    P1[++i] = j;
                }
            }
            break;
        }
        prev = P1[i];
    }
    for(i = 0; i < n; i++)
    {
        printf("%d ", flag ? P1[i] : 0);
    }
    printf("\n");
    for(i = 1; i <= n; i++)
    {
        used[i] = 0;
    }
    prev = MALO;
    flag = 0;
    for(i = n - 1; i >= 0; i--)
    {
        if(P2[i] < prev)
        {
            flag = 1;
            int next;
            for(j = 0; j < i; j++)
            {
                used[P2[j]] = 1;
            }
            for(j = P2[i] + 1; j <= n; j++)
            {
                if(!used[j])
                {
                    next = j;
                    break;
                }
            }
            P2[i] = next;
            used[next] = 1;
            for(j = 1; j <= n; j++)
            {
                if(!used[j])
                {
                    P2[++i] = j;
                }
            }
            break;
        }
        prev = P2[i];
    }
    for(i = 0; i < n; i++)
    {
        printf("%d ", flag ? P2[i] : 0);
    }
    printf("\n");
    return 0;
}
