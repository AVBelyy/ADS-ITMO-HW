#include <cstdio>
#include <vector>
#include <queue>
#include <utility>

int N, M;

std::vector<std::vector<int>> G;
std::vector<bool> Visited;
std::vector<int> Coloring;

bool bfs(int V) {
    std::queue<std::pair<int, bool>> Q;

    Q.emplace(V, true);

    while (!Q.empty()) {
        auto P = Q.front();
        int U = P.first;
        bool C = P.second;
        Q.pop();

        if (Visited[U]) {
            if (C != Coloring[U]) {
                return false;
            }
        } else {
            Visited[U] = true;
            Coloring[U] = C;

            for (int UU: G[U]) {
                Q.emplace(UU, !C);
            }
        }
    }

    return true;
}

int main() {
    freopen("bipartite.in",  "r", stdin);
    freopen("bipartite.out", "w", stdout);

    scanf("%d%d", &N, &M);

    G.resize(N);
    Visited.resize(N);
    Coloring.resize(N);

    for (int I = 0; I < M; I++) {
        int U, V;
        scanf("%d%d", &U, &V);
        G[U - 1].push_back(V - 1);
        G[V - 1].push_back(U - 1);
    }

    bool IsBipartite = true;
    for (int I = 0; I < N; I++) {
        if (!Visited[I]) {
            IsBipartite &= bfs(I);
        }
    }

    printf(IsBipartite ? "YES\n" : "NO\n");

    return 0;
}
