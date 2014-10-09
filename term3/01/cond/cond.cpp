#include <cstdio>
#include <vector>
#include <stack>

int Index = 0;
int ComponentsNum = 0;

struct Vertex {
    int Number;
    int Index;
    int LowLink;
    int Component;
};

std::stack<int> CurStrongComponent;
std::vector<Vertex> Vertices;
std::vector<std::vector<int>> G;
std::vector<bool> UsedVertices;

void StrongConnect(Vertex & V) {
    V.Index = Index;
    V.LowLink = Index;
    Index++;
    CurStrongComponent.push(V.Number);
    UsedVertices[V.Number] = true;

    for (int I: G[V.Number]) {
        Vertex & U = Vertices[I];

        if (U.Index == -1) {
            StrongConnect(U);
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

int main() {
    int N, M;
    freopen("cond.in",  "r", stdin);
    freopen("cond.out", "w", stdout);

    scanf("%d%d", &N, &M);

    G.resize(N);
    Vertices.resize(N);
    UsedVertices.resize(N);

    for (int I = 0; I < N; I++) {
        Vertices[I].Index = -1;
        Vertices[I].Number = I;
    }

    for (int I = 0; I < M; I++) {
        int U, V;
        scanf("%d%d", &U, &V);
        G[U - 1].push_back(V - 1);
    }

    for (Vertex & V: Vertices) {
        if (V.Index == -1) {
            StrongConnect(V);
        }
    }

    printf("%d\n", ComponentsNum);
    for (Vertex & V: Vertices) {
        printf("%d ", V.Component + ComponentsNum);
    }
    printf("\n");

    return 0;
}
