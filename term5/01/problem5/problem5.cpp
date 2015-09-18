#include <algorithm>
#include <iostream>
#include <utility>
#include <cstdio>
#include <string>
#include <vector>
#include <deque>
#include <set>
#include <map>

using namespace std;

const int MOD = 1e9 + 7;

int paths[105][10005];
map<int, int> g[105];
map<int, int> ginv[105];
vector<map<char, vector<int>>> ng;
set<int> nalive = {0};
set<int> alive = {0};
vector<int> nterm;
vector<int> term;

int countPaths(int v, int l) {
    if (paths[v][l] == -1) {
        paths[v][l] = 0;
        if (l != 0) {
            for (auto p : ginv[v]) {
                int u = p.first, cnt = p.second;
                if (alive.count(u)) {
                    paths[v][l] = (((long long) countPaths(u, l - 1)) * cnt + paths[v][l]) % MOD;
                }
            }
        }
    }
    return paths[v][l];
}

int nfa2dfa() {
    vector<set<int>> dstates = {{0}};
    deque<pair<set<int>, int>> q = {{{0}, 0}};

    while (!q.empty()) {
        auto p = q.front();
        auto & pd = p.first;
        int u = p.second;
        q.pop_front();
        for (char c = 'a'; c <= 'z'; c++) {
            set<int> qd;
            for (int p : pd) {
                auto & us = ng[p][c];
                copy(us.begin(), us.end(), inserter(qd, qd.begin()));
            }

            int v = find(dstates.begin(), dstates.end(), qd) - dstates.begin();
            if (v == dstates.size() && qd.size() != 0) {
                dstates.push_back(qd);
                q.emplace_back(qd, v);
            }
            if (qd.size() != 0) {
                ginv[v][u] = g[u][v] = g[u].count(v) ? g[u][v] + 1 : 1;
            }
        }
    }

    int i = 0;
    for (auto & st : dstates) {
        for (int t : nterm) {
            if (st.count(t)) {
                term.push_back(i);
                break;
            }
        }
        i++;
    }

    return dstates.size();
}

int main() {
    freopen("problem5.in",  "r", stdin);
    freopen("problem5.out", "w", stdout);

    int nn, m, k, l;
    cin >> nn >> m >> k >> l;

    nterm.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> nterm[i];
        nterm[i]--;
    }

    // read NFA
    ng.resize(nn);
    for (int i = 0; i < m; i++) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        ng[u - 1][c].push_back(v - 1);
    }

    // find out which vertices are reachable in NFA
    vector<int> q = {0};
    while (!q.empty()) {
        int u = q.back();
        q.pop_back();
        for (auto & p : ng[u]) {
            for (int v : p.second) {
                if (!nalive.count(v)) {
                    nalive.insert(v);
                    q.push_back(v);
                }
            }
        }
    }

    // construct DFA from NFA
    int n = nfa2dfa();

    // find out which vertices are reachable in DFA
    q = {0};
    while (!q.empty()) {
        int u = q.back();
        q.pop_back();
        for (auto p : g[u]) {
            int v = p.first;
            if (!alive.count(v)) {
                alive.insert(v);
                q.push_back(v);
            }
        }
    }

    // count paths in DFA
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= l; j++) {
            paths[i][j] = -1;
        }
    }
    paths[0][0] = 1;
    for (int u : term) {
        if (!alive.count(u)) {
            continue;
        }
        ans = (ans + countPaths(u, l)) % MOD;
    }
    cout << ans << endl;
    return 0;
}
