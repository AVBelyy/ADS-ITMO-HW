#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <limits>

const int64_t Inf = std::numeric_limits<int64_t>::max() / 2 - 1;
  
struct Edge {
    int U, V;
    int64_t W;
};

std::vector<bool> Reachable;
std::vector<std::vector<int>> G;

void dfs(int U) {
    if (!Reachable[U]) {
        Reachable[U] = true;

        for (int V : G[U]) {
            if (!Reachable[V]) {
                dfs(V);
            }
        }
    }
}

int main() {
    int N, M, S;
  
    freopen("path.in",  "r", stdin);
    freopen("path.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
  
    std::cin >> N >> M >> S;
    S--;
    G.resize(N);
    Reachable.resize(N);
  
    std::vector<Edge> Edges;
    std::vector<bool> ThroughNegCycle(N);
    std::vector<int64_t> Dist(N, Inf);
 
    for (int I = 0; I < M; I++) {
        int U, V;
        int64_t W;
        std::cin >> U >> V >> W;
        G[U - 1].push_back(V - 1);
        Edges.push_back({U - 1, V - 1, W});
    }
 
    // first dfs
    dfs(S);
    auto NonAdjacent = Reachable;
    NonAdjacent.flip();

    Dist[S] = 0;
  
    for (int I = 0; I < N - 1; I++) {
        for (Edge E : Edges) {
            if (Dist[E.V] > Dist[E.U] + E.W && Dist[E.U] < Inf) {
                Dist[E.V] = Dist[E.U] + E.W;
                if(Dist[E.V] < -Inf) {
                    Dist[E.V] = -Inf;
                }
            }
        }
    }
 
    std::fill(Reachable.begin(), Reachable.end(), false);
    for (Edge E : Edges) {
        if (Dist[E.V] > Dist[E.U] + E.W && Dist[E.U] < Inf) {
            Dist[E.V] = Dist[E.U] + E.W;
            if(Dist[E.V] < -Inf) {
                Dist[E.V] = -Inf;
            }
            dfs(E.V);
        }
    }
    ThroughNegCycle = Reachable;

    for (int I = 0; I < N; I++) {
        if (NonAdjacent[I]) {
            std::cout << '*' << std::endl;
        } else if (ThroughNegCycle[I]) {
            std::cout << '-' << std::endl;
        } else {
            std::cout << Dist[I] << std::endl;
        }
    }
 
    return 0;
}
