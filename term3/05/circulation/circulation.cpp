#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

struct Edge {
    int U;
    int V;
    int C;

    Edge() : U(0), V(0), C(0) {}
    Edge(int U, int V, int C) : U(U), V(V), C(C) {}
};

const int Inf = 1e9;

int main() {
    freopen("circulation.in",  "r", stdin);
    freopen("circulation.out", "w", stdout);

    int Nold, Mold;

    scanf("%d%d", &Nold, &Mold);

    std::vector<Edge> Edges(Mold * 3);
    std::vector<Edge> EdgeMapping(Mold);

    for (int I = 0; I < Mold; I++) {
        int U, V, L, C;
        scanf("%d%d%d%d", &U, &V, &L, &C);
        Edges[I * 3] = Edge(0, V, L);
        Edges[I * 3 + 1] = Edge(U, V, C - L);
        Edges[I * 3 + 2] = Edge(U, Nold + 1, L);
        EdgeMapping[I] = Edge(U, V, L);
    }

    int N = Nold + 2, M = Mold * 3;
    
    int Capacity[N][N];
    int Flow[N][N];

    for (int I = 0; I < N; I++) {
        for (int J = 0; J < N; J++) {
            Capacity[I][J] = 0;
            Flow[I][J] = 0;
        }
    }

    for (int I = 0; I < M; I++) {
        Edge E = Edges[I];
        Capacity[E.U][E.V] += E.C;
    }

    int Start = 0, End = N - 1;

    while (true) {
        std::vector<int> From(N, -1);
        std::vector<int> Q(N);
        int H = 0, T = 0;

        Q[T++] = 0;
        From[Start] = 0;

        while (H < T) {
            int Cur = Q[H++];
            for (int V = 0; V < N; V++) {
                if (From[V] == -1 && Capacity[Cur][V] - Flow[Cur][V] > 0) {
                    Q[T++] = V;
                    From[V] = Cur;
                }
            }
        }

        if (From[End] == -1) {
            break;
        }

        int Cf = Inf;

        for (int Cur = End; Cur != 0; ) {
            int Prev = From[Cur];
            Cf = std::min(Cf, Capacity[Prev][Cur] - Flow[Prev][Cur]);
            Cur = Prev;
        }

        for (int Cur = End; Cur != 0; ) {
            int Prev = From[Cur];
            Flow[Prev][Cur] += Cf;
            Flow[Cur][Prev] -= Cf;
            Cur = Prev;
        }
    }

    int MaxFlow = 0;
    bool CirculationFlag = true;
    for (int I = 0; I < N; I++) {
        if (Capacity[Start][I] != 0) {
            if (Flow[Start][I] < Capacity[Start][I]) {
                CirculationFlag = false;
                break;
            } else {
                MaxFlow += Flow[Start][I];
            }
        }
    }

    if (CirculationFlag) {
        std::cout << "YES" << std::endl;
        for (std::vector<Edge>::iterator It = EdgeMapping.begin(); It != EdgeMapping.end(); ++It) {
            Edge E = *It;
            std::cout << Flow[E.U][E.V] + E.C << std::endl;
        }
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
