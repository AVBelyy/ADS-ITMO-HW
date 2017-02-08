#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct vertex {
    map<char, int> es;
    bool term;
    bool visited;
};

int n, m, k;
vector<vertex> G[2];

bool dfs(vertex & u, vertex & v) {
    u.visited = true;
    if (u.term != v.term) {
        return false;
    }

    for (auto & e : u.es) {
        char c = e.first;
        if (!v.es.count(c)) {
            return false;
        }
        vertex & t1 = G[0][e.second];
        vertex & t2 = G[1][v.es[c]];
        if (!t1.visited && !dfs(t1, t2)) {
            return false;
        }
    }

    return true;
}

int main() {
    freopen("isomorphism.in",  "r", stdin);
    freopen("isomorphism.out", "w", stdout);

    int n[2], m[2], k[2];
    for (int t = 0; t < 2; t++) {
        cin >> n[t] >> m[t] >> k[t];
        G[t].resize(n[t]);
        for (int i = 0; i < k[t]; i++) {
            int v;
            cin >> v;
            G[t][v - 1].term = true;
        }
        for (int i = 0; i < m[t]; i++) {
            int u, v;
            char c;
            cin >> u >> v >> c;
            G[t][u - 1].es[c] = v - 1;
        }
    }

    if (n[0] != n[1] || m[0] != m[1] || k[0] != k[1]) {
        cout << "NO" << endl;
    } else {
        cout << (dfs(G[0][0], G[1][0]) ? "YES" : "NO") << endl;
    }

    return 0;
}
