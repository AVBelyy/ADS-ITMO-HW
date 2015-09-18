#include <iostream>
#include <cstdio>
#include <vector>

const int NMAX = 100;
const int MMAX = 2000;
const int COLMAX = 100;

struct edge_t {
    int u, v;

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
    freopen("multispan.in", "r", stdin);
    cin >> n >> m;
    cout << "Testing " << n << " " << m << endl;
    edges.resize(m + 1);
    dsu_build();
    for (int i = 1; i <= m; i++) {
        edge_t e;
        cin >> e.u >> e.v;
        edges[i] = e;
        dsu_union(e.u, e.v);
    }
   
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dsu_get(i) != dsu_get(j)) {
                cout << "Not connected" << endl;
                return 1;
            }
        }
    }

    cout << "OK" << endl;
    return 0;
}
