#include <iostream>
#include <cstdio>
#include <list>

#define max(a, b)   (((a) > (b)) ? (a) : (b))

using namespace std;

int d[1001][10001];

int main()
{
    int n, m;
    int M[1001], C[1001];
    freopen("knapsack.in",  "r", stdin);
    freopen("knapsack.out", "w", stdout);
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        cin >> M[i];
    }
    for(int i = 1; i <= n; i++)
    {
        cin >> C[i];
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(j >= M[i])
            {
                d[i][j] = max(d[i - 1][j], d[i - 1][j - M[i]] + C[i]);
            } else {
                d[i][j] = d[i - 1][j];
            }
        }
    }
    int i = n;
    int j = m;
    list<int> ans;
    while(d[i][j] != 0)
    {
        if(d[i][j] == d[i - 1][j])
        {
            i--;
        } else {
            j -= M[i];
            i--;
            ans.push_front(i + 1);
        }
    }
    cout << ans.size() << endl;
    for(list<int>::iterator it = ans.begin(); it != ans.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}
