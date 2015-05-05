#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stdint.h>

struct DSU_t {
    int Rank;
};

struct Edge {
    int64_t W;
    int Id;
    int U;
    int V;

    Edge() : W(0), Id(0), U(0), V(0) {
    }

    Edge(int64_t W, int Id, int U, int V) : W(W), Id(Id), U(U), V(V) {
    }
    
    static bool RevCompare(Edge A, Edge B) {
        return B.W < A.W;
    }
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
    int64_t S;

    freopen("destroy.in",  "r", stdin);
    freopen("destroy.out", "w", stdout);

    std::cin >> N >> M >> S;

    DSU.resize(N);
    Parent.resize(N, -1);

    std::vector<Edge> Edges;

    for (int I = 0; I < N; I++) {
        DSU[I].Rank = 0;
        Parent[I] = I;
    }

    for (int I = 0; I < M; I++) {
        int U, V;
        int64_t W;
        std::cin >> U >> V >> W;
        Edges.push_back(Edge(W, I, U - 1, V - 1));
    }

    std::sort(Edges.begin(), Edges.end(), Edge::RevCompare);

    std::vector<Edge> Fat;

    // create maximum spanning tree
    for (std::vector<Edge>::iterator P = Edges.begin(); P != Edges.end(); P++) {
        if (Get(P->U) != Get(P->V)) {
            Union(P->U, P->V);
        } else {
            Fat.push_back(*P);
        }
    }
    std::reverse(Fat.begin(), Fat.end());
    std::vector<int> Ans;
    // put other edges on tree
    for (std::vector<Edge>::iterator P = Fat.begin(); P != Fat.end(); P++) {
        if (P->W > S) {
            break;
        } else {
            S -= P->W;
            Ans.push_back(P->Id);
        }
    }

    std::sort(Ans.begin(), Ans.end());

    std::cout << Ans.size() << std::endl;
    for (int I = 0; I < Ans.size(); I++) {
        std::cout << Ans[I] + 1 << ' ';
    }
    std::cout << std::endl;

    return 0;
}
