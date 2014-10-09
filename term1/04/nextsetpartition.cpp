#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

bool U[201];

int main()
{
    int n, t, k;
    char c;
    bool flag;
    freopen("nextsetpartition.in",  "r", stdin);
    freopen("nextsetpartition.out", "w", stdout);
    while(1)
    {
        int i, cur = 0;
        cin >> n >> k;
        if(n == 0 && k == 0) break;
        vector< vector<int> > A(n);
        for(int i = 0; i < n; i++)
        {
            scanf("%d%c", &t, &c);
            A[cur].push_back(t);
            if(c == '\n') cur++;
        }
        flag = false;
        for(i = 1; i <= n; i++)
        {
            U[i] = false;
        }
        for(i = k - 1; i >= 0; i--)
        {
            for(int j = *(A[i].end() - 1) + 1; j <= n; j++)
            {
                if(U[j])
                {
                    U[j] = false;
                    A[i].push_back(j);
                    flag = true;
                    break;
                }
            }
            if(flag) break;
            int len = A[i].size();
            for(int j = len - 1; j >= 0; j--)
            {
                if(flag) break;
                U[A[i][j]] = true;
                if(len < 3) continue;
                for(int k = A[i][j] + 1; k <= n; k++)
                {
                    if(U[k])
                    {
                        A[i][j] = k;
                        U[k] = false;
                        A[i].erase(A[i].begin() + j + 1, A[i].end());
                        flag = true;
                        break;
                    }
                }
            }
            if(flag) break;
        }
        if(flag)
        {
            for(int j = 1; j <= n; j++)
            {
                if(U[j])
                {
                    A[++i].clear();
                    A[i].push_back(j);
                }
            }
        } else {
            for(i = 0; i < n; i++)
            {
                A[i].clear();
                A[i].push_back(i + 1);
            }
            i--;
        }
        int cnt = i;
        cout << n << " " << cnt + 1 << endl;
        for(int i = 0; i <= cnt; i++)
        {
            int len = A[i].size();
            for(int j = 0; j < len; j++)
            {
                cout << A[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
