#include <cstdio>
#include <vector>

int N, M, Components = 0;

std::vector<std::vector<int>> G;
std::vector<int> VertexComponent;

void dfs(int V, int C) {
    if (VertexComponent[V]) return;

    VertexComponent[V] = C;

    for (int U: G[V]) {
        dfs(U, C);
    }
}

int main() {
    freopen("components.in",  "r", stdin);
    freopen("components.out", "w", stdout);
    
    scanf("%d", &N);
    scanf("%d", &M);

    G.resize(N);
    VertexComponent.resize(N);

    for (int I = 0; I < M; I++) {
        int U, V;
        scanf("%d%d", &U, &V);
        G[U - 1].push_back(V - 1);
        G[V - 1].push_back(U - 1);
    }

    for (int I = 0; I < N; I++) {
        if (!VertexComponent[I]) {
            dfs(I, ++Components);
        }
    }

    printf("%d\n", Components);
    for (int I = 0; I < N; I++) {
        printf("%d ", VertexComponent[I]);
    }
    putchar('\n');

    return 0;
}
