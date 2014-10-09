#include <stdio.h>

#define max(A, B)   (((A) > (B)) ? (A) : (B))

int P[100000];
int cnt[100001];

int main()
{
    int n, i, j, M = 0, prev = 0, flag = 0;
    freopen("nextmultiperm.in",  "r", stdin);
    freopen("nextmultiperm.out", "w", stdout);
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &P[i]);
        M = max(M, P[i]);
        cnt[P[i]]++;
    }
    for(i = n - 1; i >= 0; i--)
    {
        if(P[i] < prev)
        {
            flag = 1;
            int next;
            for(j = 0; j < i; j++)
            {
                cnt[P[j]]--;
            }
            for(j = P[i] + 1; j <= M; j++)
            {
                if(cnt[j] != 0)
                {
                    next = j;
                    break;
                }
            }
            P[i] = next;
            cnt[next]--;
            for(j = 1; j <= M; j++)
            {
                while(cnt[j] != 0)
                {
                    P[++i] = j;
                    cnt[j]--;
                }
            }
            break;
        }
        prev = P[i];
    }
    for(i = 0; i < n; i++)
    {
        printf("%d ", flag ? P[i] : 0);
    }
    printf("\n");
    return 0;
}
