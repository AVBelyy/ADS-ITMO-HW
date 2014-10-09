#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>

int N, M;

std::vector<std::vector<int>> G;
std::unordered_map<long long, int> Edges;
std::vector<bool> Used;
std::vector<int> Enter;
std::vector<int> Ret;

std::vector<int> Bridges;

inline uint64_t hasher(int U, int V) {
    return ((uint64_t)U << 32) + V;
}

int Time = 0;

void dfs(int V, int Prev = -1) {
    if (Used[V]) return;

    Used[V] = true;
    Enter[V] = Ret[V] = Time;
    Time++;

    for (int U: G[V]) {
        if (U == Prev) continue;

        if (Used[U]) {
            if (Ret[V] > Enter[U]) {
                Ret[V] = Enter[U];
            }
        } else {
            dfs(U, V);
            if (Ret[V] > Ret[U]) {
                Ret[V] = Ret[U];
            }
            if (Ret[U] > Enter[V]) {
                Bridges.push_back(Edges[hasher(V, U)]);
            }
        }
    }
}

int main() {
    freopen("bridges.in",  "r", stdin);
    freopen("bridges.out", "w", stdout);

    scanf("%d%d", &N, &M);

    G.resize(N);
    Used.resize(N);
    Enter.resize(N);
    Ret.resize(N);

    for (int I = 0; I < M; I++) {
        int U, V;

        scanf("%d%d", &U, &V);
        G[U - 1].push_back(V - 1);
        G[V - 1].push_back(U - 1);
        Edges[hasher(U - 1, V - 1)] = I + 1;
       Edges[hasher(V - 1, U - 1)] = I + 1;
    }

    for (int I = 0; I < N; I++) {
        Time = 0;
        dfs(I);
    }

    std::sort(Bridges.begin(), Bridges.end());

    int BridgeCount = Bridges.size();
    printf("%d\n", BridgeCount);
    for (int I = 0; I < BridgeCount; I++) {
        printf("%d\n", Bridges[I]);
    }

    return 0;
}
