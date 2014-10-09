#include <iostream>
#include <utility>
#include <cstdio>

#define max(a, b)   (((a) > (b)) ? (a) : (b))

using namespace std;

int a[2001], b[2001];

int lcs[2001][2001];
pair<int, int> p[2001][2001];

void output(int i, int j)
{
    if(i != 0 && j != 0)
    {
        output(p[i][j].first, p[i][j].second);
        if(p[i][j] == make_pair(i - 1, j - 1))
        {
            cout << a[i] << " ";
        }
    }
}

int main()
{
    int n, m;
    freopen("lcs.in",  "r", stdin);
    freopen("lcs.out", "w", stdout);
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    cin >> m;
    for(int i = 1; i <= m; i++)
    {
        cin >> b[i];
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(a[i] == b[j])
            {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
                p[i][j] = make_pair(i - 1, j - 1);
            } else if(lcs[i][j - 1] > lcs[i - 1][j]) {
                lcs[i][j] = lcs[i][j - 1];
                p[i][j] = make_pair(i, j - 1);
            } else {
                lcs[i][j] = lcs[i - 1][j];
                p[i][j] = make_pair(i - 1, j);
            }
        }
    }
    cout << lcs[n][m] << endl;
    output(n, m);
    cout << endl;
    return 0;
}
