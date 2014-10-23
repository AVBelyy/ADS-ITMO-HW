#include <iostream>
#include <utility>
#include <cstdint>
#include <cstdio>
#include <vector>
#include <limits>
#include <queue>

const int Inf = std::numeric_limits<int>::max();

int main() {
    int N, M;

    freopen("pathbge1.in",  "r", stdin);
    freopen("pathbge1.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);

    std::cin >> N >> M;

    int S = 0;

    std::vector<std::vector<std::pair<int, int>>> G(N);
    std::vector<int> Dist(N, Inf);
    std::priority_queue<std::pair<int, int>> Q;

    for (int I = 0; I < M; I++) {
        int U, V;
        std::cin >> U >> V;
        U--; V--;
        G[U].push_back({V, 1});
        G[V].push_back({U, 1});
    }

    Dist[S] = 0;
    Q.emplace(-Dist[S], S);

    while (!Q.empty()) {
        auto P = Q.top();
        int D = -P.first;
        int U = P.second;
        Q.pop();

        if (D > Dist[U]) continue;
        
        for (auto PP : G[U]) {
            int V = PP.first;
            int W = PP.second;

            if (Dist[V] > Dist[U] + W) {
                Dist[V] = Dist[U] + W;
                Q.emplace(-Dist[V], V);
            }
        }
    }

    for (int D : Dist) {
        std::cout << D << ' ';
    }
    std::cout << std::endl;

    return 0;
}
