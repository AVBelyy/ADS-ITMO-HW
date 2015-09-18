#include <iostream>
#include <utility>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main() {
    freopen("problem1.in",  "r", stdin);
    freopen("problem1.out", "w", stdout);

    string s;
    cin >> s;
    
    int n, m, k;
    cin >> n >> m >> k;

    set<int> t;
    for (int i = 0; i < k; i++) {
        int term_state;
        cin >> term_state;
        t.insert(term_state - 1);
    }

    vector<map<char, int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        g[u - 1][c] = v - 1;
    }

    int aut_pos = 0;
    bool can = true;
    for (char c : s) {
        if (!g[aut_pos].count(c)) {
            can = false;
            break;
        }
        aut_pos = g[aut_pos][c];
    }

    cout << (can && t.count(aut_pos) ? "Accepts" : "Rejects") << endl;
    return 0;
}
