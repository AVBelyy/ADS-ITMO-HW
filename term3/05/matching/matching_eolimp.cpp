#include <iostream>
#include <cstdio>
#include <vector>

std::vector< std::vector<int> > G;
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
    int N, M;
    scanf("%d%d", &N, &M);

    G.resize(N);
    Px.assign(N, -1);
    Py.assign(M, -1);

    for (int U = 0; U < N; U++) {
        int V;
        while (true) {
            scanf("%d", &V);
            if (V == 0) {
                break;
            }
            G[U].push_back(V - 1);
        };
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

    std::vector< std::pair<int, int> > Ans;

    int Count = 0;
    for (int X = 0; X < N; X++) {
        for (int Y : G[X]) {
            if (Px[X] == Y) {
                Count++;
                Ans.push_back(std::make_pair(X, Y));
            }
        }
    }
    
    std::cout << Count << std::endl;
    for (int I = 0; I < Count; I++) {
        std::cout << Ans[I].first + 1 << ' ' << Ans[I].second + 1 << std::endl;
    }

    return 0;
}
