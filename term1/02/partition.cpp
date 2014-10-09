#include <iostream>
#include <string>

using namespace std;

void C(string s, int n, int k)
{
    for(int i = k; i <= n/2; i++)
    {
        C(s + to_string(i) + '+', n - i, i);
    }
    cout << s << n << endl;
}

int main()
{
    int n;
    freopen("partition.in",  "r", stdin);
    freopen("partition.out", "w", stdout);
    cin >> n;
    C("", n, 1);
    return 0;
}
