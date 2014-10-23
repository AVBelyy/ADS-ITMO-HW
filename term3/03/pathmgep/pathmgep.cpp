#include <utility>
#include <cstdint>
#include <cstdio>
#include <vector>
#include <limits>
#include <queue>

const int Inf = std::numeric_limits<int>::max();

int main() {
    int N, S, F;

    freopen("pathmgep.in",  "r", stdin);
    freopen("pathmgep.out", "w", stdout);

    scanf("%d%d%d", &N, &S, &F);
    S--; F--;

    std::vector<std::vector<std::pair<int, int>>> G(N);
    std::vector<int> Dist(N, Inf);
    std::priority_queue<std::pair<int, int>> Q;

    for (int I = 0; I < N; I++) {
        for (int J = 0; J < N; J++) {
            int W;
            scanf("%d", &W);
            if (W != -1) {
                G[I].push_back({J, W});
            }
        }
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

    printf("%d\n", Dist[F] == Inf ? -1 : Dist[F]);

    return 0;
}
