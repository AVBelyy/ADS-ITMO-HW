#include <iostream>

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// TODO: Implement Radix sort for O(N*logN) sorting

int main()
{
    int len;
    freopen("bwt.in",  "r", stdin);
    freopen("bwt.out", "w", stdout);
    string s;
    cin >> s;
    len = s.size();
    vector<string> S(len);
    S[0] = s;
    for(int i = 1; i < len; i++)
    {
        S[i] = S[i-1].substr(1) + S[i-1][0];
    }
    sort(S.begin(), S.end());
    for(int i = 0; i < len; i++)
    {
        cout << S[i][len-1];
    }
    cout << endl;
    return 0;
}
