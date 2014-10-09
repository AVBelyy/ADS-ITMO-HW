#include <algorithm>
#include <iostream>
#include <utility>
#include <cstdio>
#include <vector>

const int Inf = 1e9;
int N, M, S, T;
int Depth = 0;

std::vector<std::vector<std::pair<int, int>>> G;
std::vector<int> Ordering;
std::vector<int> Color;

bool dfs(int U) {
    if (Color[U] == 1) return true;
    if (Color[U] == 2) return false;

    Color[U] = 1;

    for (auto P: G[U]) {
        int V = P.first;
        if (dfs(V)) {
            return true;
        }
    }

    Ordering.push_back(U);
    Color[U] = 2;
    return false;
}

void topSort() {
    dfs(S);
}

int main() {
    freopen("shortpath.in",  "r", stdin);
    freopen("shortpath.out", "w", stdout);

    scanf("%d%d%d%d", &N, &M, &S, &T);
    S--; T--;

    std::vector<int> Dist(N, Inf);

    G.resize(N);
    Color.resize(N);

    for (int I = 0; I < M; I++) {
        int U, V, W;
        scanf("%d%d%d", &U, &V, &W);
        G[U - 1].push_back({V - 1, W});
    }

    Dist[S] = 0;

    topSort();
    std::reverse(Ordering.begin(), Ordering.end());

    for (int U: Ordering) {
        for (auto P: G[U]) {
            int V = P.first;
            int W = P.second;
            if (Dist[V] > Dist[U] + W) {
                Dist[V] = Dist[U] + W;
            }
        }
    }

    if (Dist[T] == Inf) {
        std::cout << "Unreachable" << std::endl;
    } else {
        std::cout << Dist[T] << std::endl;
    }
    
    return 0;
}
