#include <iostream>
#include <cstdio>
#include <vector>

std::vector<std::vector<int>> G;
std::vector<bool> Visited;
std::vector<int> Px;
std::vector<int> Py;

bool dfs(int X) {
    if (Visited[X]) {
        return false;
    }

    Visited[X] = true;

    for (int Y : G[X]) {
        if (Py[Y] == -1) {
            Py[Y] = X;
            Px[X] = Y;
            return true;
        } else if (dfs(Py[Y])) {
            Py[Y] = X;
            Px[X] = Y;
            return true;
        }
    }

    return false;
}

int main() {
    freopen("matching.in",  "r", stdin);
    freopen("matching.out", "w", stdout);

    int N, M, K;
    scanf("%d%d%d", &N, &M, &K);

    G.resize(N);
    Px.assign(N, -1);
    Py.assign(M, -1);

    for (int I = 0; I < K; I++) {
        int U, V;
        scanf("%d%d", &U, &V);
        G[U - 1].push_back(V - 1);
    }

    bool IsPath = true;
    while (IsPath) {
        IsPath = false;
        Visited.assign(N, false);
        for (int X = 0; X < N; X++) {
            if (Px[X] == -1) {
                if (dfs(X)) {
                    IsPath = true;
                }
            }
        }
    }

    int Count = 0;
    for (int X = 0; X < N; X++) {
        for (int Y : G[X]) {
            if (Px[X] == Y) {
                Count++;
            }
        }
    }
    std::cout << Count << std::endl;

    return 0;
}
