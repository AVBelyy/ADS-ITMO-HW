#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

// Happy new year, everyone!

struct Edge {
    int To;
    int W;
};
 
int N;
std::vector<std::vector<Edge>> G;

std::vector<bool> Visited;
std::vector<int> Px;
std::vector<int> Py;

bool dfs(int X, int W) {
    if (Visited[X]) {
        return false;
    }

    Visited[X] = true;

    for (Edge & E : G[X]) {
        int Y = E.To;
        if (E.W >= W) {
            if (Py[Y] == -1) {
                Py[Y] = X;
                Px[X] = Y;
                return true;
            } else if (dfs(Py[Y], W)) {
                Py[Y] = X;
                Px[X] = Y;
                return true;
            }
        }
    }

    return false;
}

bool canWeBuildCompleteMatchingOutOfEdgesWithCertainWeight(int W) {
    Px.assign(N, -1);
    Py.assign(N, -1);

    bool IsPath = true;
    while (IsPath) {
        IsPath = false;
        Visited.assign(N, false);
        for (int X = 0; X < N; X++) {
            if (Px[X] == -1) {
                if (dfs(X, W)) {
                    IsPath = true;
                }
            }
        }
    }

    int Count = 0;
    for (int X = 0; X < N; X++) {
        for (Edge & E : G[X]) {
            int Y = E.To;
            if (Px[X] == Y) {
                Count++;
                break;
            }
        }
    }

    return Count == N;
}
 
int main() {
    freopen("minimax.in",  "r", stdin);
    freopen("minimax.out", "w", stdout);
 
    std::cin >> N;

    G.resize(N);
    std::vector<int> Ws(N * N);
 
    for (int U = 0; U < N; U++) {
        for (int V = 0; V < N; V++) {
            int W;
            std::cin >> W;
            Ws[U * N + V] = W;
            G[U].push_back({V, W});
        }
    }
    std::sort(Ws.begin(), Ws.end());

    int L = -1, R = N * N;
    while (R - L > 1) {
        int M = (L + R) / 2;
        if (canWeBuildCompleteMatchingOutOfEdgesWithCertainWeight(Ws[M])) {
            L = M;
        } else {
            R = M;
        }
    }

    std::cout << Ws[L] << std::endl;
 
    return 0;
}
