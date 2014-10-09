#include <iostream>
#include <cstdio>
#include <vector>
#include <list>

using namespace std;

const int M = 1E9 + 7;

int n, depth = 0;
list<int> U[100000], V[100000];
bool used[100000];
int color[100000];
int dp[100000], T[100000];

bool DFS(int u)
{
    if(color[u] == 1) return true;
    if(color[u] == 2) return false;
    color[u] = 1;
    for(list<int>::iterator it = V[u].begin(); it != V[u].end(); it++)
    {
        if(DFS(*it))
        {
            return true;
        }
    }
    T[u] = n - depth++ - 1;
    color[u] = 2;
    return false;
}

void topSort()
{
    /*for(int u = 0; u < n; u++)
    {
        if(!used[u])
        {
            DFS(u);
        }
    }*/
    for(int u = 0; u < n; u++)
    {
        DFS(u);
    }
}

int main()
{
    int m;
    freopen("countpaths.in",  "r", stdin);
    freopen("countpaths.out", "w", stdout);
    cin >> n >> m;
    for(int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        U[a - 1].push_back(b - 1);
        V[b - 1].push_back(a - 1);
    }
    topSort();
    for(int i = 0; i < n; i++)
    {
        //cout << T[i] + 1 << endl;
    }
    // simple & neat dp
    dp[n - 1] = 1;
    for(int i = 1; i < n; i++)
    {
        for(list<int>::iterator it = U[T[i]].begin(); it != U[T[i]].end(); it++)
        {
            dp[T[i]]  = (dp[T[i]] + dp[*it]) % M;
        }
        //cout << dp[T[i]] << endl;
    }
    cout << dp[0] << endl;
    return 0;
}
