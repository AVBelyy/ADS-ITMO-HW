#include <cstdint>
#include <cstdio>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> G;
std::vector<std::vector<int>> GEdge;
std::vector<int> Components;
std::vector<int> Enter;
std::vector<int> Ret;
std::vector<bool> Visited;

int MaxColor = 0;
int Time;

void dfs1(int U, int Prev = -1) {
    if (Visited[U]) return;

    Visited[U] = true;
    Enter[U] = Ret[U] = Time++;

    for (int V: G[U]) {
        if (U == Prev) continue;

        if (Visited[V]) {
            if (Ret[U] > Enter[V]) {
                Ret[U] = Enter[V];
            }
        } else {
            dfs1(V, U);
            if (Ret[U] > Ret[V]) {
                Ret[U] = Ret[V];
            }
        }
    }
}

void dfs2(int V, int Color = -1, int Prev = -1) {
    if (Visited[V]) return;

    Visited[V] = true;

    for (int I = 0; I < G[V].size(); I++) {
        int U = G[V][I];
        if (U == Prev) continue;

        int EdgeId = GEdge[V][I];
        
        if (Visited[U]) {
            if (Enter[U] <= Enter[V]) {
                Components[EdgeId] = Color;
            }
        } else { 
            if (Ret[U] >= Enter[V]) {
                int NewColor = ++MaxColor;
                Components[EdgeId] = NewColor;

                dfs2(U, NewColor, V);
            } else {
                Components[EdgeId] = Color;

                dfs2(U, Color, V);
            }
        }
    }
}

int main() {
    int N, M;

    freopen("biconv.in",  "r", stdin);
    freopen("biconv.out", "w", stdout);

    scanf("%d%d", &N, &M);

    G.resize(N);
    GEdge.resize(N);
    Enter.resize(N);
    Ret.resize(N);
    Visited.resize(N);
    Components.resize(M);

    for (int I = 0; I < M; I++) {
        int U, V;
        scanf("%d%d", &U, &V);
        G[U - 1].push_back(V - 1);
        G[V - 1].push_back(U - 1);
        GEdge[U - 1].push_back(I);
        GEdge[V - 1].push_back(I);
    }

    // first pass
    for (int I = 0; I < N; I++) {
        Time = 0;
        dfs1(I);
    }

    for (int I = 0; I < N; I++) {
        Visited[I] = false;
    }

    // second pass
    for (int I = 0; I < N; I++) {
        dfs2(I);
    }
    
    int ComponentCount = MaxColor;
    
    printf("%d\n", ComponentCount);
    for (int Component: Components) {
        printf("%d ", Component);
    }
    putchar('\n');

    return 0;
}
