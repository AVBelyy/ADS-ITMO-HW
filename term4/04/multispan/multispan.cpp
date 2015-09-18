
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
 
using namespace std;
 
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
 
int n, m;
vector<edge_t> edges;
set<int> J;
vector<bool> SJ(MMAX + 1);
dsu_t dsu[NMAX + 1];
vector<bool> X2;
vector<vector<int>> ans;
 
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
 
int G[NMAX + 1][NMAX + 1][2];
int Gs[NMAX + 1];
int Enter[NMAX + 1];
int Ret[NMAX + 1];
vector<bool> Used;
 
int Time = 0;
void bridge_dfs(int V, int EdgeNum = -1) {
    if (Used[V]) return;
 
    Used[V] = true;
    Enter[V] = Ret[V] = Time;
    Time++;
 
    int Prev = EdgeNum == -1 ? -1 : V ^ edges[EdgeNum].u ^ edges[EdgeNum].v;
    for (int i = 0; i< Gs[V]; i++) {
        int U = G[V][i][0];
        int NextEdgeNum = G[V][i][1];
        if (U == Prev) continue;
 
        if (Used[U]) {
            if (Ret[V] > Enter[U]) {
                Ret[V] = Enter[U];
            }
        } else {
            bridge_dfs(U, NextEdgeNum);
            if (Ret[V] > Ret[U]) {
                Ret[V] = Ret[U];
            }
            if (Ret[U] > Enter[V]) {
                X2[NextEdgeNum] = false;
            }
        }
    }
}
 
void bridge_build() {
    X2.assign(m + 1, false);
    for (int i = 1; i <= n; i++) {
        Gs[i] = 0;
    }
    Used.assign(n + 1, false);
    for (int i = 1; i <= m; i++) {
        if (SJ[i]) {
            edge_t e = edges[i];
            G[e.u][Gs[e.u]][0] = e.v;
            G[e.u][Gs[e.u]++][1] = i;
            G[e.v][Gs[e.v]][0] = e.u;
            G[e.v][Gs[e.v]++][1] = i;
            X2[i] = true;
        }
    }
    for (int i = 1; i <= n; i++) {
        Time = 0;
        bridge_dfs(i);
    }
}
 
int main() {
    freopen("multispan.in",  "r", stdin);
    freopen("multispan.out", "w", stdout);
     
    cin >> n >> m;
 
    edges.resize(m + 1);
    X2.resize(m + 1);
 
    for (int i = 1; i <= m; i++) {
        edge_t e;
        cin >> e.u >> e.v;
        SJ[i] = true;
        edges[i] = e;
    }
    vector<bool> used(m + 1);
    vector<int> parent(m + 1);
    set<int> JJ;
    int Q[MMAX + 1];
    int Ql, Qr;
    while (true) {
        while (true) {
            // build substitution graph
            for (int i = 1; i <= m; i++) {
                subst_edges_cnt[i] = 0;
            }
            JJ = J;
            for (int i : JJ) {
                J.erase(i);
                SJ[i] = true;
                dsu_build();
                bridge_build();
                for (int j = 1; j <= m; j++) {
                    if (!SJ[j]) continue;
                    if (dsu_get(edges[j].u) != dsu_get(edges[j].v)) {
                        subst_edges[i][subst_edges_cnt[i]++] = j;
                    }
                    if (X2[j]) {
                        subst_edges[j][subst_edges_cnt[j]++] = i;
                    }
                }
                SJ[i] = false;
                J.insert(i);
            }
 
            // build X1 and X2
            dsu_build();
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
            }
            // find B = {set of all bridges in X \ S}, then X2 = X \ B
            bridge_build();
             
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
 
        if (J.size() != n - 1) break;
        vector<int> Jans(J.size());
        copy(J.begin(), J.end(), Jans.begin());
        ans.push_back(Jans);
        for (int i : Jans) {
            SJ[i] = false;
        }
        J.clear();
    }
    for (int i = 1; i <= n; i++) {
        dsu[i].rank = 0;
        dsu[i].parent = i;
    }
    ans.push_back(vector<int>());
    for (int i = 1; i <= m; i++) {
        if (SJ[i]) {
            edge_t e = edges[i];
            if (dsu_get(e.u) != dsu_get(e.v)) {
                dsu_union(e.u, e.v);
                ans[ans.size() - 1].push_back(i);
            }
        }
    }
    if (ans[ans.size() - 1].size() != n - 1) {
        ans.pop_back();
    }
    cout << ans.size() << endl;
    for (vector<int> & jans : ans) {
        for(int i : jans) {
            cout << i << ' ';
        }
        cout << endl;
    }
     
    return 0;
}
