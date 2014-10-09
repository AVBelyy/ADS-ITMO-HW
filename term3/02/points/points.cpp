#include <cstdio>
#include <vector>
#include <algorithm>

int N, M;
int Time;

std::vector<std::vector<int>> G;
std::vector<int> Enter;
std::vector<int> Ret;
std::vector<bool> Visited;
std::vector<int> Points;

void dfs(int U, int Prev = -1) {
    if (Visited[U]) return;

    Visited[U] = true;
    Enter[U] = Ret[U] = Time++;
    int Count = 0;
    bool IsCutPoint = false;

    for (int V: G[U]) {
        if (U == Prev) continue;

        if (Visited[V]) {
            if (Ret[U] > Enter[V]) {
                Ret[U] = Enter[V];
            }
        } else {
            Count++;
            dfs(V, U);
            if (Ret[U] > Ret[V]) {
                Ret[U] = Ret[V];
            }
            if (Ret[V] >= Enter[U] && Prev != -1) {
                IsCutPoint = true;
            }
        }
    }

    if (Prev == -1 && Count > 1) {
        IsCutPoint = true;
    }

    if (IsCutPoint) {
        Points.push_back(U + 1);
    }
}

int main() {
    freopen("points.in",  "r", stdin);
    freopen("points.out", "w", stdout);

    scanf("%d%d", &N, &M);

    G.resize(N);
    Enter.resize(N);
    Ret.resize(N);
    Visited.resize(N);

    for (int I = 0; I < M; I++) {
        int U, V;
        scanf("%d%d", &U, &V);
        G[U - 1].push_back(V - 1);
        G[V - 1].push_back(U - 1);
    }

    for (int I = 0; I < N; I++) {
        Time = 0;
        dfs(I);
    }

    std::sort(Points.begin(), Points.end());

    int PointCount = Points.size();

    printf("%d\n", PointCount);
    for (int Point: Points) {
        printf("%d\n", Point);
    }

    return 0;
}
