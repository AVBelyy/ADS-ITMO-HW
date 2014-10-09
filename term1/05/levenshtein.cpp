#include <iostream>
#include <cstdio>
#include <string>

#define min(a, b)   (((a) < (b)) ? (a) : (b))

using namespace std;

int d[5001][5001];

int main()
{
    string s1, s2;
    freopen("levenshtein.in",  "r", stdin);
    freopen("levenshtein.out", "w", stdout);
    cin >> s1 >> s2;
    int n = s1.size(), m = s2.size();
    for(int i = 0; i <= n; i++)
    {
        for(int j = 0; j <= m; j++)
        {
            if(i == 0 || j == 0)
            {
                d[i][j] = i + j;
            } else {
                if(s1[i - 1] == s2[j - 1])
                {
                    d[i][j] = d[i - 1][j - 1];
                } else {
                    d[i][j] = min(min(d[i][j - 1], d[i - 1][j]), d[i - 1][j - 1]) + 1;
                }
            }
        }
    }
    cout << d[n][m] << endl;
    return 0;
}
