#include <stack>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <limits>
#include <cstdint>

const int PlusInf = 1e9 + 2007;

int Index;
int ComponentsNum;

struct Vertex {
    int Number;
    int Index;
    int LowLink;
    int Component;
};

struct Edge_t {
    int To;
    int W;

    Edge_t(int To, int W) : To(To), W(W) {}
};

std::stack<int> CurStrongComponent;
std::vector<Vertex> Vertices;
std::vector<int> MinEdge;
std::vector<std::vector<Edge_t>> G;
std::vector<std::vector<Edge_t>> OldG;
std::vector<std::vector<Edge_t>> NewG;
std::vector<std::vector<Edge_t>> ZeroG;
std::vector<bool> UsedVertices;

std::vector<bool> Used;

void dfs(int V) {
    Used[V] = true;

    for (Edge_t E : G[V]) {
        if (!Used[E.To]) {
            dfs(E.To);
        }
    }
}

bool reachable(int V) {
    Used = std::vector<bool>(G.size());
    dfs(V);

    for (bool Flag : Used) {
        if (!Flag) {
            return false;
        }
    }

    return true;
}

void strongConnect(Vertex & V) {
    V.Index = Index;
   V.LowLink = Index;
    Index++;
    CurStrongComponent.push(V.Number);
    UsedVertices[V.Number] = true;

    for (Edge_t E : G[V.Number]) {
        int I = E.To;
        Vertex & U = Vertices[I];

        if (U.Index == -1) {
            strongConnect(U);
            if (V.LowLink > U.LowLink) {
                V.LowLink = U.LowLink;
            }
        } else if (UsedVertices[I]) {
            if (V.LowLink > U.Index) {
                V.LowLink = U.Index;
            }
        }
    }

    if (V.LowLink == V.Index) {
        int U;
        do {
            U = CurStrongComponent.top();
            CurStrongComponent.pop();
            UsedVertices[U] = false;
            Vertices[U].Component = -ComponentsNum;
        } while(U != V.Number);
        ComponentsNum++;
    }
}

void condensate() {
    UsedVertices = std::vector<bool>(G.size());
    Vertices = std::vector<Vertex>(G.size());
    Index = 0;
    ComponentsNum = 0;

    for (int I = 0; I < G.size(); I++) {
        Vertices[I].Index = -1;
        Vertices[I].Number = I;
    }

    for (Vertex & V : Vertices) {
        if (V.Index == -1) {
            strongConnect(V);
        }
    }
}

int64_t findMST(int Root) {
    int64_t Result = 0;
    MinEdge.assign(G.size(), PlusInf);
    
    for (int I = 0; I < G.size(); I++) {
        for (Edge_t E : G[I]) {
            MinEdge[E.To] = std::min(MinEdge[E.To], E.W);
        }
    }
    
    for (int I = 0; I < G.size(); I++) {
        for (Edge_t & E : G[I]) {
            E.W -= MinEdge[E.To];
        }
    }
    
    for (int I = 0; I < G.size(); I++) {
        if (I != Root) {
            Result += MinEdge[I];
        }
    }

    ZeroG.clear();
    ZeroG.resize(G.size());

    for (int I = 0; I < G.size(); I++) {
        for (Edge_t E : G[I]) {
            if (E.W == 0) {
                ZeroG[I].push_back(E);
            }
        }
    }

    OldG = G;
    G = ZeroG;

    if (reachable(Root)) {
        return Result;
    }

    condensate();

    NewG.clear();
    NewG.resize(ComponentsNum);

    for (int I = 0; I < OldG.size(); I++) {
        for (Edge_t E : OldG[I]) {
            int CU = Vertices[I].Component + ComponentsNum - 1;
            int CV = Vertices[E.To].Component + ComponentsNum - 1;
            if (CU != CV) {
                NewG[CU].push_back({CV, E.W});
            }
        }
    }

    G = NewG;

    Result += findMST(Vertices[Root].Component + ComponentsNum - 1);
    
    return Result;
}

int main() {
    int N, M;

    freopen("chinese.in",  "r", stdin);
    freopen("chinese.out", "w", stdout);

    scanf("%d%d", &N, &M);

    G.resize(N);

    for (int I = 0; I < M; I++) {
        int U, V, W;
        scanf("%d%d%d", &U, &V, &W);
        if (U != V) {
            G[U - 1].push_back({V - 1, W});
        }
    }

    if (reachable(0)) {
        int64_t Result = findMST(0);
        std::cout << "YES" << std::endl;
        std::cout << Result << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
}
