#include <iostream>
#include <cstdio>
#include <vector>

std::vector<std::vector<int> > G;
std::vector<bool> Visited;
std::vector<int> Px;
std::vector<int> Py;

bool dfs(int X) {
    if (Visited[X]) {
        return false;
    }

    Visited[X] = true;

    for (std::vector<int>::iterator It = G[X].begin(); It != G[X].end(); ++It) {
        int Y = *It;
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
    freopen("paths.in",  "r", stdin);
    freopen("paths.out", "w", stdout);

    int N, M;
    scanf("%d%d", &N, &M);

    G.resize(N);
    Px.assign(N, -1);
    Py.assign(N, -1);

    for (int I = 0; I < M; I++) {
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
        for (std::vector<int>::iterator It = G[X].begin(); It != G[X].end(); ++It) {
            int Y = *It;
            if (Px[X] == Y) {
                Count++;
                break;
            }
        }
    }
    std::cout << N - Count << std::endl;

    return 0;
}
