#include <stdio.h>
#include <stdint.h>
#include <iostream>

using namespace std;

int n;
bool used[19];

int by_num(int p)
{
    int res = 0;
    for(int i = 1; i < p; i++)
    {
        if(used[i])
        {
            res++;
        }
    }
    used[p] = true;
    return p - res - 1;
}

int main()
{
    uint64_t ans = 0;
    uint64_t F[19];
    freopen("perm2num.in",  "r", stdin);
    freopen("perm2num.out", "w", stdout);
    cin >> n;
    F[0] = 1;
    for(int i = 0; i < n; i++)
    {
        F[i + 1] = (i + 1) * F[i];
    }
    for(int i = 0; i < n; i++)
    {
        int p;
        cin >> p;
        ans += by_num(p) * F[n - i - 1];
    }
    cout << ans << endl;
    return 0;
}
