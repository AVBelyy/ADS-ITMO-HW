#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <iostream>

using namespace std;

char S[41];
uint64_t D[41][41];

int main()
{
    int n, depth = 0;
    uint64_t ans = 0;
    freopen("brackets2num.in",  "r", stdin);
    freopen("brackets2num.out", "w", stdout);
    cin >> S;
    n = strlen(S);
    for(int i = 0; i <= 40; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            uint64_t v;
            if(i == 0 && j == 0) v = 1;
            else if(i == 0) v = 0;
            else if(j == 0) v = D[i - 1][1];
            else v = D[i - 1][j - 1] + D[i - 1][j + 1];
            D[i][j] = v;
        }
    }
    for(int i = 0; i < n; i++)
    {
        if(S[i] == '(')
        {
            depth++;
        } else {
            ans += D[n - i - 1][depth + 1];
            depth--;
        }
    }
    cout << ans << endl;
    return 0;
}
