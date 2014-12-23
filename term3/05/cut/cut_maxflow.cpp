#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <queue>

const int Inf = 1e9 + 2007;

struct Edge {
    int To;
    int C, F;

    Edge() {}
    Edge(int To, int C, int F) : To(To), C(C), F(F) {}
};

int N, M;
int Start, End;
std::vector<std::vector<Edge>> G;
std::vector<std::vector<Edge>> RG;
std::vector<int> D;
std::vector<int> Parent;
std::vector<bool> Used;

bool bfs() {
    std::queue<int> Q;
    D.assign(N, Inf);
    Q.push(Start);
    D[Start] = 0;

    while (!Q.empty()) {
        int V = Q.front();
        Q.pop();
        for (int I = 0; I < G[V].size(); I++) {
            int To = G[V][I].To;
            if (D[To] > D[V] + 1 && G[V][I].F < G[V][I].C) {
                D[To] = D[V] + 1;
                Q.push(To);
            }
        }
    }

    return D[End] != Inf;
}

int dfs(int V, int Flow) {
    if (Flow == 0) return 0;
    if (V == End) return Flow;

    for (int & I = Parent[V]; I < G[V].size(); I++) {
        Edge & E = G[V][I];
        if (D[E.To] != D[V] + 1) continue;
        int FlowCnt = dfs(E.To, std::min(Flow, E.C - E.F));
        if (FlowCnt != 0) {
            E.F += FlowCnt;
            for (int J = 0; J < G[E.To].size(); J++) {
                if (G[E.To][J].To == V) {
                    G[E.To][J].F -= FlowCnt;
                }
            }
            return FlowCnt;
        }
    }

    return 0;
}

void dfs2(int V) {
    Used[V] = true;

    for (int I = 0; I < RG[V].size(); I++) {
        Edge & E = RG[V][I];
        if (!Used[E.To]) {
            dfs2(E.To);
        }
    }
}

int main() {
    freopen("cut.in",  "r", stdin);
    freopen("cut.out", "w", stdout);
 
    scanf("%d%d", &N, &M);

    Start = 0;
    End = N - 1;

    G.resize(N);

    for (int I = 0; I < M; I++) {
        int U, V, C;
        scanf("%d%d%d", &U, &V, &C);
        G[U - 1].push_back(Edge(V - 1, C, 0));
        G[V - 1].push_back(Edge(U - 1, C, 0));
    }
 
    // Search for max flow
    while (true) {
        if (!bfs()) break;
        Parent.assign(N, 0);
        while (dfs(Start, Inf));
    }

    RG.resize(N);
    
    // Build residual network
    for (int V = 0; V < N; V++) {
        for (Edge & E : G[V]) {
            if (E.C - E.F > 0) {
                RG[V].push_back(E);
            }
        }
    }

    // Check vertices for reachability in RG
    std::vector<int> SS;
    Used.assign(N, false);
    dfs2(Start);
    for (int V = 0; V < N; V++) {
        if (Used[V]) {
            SS.push_back(V);
        }
    }

    // Output S set
    std::cout << SS.size() << std::endl;
    for (int S : SS) {
        std::cout << S + 1 << ' ';
    }
    std::cout << std::endl;
 
    return 0;
}
