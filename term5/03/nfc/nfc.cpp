#include <iostream>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

int n;
char S;

int DP[256][105][105];
string w;

bool nterm(char c) {
    return 'A' <= c && c <= 'Z';
}

const int MOD = 1000000007;

struct rule {
    char tr[2];
    bool leaf;
};
map<char, vector<rule>> g;

int dp(char c, int l, int r) {
    if (DP[c][l][r] == -1) {
        int ans = 0;
        for (rule & R : g[c]) {
            if (R.leaf) {
               ans = ((l + 1 == r && w[l] == R.tr[0]) + ans) % MOD;
            } else {
                for (int i = l + 1; i < r; i++) {
                    ans = (((long long) dp(R.tr[0], l, i)) * dp(R.tr[1], i, r) + ans) % MOD;
                }
            }
        }
        DP[c][l][r] = ans;
    }
    return DP[c][l][r];
}

int main() {
    string buf;

    freopen("nfc.in",  "r", stdin);
    freopen("nfc.out", "w", stdout);

    cin >> n >> S;
    getline(cin, buf);
    memset(DP, 255, sizeof(DP));

    for (int i = 0; i < n; i++) {
        getline(cin, buf);
        char c = buf[0];
        rule r;
        r.tr[0] = buf[5];
        if (nterm(buf[5])) {
            r.tr[1] = buf[6];
            r.leaf = false;
        } else {
            r.leaf = true;
        }
        g[c].push_back(r);
    }
    cin >> w;
    cout << dp(S, 0, w.size()) << endl;

    return 0;
}
