#include <iostream>
#include <stdint.h>
#include <cstdio>
#include <vector>
#include <map>

#define max(a, b)   (((a) > (b)) ? (a) : (b))

using namespace std;

vector< map<int, int64_t> > Ch;

int64_t a[100000], b[100000], c[100000];

void W(int u)
{
    for(map<int, int64_t>::iterator it = Ch[u].begin(); it != Ch[u].end(); it++)
    {
        int v = it->first;
        Ch[v].erase(u);
        W(v);
    }
}

void D(int u)
{
    if(c[u] != - 1) return;
    a[u] = 0;
    for(map<int, int64_t>::iterator it = Ch[u].begin(); it != Ch[u].end(); it++)
    {
        int v = it->first;
        int64_t w = it->second;
        D(v);
        a[u] = max(a[u], b[v] - c[v] + w);
        b[u] += c[v];
    }
    a[u] += b[u];
    c[u] = max(a[u], b[u]);
}

int main()
{
    int n;
    freopen("matching.in",  "r", stdin);
    freopen("matching.out", "w", stdout);
    cin >> n;
    Ch.resize(n);
    for(int i = 0; i < n; i++)
    {
        c[i] = -1;
    }
    for(int i = 0; i < n - 1; i++)
    {
        int a, b;
        int64_t w;
        cin >> a >> b >> w;
        Ch[a - 1][b - 1] = w;
        Ch[b - 1][a - 1] = w;
    }
    W(0);
    D(0);
    cout << c[0] << endl;
    return 0;
}
