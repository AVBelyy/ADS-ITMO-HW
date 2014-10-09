#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <iostream>

using namespace std;

uint64_t D[41][41];

int main()
{
    int n, depth = 0;
    int64_t k;
    freopen("num2brackets.in",  "r", stdin);
    freopen("num2brackets.out", "w", stdout);
    cin >> n >> k;
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
    for(int i = 0; i < 2*n; i++)
    {
        if(k >= D[2*n - i - 1][depth + 1])
        {
            k -= D[2*n - i - 1][depth + 1];
            depth--;
            putchar(')');
        } else {
            depth++;
            putchar('(');
        }
    }
    putchar('\n');
    return 0;
}
