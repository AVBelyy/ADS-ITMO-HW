#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdint>
#include <limits>

const int PlusInf = 1000002007;
const int MinusInf = -1000002007;

struct DSU_t {
    int Rank;
    int Parent;
    int Size;

    DSU_t() : Rank(0), Parent(-1), Size(1) {}
    DSU_t(int Rank, int Parent, int Size) : Rank(Rank), Parent(Parent), Size(Size) {}
};

std::vector<DSU_t> DSU;

int Get(int X) {
    if (DSU[X].Parent == X) {
        return X;
    } else {
        return DSU[X].Parent = Get(DSU[X].Parent);
    }
}

void Union(int Xnode, int Ynode) {
    int X = Get(Xnode), Y = Get(Ynode);
    if (X != Y) {
        if (DSU[X].Rank == DSU[Y].Rank) {
            DSU[X].Rank++;
        }
        if (DSU[X].Rank < DSU[Y].Rank) {
            DSU[X].Parent = Y;
            DSU[Y].Size += DSU[X].Size;
        } else {
            DSU[Y].Parent = X;
            DSU[X].Size += DSU[Y].Size;
        }
    }
}

int main() {
    int N, M;

    freopen("mindiff.in",  "r", stdin);
    freopen("mindiff.out", "w", stdout);

    scanf("%d%d", &N, &M);

    DSU.resize(N);

    std::vector<std::pair<int, std::pair<int, int>>> Edges(N);

    for (int I = 0; I < M; I++) {
        int U, V, W;
        scanf("%d%d%d", &U, &V, &W);
        Edges.push_back({W, {U - 1, V - 1}});
    }

    std::sort(Edges.begin(), Edges.end());

    int64_t MinDiff = (int64_t)PlusInf - MinusInf;
    for (auto I = Edges.begin(); I != Edges.end(); I++) {
        int Min = PlusInf;
        int Max = MinusInf;
        for (int V = 0; V < N; V++) {
            DSU[V] = {0, V, 1};
        }
        for (auto J = I; J != Edges.end(); J++) {
            int U = J->second.first, V = J->second.second;
            int W = J->first;
            if (Get(U) != Get(V)) {
                Union(U, V);
                Min = std::min(Min, W);
                Max = std::max(Max, W);
            }
        }
        // Are all edges connected?
        bool IsConnected = true;
        for (int V = 0; V < N; V++) {
            if (DSU[Get(V)].Size != N) {
                IsConnected = false;
                break;
            }
        }
        if (IsConnected) {
            MinDiff = std::min(MinDiff, (int64_t)Max - Min);
        }
    }

    if (abs(MinDiff) >= (int64_t)PlusInf - MinusInf) {
        std::cout << "NO" << std::endl;
    } else {
        std::cout << "YES" << std::endl;
        std::cout << MinDiff << std::endl;
    }

    return 0;
}
