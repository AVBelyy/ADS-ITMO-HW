#include <cstdio>
#include <vector>

std::vector<std::vector<int>> G;
std::vector<int> Components;
std::vector<int> Enter;
std::vector<int> Ret;
std::vector<bool> Visited;
int Time, MaxColor = 0;

void dfs(int V, int Prev = -1) {
    if (Visited[V]) return;

    Visited[V] = true;
    Enter[V] = Ret[V] = Time;
    Time++;

    for (int U: G[V]) {
        if (U == Prev) continue;

        if (Visited[U]) {
            if (Ret[V] > Enter[U]) {
                Ret[V] = Enter[U];
            }
        } else {
            dfs(U, V);
            if (Ret[V] > Ret[U]) {
                Ret[V] = Ret[U];
            }
        }
    }
}

void paint(int V, int Color) {
    Components[V] = Color;

    for (int U: G[V]) {
        if (Components[U] == 0) {
            if (Ret[U] == Enter[U]) {
                MaxColor++;
                paint(U, MaxColor);
            } else {
                paint(U, Color);
            }
        }
    }
}

int main() {
    int N, M;

    freopen("bicone.in",  "r", stdin);
    freopen("bicone.out", "w", stdout);

    scanf("%d%d", &N, &M);

    G.resize(N);
    Components.resize(N);
    Enter.resize(N);
    Ret.resize(N);
    Visited.resize(N);

    for (int I = 0; I < M; I++) {
        int U, V;
        scanf("%d%d", &U, &V);
        G[U - 1].push_back(V - 1);
        G[V - 1].push_back(U - 1);
    }

    // first pass
    for (int I = 0; I < N; I++) {
        Time = 0;
        dfs(I);
    }

    // second pass
    for (int I = 0; I < N; I++) {
        if (Components[I] == 0) {
            MaxColor++;
            paint(I, MaxColor);
        }
    }

    printf("%d\n", MaxColor);
    for (int Component: Components) {
        printf("%d ", Component);
    }
    putchar('\n');

    return 0;
}
