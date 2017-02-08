#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

int n, S;

int DP[1005][105][105];
string w;

struct elem {
    bool term;
    int id;

    elem(bool term, int id) : term(term), id(id) {}
};

bool nterm(char c) {
    return 'A' <= c && c <= 'Z';
}

const int MOD = 1000000007;

map<int, vector<vector<elem>>> g;

void remove_long_rules() {
    map<int, vector<vector<elem>>> gg;
    int ruleCount = 30;
    for (auto & p : g) {
        int c = p.first;
        for (vector<elem> & r : p.second) {
            if (r.size() <= 2) {
                gg[c].push_back(r);
            } else {
                // c_orig -> abcde
                // c -> aB
                // B -> bC
                // C -> cD
                // D -> de
                int PREV = c;
                for (int i = 0; i <= r.size() - 3; i++) {
                    int NEW = ruleCount++;
                    gg[PREV].push_back({r[i], {false, NEW}});
                    PREV = NEW;
                }
                gg[PREV].push_back({r[r.size() - 2], r[r.size() - 1]});
            }
        }
    }
    g = gg;
}

void remove_eps_rules() {
    set<int> bad;
    bool changed;
    do {
        changed = false;
        for (auto & R : g) {
            int c = R.first;
            auto & rs = R.second;
            for (auto & r : rs) {
                bool flag = true;
                for (elem & d : r) {
                    if (!d.term && bad.count(d.id)) {
                        flag = true;
                    } else {
                        flag = false;
                        break;
                    }
                }
                if (flag && bad.count(c) == 0) {
                    changed = true;
                    bad.insert(c);
                    break;
                }
            }
        }
    } while (changed);
    map<int, vector<vector<elem>>> gg;
    for (auto & R : g) {
        int c = R.first;
        auto & rs = R.second;
        for (auto & r : rs) {
            if (r.size() == 1) {
                gg[c].push_back(r);
            } else if (r.size() == 2) {
                if (bad.count(r[0].id) && bad.count(r[1].id)) {
                    gg[c].push_back({r[0]});
                    gg[c].push_back({r[0], r[1]});
                    gg[c].push_back({r[0]});
                    gg[c].push_back({r[1]});
                } else if (bad.count(r[0].id)) {
                    gg[c].push_back({r[0], r[1]});
                    gg[c].push_back({r[1]});
                } else if (bad.count(r[1].id)) {
                    gg[c].push_back({r[0], r[1]});
                    gg[c].push_back({r[0]});
                } else {
                    gg[c].push_back(r);
                }
            }
        }
    }
    if (bad.count(S)) {
        gg[1000].push_back({{false, S}});
        gg[1000].push_back({{}});
        S = 1000;
    }
    g = gg;
}

int dp(int c, int l, int r) {
    if (DP[c][l][r] == -2 || l >= r) {
        return 0;
    }
    if (DP[c][l][r] == -1) {
        int ans = 0;
        DP[c][l][r] = -2;
        for (vector<elem> & R : g[c]) {
            if (R.size() == 1) {
                if (R[0].term) {
                    ans = ((l + 1 == r && w[l] == R[0].id) + ans) % MOD;
                } else {
                    ans = (dp(R[0].id, l, r) + ans) % MOD;
                }
            } else if (R.size() == 2) {
                if (R[0].term && R[1].term) {
                    ans = ((l + 2 == r && w[l] == R[0].id && w[l + 1] == R[1].id) + ans) % MOD;
                } else if (R[0].term) {
                    ans = ((w[l] == R[0].id) * dp(R[1].id, l + 1, r) + ans) % MOD;
                } else if (R[1].term) {
                    ans = ((w[r - 1] == R[1].id) * dp(R[0].id, l, r - 1) + ans) % MOD;
                } else {
                    for (int i = l + 1; i < r; i++) {
                        ans = (((long long) dp(R[0].id, l, i)) * dp(R[1].id, i, r) + ans) % MOD;
                    }
                }
            }
        }
        DP[c][l][r] = ans;
    }
    return DP[c][l][r];
}

int main() {
    string buf;

    freopen("cf.in",  "r", stdin);
    freopen("cf.out", "w", stdout);

    char Sc;
    cin >> n >> Sc;
    S = Sc - 'A';
    getline(cin, buf);
    memset(DP, 255, sizeof(DP));

    for (int i = 0; i < n; i++) {
        getline(cin, buf);
        vector<elem> r;
        if (buf.size() > 5) {
            for (char c : buf.substr(5)) {
                if (nterm(c)) {
                    r.push_back({false, c - 'A'});
                } else {
                    r.push_back({true, c});
                }
            }
        }
        int c = buf[0] - 'A';
        g[c].push_back(r);
    }
    remove_long_rules();
    remove_eps_rules();
    cout << (int)S << endl;
    /*for (auto & p : g) {
        int c = p.first;
        for (vector<elem> & r : p.second) {
            cout << c << " ->";
            for (elem sr : r) {
                cout << ' ' << sr.id;
            }
            cout << endl;
        }
    }*/
    cin >> w;
    cout << (dp(S, 0, w.size()) ? "yes" : "no") << endl;

    return 0;
}
