#include <iostream>

#include <string>
#include <list>

using namespace std;

list<char> C;

int main()
{
    string s;
    freopen("mtf.in",  "r", stdin);
    freopen("mtf.out", "w", stdout);
    cin >> s;
    for(char c = 'a'; c <= 'z'; c++)
    {
        C.push_back(c);
    }
    for(int i = 0; i < s.size(); i++)
    {
        char c = s[i];
        int pos = 1;
        for(list<char>::iterator it = C.begin(); it != C.end(); it++, pos++)
        {
            if(c == *it)
            {
                cout << pos << " ";
                C.splice(C.begin(), C, it);
                break;
            }
        }
    }
    cout << endl;
    return 0;
}
