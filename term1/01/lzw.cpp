#include <iostream>

#include <string>
#include <map>

using namespace std;

map<string, int> D;

int main()
{
    int code = 0;
    string s, t;
    freopen("lzw.in",  "r", stdin);
    freopen("lzw.out", "w", stdout);
    cin >> s;
    for(char c = 'a'; c <= 'z'; c++)
    {
        D[string(1, c)] = code++;
    }
    for(int i = 0; i < s.size(); i++)
    {
        char c = s[i];

        if(D.find(t + c) != D.end())
        {
            t += c;
        } else {
            cout << D[t] << " ";
            D[t + c] = code++;
            t = c;
        }
    }
    cout << D[t] << endl;
    return 0;
}
