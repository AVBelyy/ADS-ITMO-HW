#include <iostream>
#include <utility>
#include <cstdio>
#include <string>
#include <vector>
#include <deque>
#include <set>
#include <map>

using namespace std;

bool already[105][10005];

int main() {
    freopen("problem2.in",  "r", stdin);
    freopen("problem2.out", "w", stdout);

    string s;
    cin >> s;
    
    int n, m, k;
    cin >> n >> m >> k;

    vector<bool> t(n);
    for (int i = 0; i < k; i++) {
        int term_state;
        cin >> term_state;
        t[term_state - 1] = true;
    }

    vector<map<char, vector<int>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        g[u - 1][c].push_back(v - 1);
    }

    bool ok = false;
    deque<pair<int, int>> q = {{0, 0}};
    while (!q.empty()) {
        auto ss = q.front();
        int cur = ss.first, i = ss.second;
        q.pop_front();
        if (i == s.size()) {
            if (t[cur]) {
                ok = true;
                break;
            } else {
                continue;
            }
        }
        if (!g[cur].count(s[i])) {
            continue;
        }
        for (int next : g[cur][s[i]]) {
            if (!already[next][i + 1]) {
                already[next][i + 1] = true;
                q.emplace_back(next, i + 1);
            }
        }
    }

    cout << (ok ? "Accepts" : "Rejects") << endl;
    return 0;
}
