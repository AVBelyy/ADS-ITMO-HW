#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
 
const int Inf = 1e9 + 2007;
 
int main() {
    freopen("maxflow.in",  "r", stdin);
    freopen("maxflow.out", "w", stdout);
 
    int N, M;
 
    scanf("%d%d", &N, &M);
 
    int Cost[N][N];
    int Flow[N][N];
 
    for (int I = 0; I < N; I++) {
        for (int J = 0; J < N; J++) {
            Cost[I][J] = 0;
            Flow[I][J] = 0;
        }
    }
 
    for (int I = 0; I < M; I++) {
        int U, V, C;
        scanf("%d%d%d", &U, &V, &C);
        Cost[U - 1][V - 1] = C;
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
                if (From[V] == -1 && Cost[Cur][V] - Flow[Cur][V] > 0) {
                    Q[T++] = V;
                    From[V] = Cur;
                }
            }
        }
 
        if (From[End] == -1) {
            break;
        }
 
        int Cf = Inf;
 
        for (int Cur = N - 1; Cur != 0; ) {
            int Prev = From[Cur];
            Cf = std::min(Cf, Cost[Prev][Cur] - Flow[Prev][Cur]);
            Cur = Prev;
        }
 
        for (int Cur = N - 1; Cur != 0; ) {
            int Prev = From[Cur];
            Flow[Prev][Cur] += Cf;
            Flow[Cur][Prev] -= Cf;
            Cur = Prev;
        }
    }
 
    int MaxFlow = 0;
    for (int I = 0; I < N; I++) {
        if (Cost[Start][I] != 0) {
            MaxFlow += Flow[Start][I];
        }
    }
 
    std::cout << MaxFlow << std::endl;
 
    return 0;
}
