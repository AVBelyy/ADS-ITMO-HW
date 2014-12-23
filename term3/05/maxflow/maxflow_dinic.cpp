#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

const int64_t Inf = 1e16 + 2007;

int N, M;
int Start, End;
std::vector<std::vector<int> > G;
std::vector<std::vector<int64_t> > C;
std::vector<std::vector<int64_t> > F;
std::vector<int> D;
std::vector<int> Ptr;

bool bfs() {
    int QH = 0, QT = 0;
    std::vector<int> Q(N);
    D.assign(N, -1);
    Q[QT++] = Start;
    D[Start] = 0;

    while (QH < QT) {
        int V = Q[QH++];
        for (int To = 0; To < N; To++) {
            if (D[To] == -1 && F[V][To] < C[V][To]) {
                Q[QT++] = To;
                D[To] = D[V] + 1;
            }
        }
    }

    return D[End] != -1;
}

int64_t dfs(int V, int64_t Flow) {
    if (Flow == 0) return 0;
    if (V == End) return Flow;

    for (int & To = Ptr[V]; To < N; To++) {
        if (D[To] != D[V] + 1) continue;
        int64_t Pushed = dfs(To, std::min(Flow, C[V][To] - F[V][To]));
        if (Pushed != 0) {
            F[V][To] += Pushed;
            F[To][V] -= Pushed;
            return Pushed;
        }
    }

    return 0;
}

int main() {
    freopen("maxflow.in",  "r", stdin);
    freopen("maxflow.out", "w", stdout);
 
    std::cin >> N >> M;

    Start = 0;
    End = N - 1;

    Ptr.resize(N);
    G.assign(N, std::vector<int>(N));
    C.assign(N, std::vector<int64_t>(N));
    F.assign(N, std::vector<int64_t>(N));
 
    for (int I = 0; I < M; I++) {
        int U, V, Cap;
        std::cin >> U >> V >> Cap;
        C[U - 1][V - 1] += Cap;
        G[U - 1][V - 1] = I + 1;
    }

    int64_t MaxFlow = 0;
    while (true) {
        if (!bfs()) break;
        Ptr.assign(N, 0);
        while (int64_t Pushed = dfs(Start, Inf)) {
            MaxFlow += Pushed;
        }
    }

    std::cout << MaxFlow << std::endl;
    
    return 0;
}
