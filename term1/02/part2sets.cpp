#include <cstdio>
#include <list>

using namespace std;

int n, k, cnt = 0, C[10];
bool used[11];

int SS[10][10], L[10];

void gen_SS(list<int> Q)
{
    if(Q.empty())
    {
        for(int i = 0; i < k; i++)
        {
            for(int j = 0; j < L[i]; j++)
            {
                printf("%d ", SS[i][j]);
            }
            putchar('\n');
        }
        cnt++;
        putchar('\n');
        return;
    }
    int x = Q.front();
    Q.pop_front();
    for(int i = 0; i < k; i++)
    {
        if(SS[i][L[i] - 1] < x)
        {
            SS[i][L[i]++] = x;
            gen_SS(Q);
            L[i]--;
        }
    }
}

void gen_C(int len, int prev)
{
    if(len == k)
    {
        for(int i = 0; i < k; i++)
        {
            L[i] = 0;
            SS[i][L[i]++] = C[i];
        }
        list<int> Q;
        for(int i = 1; i <= n; i++)
        {
            if(!used[i])
            {
                Q.push_back(i);
            }
        }
        gen_SS(Q);
    }
    for(int i = prev + 1; i <= n; i++)
    {
        C[len] = i;
        used[i] = true;
        gen_C(len + 1, i);
        used[i] = false;
    }
}

int main()
{
    freopen("part2sets.in",  "r", stdin);
    freopen("part2sets.out", "w", stdout);
    scanf("%d%d", &n, &k);
    gen_C(0, 0);
    return 0;
}
