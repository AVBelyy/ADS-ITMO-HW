#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int n, m, k;
int compCount;

typedef unordered_set<int> eq_class;
struct row {
    int to[26];
};
struct row2 {
    vector<int> to[26];
};
vector<eq_class> P;
vector<vector<int>> g;
vector<row> G;
vector<int> N;
vector<row> edges;
vector<row2> Inv;
vector<bool> reachable;
vector<int> comp;
vector<pair<pair<int, int>, char>> brandNewEdges;

void buildReachable(int u) {
    reachable[u] = true;
    for (int v : g[u]) {
        if (!reachable[v]) {
            buildReachable(v);
        }
    }
}

bool valid(int u) {
    return comp[u] != comp[0] && reachable[u];
}

int vxCount = 0;
void renumberGraph(int u) {
    if (N[u] == 0) {
        N[u] = ++vxCount;
        for (char c = 'a'; c <= 'z'; c++) {
            if (G[u].to[c - 'a'] != -1) {
                renumberGraph(G[u].to[c - 'a']);
                brandNewEdges.push_back({{N[u], N[G[u].to[c - 'a']]}, c});
            }
        }
    }
}

void byEquivalenceClasses(eq_class & Q, eq_class & F) {
    eq_class QF;
    comp.resize(n);
    for (int i = 0; i < n; i++) {
        if (F.count(i)) {
            comp[i] = 0;
        } else {
            comp[i] = 1;
            QF.insert(i);
        }
    }
    P = {F, QF};
    queue<pair<int, char>> Queue;
    for (char c = 'a'; c <= 'z'; c++) {
        Queue.emplace(0, c);
        Queue.emplace(1, c);
    }
    while (!Queue.empty()) {
        auto & p = Queue.front();
        Queue.pop();
        auto & C = P[p.first];
        auto a = p.second;
        unordered_map<int, vector<int>> Involved;
        for (int q : C) {
            for (int r : Inv[q].to[a - 'a']) {
                int i = comp[r];
                Involved[i].push_back(r);
            }
        }
        for (auto p : Involved) {
            int i = p.first;
            if (Involved[i].size() < P[i].size()) {
                int j = P.size();
                P.push_back(unordered_set<int>());
                for (int r : Involved[i]) {
                    P[i].erase(r);
                    P[j].insert(r);
                }
                if (P[j].size() > P[i].size()) {
                    swap(P[i], P[j]);
                }
                for (int r : P[j]) {
                    comp[r] = j;
                }
                for (char c = 'a'; c <= 'z'; c++) {
                    Queue.emplace(j, c);
                }
            }
        }
    }
    compCount = P.size();
}

int main() {
    freopen("fastminimization.in",  "r", stdin);
    freopen("fastminimization.out", "w", stdout);

    scanf("%d%d%d", &n, &m, &k);
    n++;
    Inv.resize(n);
    edges.resize(n);
    g.resize(n);
    G.resize(n);
    N.resize(n);
    reachable.resize(n);
    eq_class Q, F, FF;

    for (int i = 0; i < k; i++) {
        int t;
        scanf("%d", &t);
        F.insert(t);
        FF.insert(t);
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        char s[4], c;
        scanf("%d%d%s", &u, &v, s);
        c = s[0];
        Inv[v].to[c - 'a'].push_back(u);
        edges[u].to[c - 'a'] = v;
        g[u].push_back(v);
    }
    for (int i = 0; i < n; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            if (edges[i].to[c - 'a'] == 0) {
                Inv[0].to[c - 'a'].push_back(i);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        Q.insert(i);
    }

    buildReachable(1);

    byEquivalenceClasses(Q, F);

    // Construct new DFA
    int newN = compCount;
    for (int i = 0; i < n; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            G[i].to[c - 'a'] = -1;
        }
    }
    for (int i = 0; i < n; i++) {
        if (!valid(i)) {
            continue;
        }
        for (char c = 'a'; c <= 'z'; c++) {
            if (valid(edges[i].to[c - 'a'])) {
                G[comp[i]].to[c - 'a'] = comp[edges[i].to[c - 'a']];
            }
        }
    }
    renumberGraph(comp[1]);
    int newM = brandNewEdges.size();
    unordered_set<int> newTerminal;
    for (int i = 1; i < n; i++) {
        if (FF.count(i) && valid(i)) {
            newTerminal.insert(N[comp[i]]);
        }
    }
    int newK = newTerminal.size();

    // output new DFA
    printf("%d %d %d\n", vxCount, newM, newK);
    for (int t : newTerminal) {
        printf("%d ", t);
    }
    printf("\n");
    for (auto & p : brandNewEdges) {
        printf("%d %d %c\n", p.first.first, p.first.second, p.second);
    }

    return 0;
}
