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
    int Num;

    Edge() {}
    Edge(int To, int C, int F, int Num) : To(To), C(C), F(F), Num(Num) {}
};

int N, M;
int Start, End;
std::vector< std::vector<Edge> > G;
std::vector<int> D;
std::vector<int> Parent;

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

int main() {
    freopen("maxflow.in",  "r", stdin);
    freopen("maxflow.out", "w", stdout);
 
    scanf("%d%d", &N, &M);

    Start = 0;
    End = N - 1;

    G.resize(N);

    for (int I = 0; I < M; I++) {
        int U, V, C;
        scanf("%d%d%d", &U, &V, &C);
        G[U - 1].push_back(Edge(V - 1, C, 0, I + 1));
        G[V - 1].push_back(Edge(U - 1, 0, 0, 0));
    }
 
    // Searching for max flow
    int MaxFlow = 0;
    while (true) {
        if (!bfs()) break;
        Parent.assign(N, 0);
        while (int FlowCnt = dfs(Start, Inf)) {
            MaxFlow += FlowCnt;
        }
    }

    std::cout << MaxFlow << std::endl;
 
    return 0;
}
