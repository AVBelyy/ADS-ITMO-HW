#include <iostream>
#include <cstring>
#include <cstdio>

#define max(a, b)   (((a) > (b)) ? (a) : (b))

using namespace std;

int d[2001][2001];

char s[2001], ans[2001];

int D(int i, int j)
{
    if(i == j)
    {
        return 1;
    }
    if(i > j)
    {
        return 0;
    }
    if(d[i][j])
    {
        return d[i][j];
    }
    if(s[i - 1] == s[j - 1])
    {
        return d[i][j] = D(i + 1, j - 1) + 2;
    } else {
        return d[i][j] = max(D(i + 1, j), D(i, j - 1));
    }
}

void output(int l, int r, int pl, int pr)
{
    while(l <= r)
    {
        if(l == r)
        {
            ans[pl++] = s[l++];
        } else if(s[l] == s[r])
        {
            ans[pl++] = s[l++];
            ans[pr--] = s[r--];
        } else {
            if(D(l + 2, r + 1) > D(l + 1, r))
            {
                l++;
            } else {
                r--;
            }
        }
    }
}

int main()
{
    freopen("palindrome.in",  "r", stdin);
    freopen("palindrome.out", "w", stdout);
    cin >> s;
    int n = strlen(s);
    cout << D(1, n) << endl;
    output(0, n - 1, 0, D(1, n) - 1);
    cout << ans << endl;
    return 0;
}
