#include <cstdio>
#include <iostream>

using namespace std;

int C[31][31];

void gen_C()
{
    for(int i = 0; i <= 30; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            if(j == 0)
            {
                C[i][j] = 1;
            } else if(i == 0) {
                C[i][j] = 0;
            } else { 
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            }
        }
    }
}

int main()
{
    int n, N, k, K, m, cnt = 1;
    freopen("num2choose.in",  "r", stdin);
    freopen("num2choose.out", "w", stdout);
    cin >> n >> k >> m;
    gen_C();
    N = n - 1;
    K = k - 1;
    while(m != 0)
    {
        if(m >= C[N][K])
        {
            m -= C[N][K];
            N--;
        } else {
            cout << n - N << " ";
            cnt++;
            N--;
            K--;
        }
    }
    cout << n - N << " ";
    for(int i = 1; i <= k - cnt; i++)
    {
        cout << n - N + i << " ";
    }
    cout << endl;
    return 0;
}
