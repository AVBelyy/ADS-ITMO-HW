#include <stdio.h>
#include <string.h>

char S[200001];

int main()
{
    int n, i, j, depth = 0;
    freopen("nextbrackets.in",  "r", stdin);
    freopen("nextbrackets.out", "w", stdout);
    scanf("%s", S);
    n = strlen(S) / 2;
    for(i = 2*n - 1; i >= 0; i--)
    {
        if(S[i] == ')')
        {
            depth++;
        } else {
            depth--;
        }
        if(S[i] == '(' && depth > 0)
        {
            S[i] = ')';
            int open = (2*n - i - depth) / 2;
            for(j = i + 1; j < i + open + 1; j++)
            {
                S[j] = '(';
            }
            for(j = i + open + 1; j < 2*n; j++)
            {
                S[j] = ')';
            }
            printf("%s\n", S);
            return 0;
        }
    }
    printf("-\n");
    return 0;
}
