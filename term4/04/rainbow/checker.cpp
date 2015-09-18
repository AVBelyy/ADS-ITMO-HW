#include <iostream>
#include <cstdio>
#include <vector>

const int NMAX = 100;
const int MMAX = 5000;
const int COLMAX = 100;

struct edge_t {
    int u, v, col;

    bool operator<(edge_t other) const {
        return u == other.u ? v < other.v : u < other.u;
    }
};

struct dsu_t {
    int rank;
    int parent;
};

using namespace std;

int n, m;
dsu_t dsu[NMAX + 1];
vector<edge_t> edges;

int dsu_get(int x) {
    if (dsu[x].parent == x) {
        return x;
    } else {
        return dsu[x].parent = dsu_get(dsu[x].parent);
    }
}

void dsu_union(int x, int y) {
    x = dsu_get(x);
    y = dsu_get(y);
    if (x != y) {
        if (dsu[x].rank == dsu[y].rank) {
            dsu[x].rank++;
        }
        if (dsu[x].rank < dsu[y].rank) {
            dsu[x].parent = y;
        } else {
            dsu[y].parent = x;
        }
    }
}

void dsu_build() {
    for (int i = 1; i <= n; i++) {
        dsu[i].rank = 0;
        dsu[i].parent = i;
    }
}

int main() {
    freopen("rainbow.in", "r", stdin);
    cin >> n >> m;
    cout << "Testing " << n << " " << m << endl;
    edges.resize(m + 1);
    for (int i = 1; i <= m; i++) {
        edge_t e;
        cin >> e.u >> e.v >> e.col;
        edges[i] = e;
    }
    dsu_build();
   
    freopen("rainbow.out", "r", stdin);
    int k;
    cin >> k;
    vector<int> J(k);
    for (int i = 0; i < k; i++) {
        cin >> J[i];
    }
    
    for (int i : J) {
        if (dsu_get(edges[i].u) == dsu_get(edges[i].v)) {
            cout << "Not a tree" << endl;
            return 1;
        }
        dsu_union(edges[i].u, edges[i].v);
    }

    vector<bool> used(COLMAX + 1);
    for (int i : J) {
        if (used[edges[i].col]) {
            cout << "Same colors" << endl;
            return 1;
        }
        used[edges[i].col] = true;
    }

    cout << "OK" << endl;
    return 0;
}
