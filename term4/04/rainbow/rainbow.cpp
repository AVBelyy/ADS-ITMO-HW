#include <iostream>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;

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

int n, m;
vector<edge_t> edges;
set<int> J;
vector<bool> SJ(MMAX + 1);
dsu_t dsu[NMAX + 1];
vector<bool> used_colors(COLMAX + 1);

int subst_edges[MMAX + 1][MMAX + 1];
int subst_edges_cnt[MMAX + 1];

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
    for (int i : J) {
        dsu_union(edges[i].u, edges[i].v);
    }
}

void colors_build() {
    used_colors.assign(COLMAX + 1, false);
    for (int i : J) {
        used_colors[edges[i].col] = true;
    }
}

int main() {
    freopen("rainbow.in",  "r", stdin);
    freopen("rainbow.out", "w", stdout);
    
    cin >> n >> m;
    edges.resize(m + 1);
    for (int i = 1; i <= m; i++) {
        edge_t e;
        cin >> e.u >> e.v >> e.col;
        SJ[i] = true;
        edges[i] = e;
    }

    vector<bool> X2(m + 1);
    vector<bool> used(m + 1);
    vector<int> parent(m + 1);
    set<int> JJ;
    int Q[MMAX + 1];
    int Ql, Qr;
    while (true) {
        // build substitution graph
        for (int i = 1; i <= m; i++) {
            subst_edges_cnt[i] = 0;
        }
        colors_build();
        JJ = J;
        for (int i : JJ) {
            J.erase(i);
            SJ[i] = true;
            dsu_build();
            for (int j = 1; j <= m; j++) {
                if (!SJ[j]) continue;
                if (dsu_get(edges[j].u) != dsu_get(edges[j].v)) {
                    subst_edges[i][subst_edges_cnt[i]++] = j;
                }
                if (edges[i].col == edges[j].col || !used_colors[edges[j].col]) {
                    subst_edges[j][subst_edges_cnt[j]++] = i;
                }
            }
            SJ[i] = false;
            J.insert(i);
        }

        // build X1 and X2
        dsu_build();
        colors_build();
        X2.assign(m + 1, false);
        used.assign(m + 1, false);
        parent.assign(m + 1, -1);
        Ql = Qr = 0;
        for (int i = 1; i <= m; i++) {
            if (!SJ[i]) continue;
            if (dsu_get(edges[i].u) != dsu_get(edges[i].v)) {
                Q[Qr++] = i;
                used[i] = true;
            }
            if (!used_colors[edges[i].col]) {
                X2[i] = true;
            }
        }
        
        // build P
        int last = -1;
        while (Ql != Qr) {
            int u = Q[Ql++];
            if (X2[u]) {
                last = u;
                break;
            }
            for (int i = 0; i < subst_edges_cnt[u]; i++) {
                int v = subst_edges[u][i];
                if (!used[v]) {
                    used[v] = true;
                    parent[v] = u;
                    Q[Qr++] = v;
                }
            }
        }
        if (last == -1) break;
        while (last != -1) {
            if (J.count(last) == 0) {
                J.insert(last);
                SJ[last] = false;
            } else {
                J.erase(last);
                SJ[last] = true;
            }
            last = parent[last];
        }
    }

    cout << J.size() << endl;
    for (int i : J) {
        cout << i << ' ';
    }
    cout << endl;

    return 0;
}
