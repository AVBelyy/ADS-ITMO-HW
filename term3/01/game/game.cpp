#include <iostream>
#include <cstdio>
#include <vector>

int main() {
    int N, M, S;
    
    freopen("game.in",  "r", stdin);
    freopen("game.out", "w", stdout);

    scanf("%d%d%d", &N, &M, &S);
    S--;

    std::vector<std::pair<int, bool>> Q;
    std::vector<std::vector<int>> Ginv(N);
    std::vector<bool> IsBottom(N, true);
    std::vector<bool> IsWinning(N, true);
    std::vector<bool> Visited(N);

    for (int I = 0; I < M; I++) {
        int U, V;
        scanf("%d%d", &U, &V);
        Ginv[V - 1].push_back(U - 1);
        IsBottom[U - 1] = false;
    }

    for (int I = 0; I < N; I++) {
        if (IsBottom[I]) {
            Q.emplace_back(I, false);
        }
    }

    int Qfront = 0;
    
    while (Qfront < Q.size()) {
        auto P = Q[Qfront++];
        int U = P.first;
        bool WinFlag = P.second;

        if (!Visited[U]) {
            Visited[U] = true;

            if (IsWinning[U] && WinFlag) {
                IsWinning[U] = false;
            }

            for (int V: Ginv[U]) {
                if (!Visited[V]) {
                    Q.emplace_back(V, !WinFlag);
                }
            }
        }
    }

    if (IsWinning[S]) {
        std::cout << "Second player wins" << std::endl;
    } else {
        std::cout << "First player wins" << std::endl;
    }

    return 0;
}
