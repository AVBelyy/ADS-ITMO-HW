#include <stdio.h>
#include <string.h>

char V1[200001], V2[200001];

int main()
{
    int i, j, len, flag;
    freopen("nextvector.in",  "r", stdin);
    freopen("nextvector.out", "w", stdout);
    scanf("%s", V1);
    len = strlen(V1);
    strncpy(V2, V1, len);
    flag = 0;
    for(i = len - 1; i >= 0; i--)
    {
        if(V1[i] == '1')
        {
            flag = 1;
            V1[i] = '0';
            for(j = i + 1; j < len; j++)
            {
                V1[j] = '1';
            }
            break;
        }
    }
    printf("%s\n", flag ? V1 : "-");
    flag = 0;
    for(i = len - 1; i >= 0; i--)
    {
        if(V2[i] == '0')
        {
            flag = 1;
            V2[i] = '1';
            for(j = i + 1; j < len; j++)
            {
                V2[j] = '0';
            }
            break;
        }
    }
    printf("%s\n", flag ? V2 : "-");
    return 0;
}
