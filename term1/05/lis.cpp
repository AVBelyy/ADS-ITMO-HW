#include <iostream>
#include <cstdio>
#include <list>

using namespace std;

#define max(a, b)   (((a) > (b)) ? (a) : (b))

int A[5000], DP[5000], P[5000];

int main()
{
    int n, len = 0, pos;
    freopen("lis.in",  "r", stdin);
    freopen("lis.out", "w", stdout);
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        int t = 0;
        cin >> A[i];
        DP[i] = 1;
        P[i] = -1;
        for(int j = 0; j < i; j++)
        {
            if(A[j] < A[i] && DP[j] + 1 > DP[i])
            {
                DP[i] = DP[j] + 1;
                P[i] = j;
            }
        }
        if(len < DP[i])
        {
            len = DP[i];
            pos = i;
        }
    }
    cout << len << endl;
    list<int> ans;
    while(pos != -1)
    {
        ans.push_front(A[pos]);
        pos = P[pos];
    }
    for(list<int>::iterator it = ans.begin(); it != ans.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}
