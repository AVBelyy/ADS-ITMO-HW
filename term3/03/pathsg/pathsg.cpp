#include <algorithm>
#include <iostream>
#include <cstdio>
#include <limits>

const int Inf = std::numeric_limits<int>::max() / 2;

int main() {
    int N, M;

    freopen("pathsg.in",  "r", stdin);
    freopen("pathsg.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);

    std::cin >> N >> M;

    int G[N][N];

    for (int I = 0; I < N; I++) {
        for (int J = 0; J < N; J++) {
            G[I][J] = Inf;
        }
        G[I][I] = 0;
    }

    for (int I = 0; I < M; I++) {
        int U, V, W;
        std::cin >> U >> V >> W;
        U--; V--;
        G[U][V] = W;
    }

    for (int K = 0; K < N; K++) {
        for (int I = 0; I < N; I++) {
            for (int J = 0; J < N; J++) {
                G[I][J] = std::min(G[I][J], G[I][K] + G[K][J]);
            }
        }
    }

    for (int I = 0; I < N; I++) {
        for (int J = 0; J < N; J++) {
            std::cout << G[I][J] << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
