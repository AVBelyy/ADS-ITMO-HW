#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct vertex {
    int es[26];
    bool term;
    bool used;
};

vector<vertex> G[2];

bool bfs(int s1, int s2) {
    queue<pair<int, int>> q;
    q.emplace(s1, s2);
    G[0][s1].used = true;
    G[1][s2].used = true;
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        int u = p.first, v = p.second;
        if (G[0][u].term != G[1][v].term) {
            return false;
        }
        for (char c = 'a'; c <= 'z'; c++) {
            int toU = G[0][u].es[c - 'a'];
            int toV = G[1][v].es[c - 'a'];
            if (!G[0][toU].used || !G[1][toV].used) {
                q.emplace(toU, toV);
                G[0][toU].used = true;
                G[1][toV].used = true;
            }
        }
    }
    return true;
}

int main() {
    int n, m, k;
    freopen("equivalence.in",  "r", stdin);
    freopen("equivalence.out", "w", stdout);

    for (int t = 0; t < 2; t++) {
        int n, m, k;
        cin >> n >> m >> k;
        n++;
        G[t].resize(n);
        for (int i = 0; i < k; i++) {
            int term;
            cin >> term;
            G[t][term].term = true;
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            char c;
            cin >> u >> v >> c;
            G[t][u].es[c - 'a'] = v;
        }
    }
    cout << (bfs(1, 1) ? "YES" : "NO") << endl;

    return 0;
}
