#include <stdio.h>
#include <stdint.h>
#include <iostream>

using namespace std;

uint64_t n;
bool used[19];

int num(int p)
{
    int res = 0;
    while(p >= 0)
    {
        res = (res + 1) % (n + 1);
        if(!used[res]) p--;
    }
    used[res] = true;
    return res;
}

int main()
{
    int cnt;
    uint64_t k;
    uint64_t F[19];
    freopen("num2perm.in",  "r", stdin);
    freopen("num2perm.out", "w", stdout);
    cin >> n >> k;
    F[0] = 1;
    for(int i = 0; i < n; i++)
    {
        F[i + 1] = (i + 1) * F[i];
    }
    for(cnt = n - 1; k != 0; cnt--)
    {
        uint64_t p = k / F[cnt];
        k %= F[cnt];
        cout << num(p) << " ";
    }
    for(int i = 0; i <= cnt; i++)
    {
        cout << num(0) << " ";
    }
    cout << endl;
    return 0;
}
