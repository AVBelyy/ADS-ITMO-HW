#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <iostream>

using namespace std;

uint64_t D[41][41];
char A[41];
char S[41];

int main()
{
    int n, depth = 0, sp = 0;
    uint64_t ans = 0;
    freopen("brackets2num2.in",  "r", stdin);
    freopen("brackets2num2.out", "w", stdout);
    cin >> A;
    n = strlen(A);
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
        if(A[i] == '(')
        {
            depth++;
            S[sp++] = '(';
            continue;
        }
        if(A[i] == ')')
        {
            ans += D[n - i - 1][depth + 1] << ((n - i - depth - 2) / 2);
            depth--;
            sp--;
            continue;
        }
        if(A[i] == '[')
        {
            ans += D[n - i - 1][depth + 1] << ((n - i - depth - 2) / 2);
            if(S[sp - 1] == '(') ans += D[n - i - 1][depth - 1] << ((n - i - depth) / 2);
            depth++;
            S[sp++] = '[';
            continue;
        }
        if(A[i] == ']')
        {
            ans += 2 * D[n - i - 1][depth + 1] << ((n - i - depth - 2) / 2);
            depth--;
            sp--;
            continue;
        }
    }
    cout << ans << endl;
    return 0;
}
