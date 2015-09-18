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

bool infinite;
vector<map<int, int>> g;
vector<map<int, int>> ginv;
vector<int> paths;
vector<bool> visited;
set<int> alive = {0};

void findCycle(int v) {
    if (infinite) return;

    for (auto p: ginv[v]) {
        int u = p.first;
        if (!alive.count(u)) {
            continue;
        }
        if (visited[u] && !infinite) {
            infinite = true;
            return;
        } else {
            visited[u] = true;
            findCycle(u);
            visited[u] = false;
        }
    }
}

int countPaths(int v) {
    if (paths[v] == -1) {
        paths[v] = 0;
        for (auto p : ginv[v]) {
            int u = p.first, cnt = p.second;
            if (alive.count(u)) {
                paths[v] = (((long long) countPaths(u)) * cnt + paths[v]) % MOD;
            }
        }
    }
    return paths[v];
}

int main() {
    freopen("problem3.in",  "r", stdin);
    freopen("problem3.out", "w", stdout);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> term(k);
    for (int i = 0; i < k; i++) {
        cin >> term[i];
        term[i]--;
    }

    g.resize(n);
    ginv.resize(n);
    visited.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        ginv[v - 1][u - 1] = g[u - 1][v - 1] = g[u - 1].count(v - 1) ? g[u - 1][v - 1] + 1 : 1;
    }

    // find out which vertices are reachable
    vector<int> q = {0};
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

    // check if number of words is infinite
    // make it recursive
    for (int v : term) {
        if (!alive.count(v)) {
            continue;
        }
        findCycle(v);
        if (infinite) {
            cout << -1 << endl;
            return 0;
        }
    }

    // count paths
    paths.assign(n, -1);
    paths[0] = 1;

    int ans = 0;
    for (int u : term) {
        if (!alive.count(u)) {
            continue;
        }
        ans = (ans + countPaths(u)) % MOD;
    }
    cout << ans << endl;
    return 0;
}
