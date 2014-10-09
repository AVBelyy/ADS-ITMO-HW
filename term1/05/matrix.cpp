#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

const int INF = 1E9;

struct matrix
{
    int a;
    int b;
    int c;
};

matrix d[400][400];

void D(int i, int j)
{
    if(d[i][j].c != INF) return;
    d[i][j].c = INF;
    for(int k = i; k < j; k++)
    {
        D(i, k);
        D(k + 1, j);
        int cost = d[i][k].c + d[k + 1][j].c + d[i][k].a * d[i][k].b * d[k + 1][j].b;
        if(d[i][j].c > cost)
        {
            d[i][j].a = d[i][k].a;
            d[i][j].b = d[k + 1][j].b;
            d[i][j].c = cost;
        }
    }
}

void R(int i, int j)
{
    if(i == j)
    {
        putchar('A');
    }
    for(int k = i; k < j; k++)
    {
        int cost = d[i][k].c + d[k + 1][j].c + d[i][k].a * d[i][k].b * d[k + 1][j].b;
        if(d[i][j].c == cost)
        {
            putchar('(');
            R(i, k);
            R(k + 1, j);
            putchar(')');
            return;
        }
    }
}

int main()
{
    int n;
    freopen("matrix.in",  "r", stdin);
    freopen("matrix.out", "w", stdout);
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            d[i][j].c = INF;
        }
    }
    for(int i = 0; i < n; i++)
    {
        cin >> d[i][i].a >> d[i][i].b;
        d[i][i].c = 0;
    }
    D(0, n - 1);
    R(0, n - 1);
    putchar('\n');
    return 0;
}
