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
int paths[105][10005];
vector<map<int, int>> g;
vector<map<int, int>> ginv;
set<int> alive = {0};
 
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
 
int main() {
    freopen("problem4.in",  "r", stdin);
    freopen("problem4.out", "w", stdout);
 
    int n, m, k, l;
    cin >> n >> m >> k >> l;
 
    vector<int> term(k);
    for (int i = 0; i < k; i++) {
        cin >> term[i];
        term[i]--;
    }
 
    g.resize(n);
    ginv.resize(n);
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
 
    // count paths
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
