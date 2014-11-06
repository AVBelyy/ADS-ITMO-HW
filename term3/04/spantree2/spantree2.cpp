#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdint>

struct DSU_t {
    int Rank;
};

std::vector<DSU_t> DSU;
std::vector<int> Parent;

int Get(int X) {
    if (Parent[X] == X) {
        return X;
    } else {
        return Parent[X] = Get(Parent[X]);
    }
}

void Union(int Xnode, int Ynode) {
    int X = Get(Xnode), Y = Get(Ynode);
    if (X != Y) {
        if (DSU[X].Rank == DSU[Y].Rank) {
            DSU[X].Rank++;
        }
        if (DSU[X].Rank < DSU[Y].Rank) {
            Parent[X] = Y;
        } else {
            Parent[Y] = X;
        }
    }
}

int main() {
    int N, M;

    freopen("spantree2.in",  "r", stdin);
    freopen("spantree2.out", "w", stdout);

    scanf("%d%d", &N, &M);

    DSU.resize(N);
    Parent.resize(N, -1);

    std::vector<std::pair<int, std::pair<int, int>>> Edges(N);

    for (int I = 0; I < N; I++) {
        DSU[I].Rank = 0;
        Parent[I] = I;
    }
    
    for (int I = 0; I < M; I++) {
        int U, V, W;
        scanf("%d%d%d", &U, &V, &W);
        Edges.push_back({W, {U - 1, V - 1}});
    }

    std::sort(Edges.begin(), Edges.end());

    uint64_t Answer = 0;
    for (auto P : Edges) {
        int U = P.second.first, V = P.second.second;
        int W = P.first;
        if (Get(U) != Get(V)) {
            Union(U, V);
            Answer += W;
        }
    }

    std::cout << Answer << std::endl;

    return 0;
}
