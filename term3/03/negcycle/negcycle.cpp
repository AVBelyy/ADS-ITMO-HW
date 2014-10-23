#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <limits>
  
const int Inf = std::numeric_limits<int>::max() / 2;
  
struct Edge {
    int U, V, W;
};
  
int main() {
    int N, M, S;
  
    freopen("negcycle.in",  "r", stdin);
    freopen("negcycle.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
  
    std::cin >> N;
  
    std::vector<Edge> Edges;
    std::vector<int> NegCycle;
    std::vector<int> Dist(N, Inf);
    std::vector<int> Parent(N, -1);
  
    for (int I = 0; I < N; I++) {
        for (int J = 0; J < N; J++) {
            int W;
            std::cin >> W;
            if (W != 1e9) {
                Edges.push_back({I, J, W});
            }
        }
    }
  
    Dist[S] = 0;
  
    int Bad;
    for (int I = 0; I < N; I++) {
        Bad = -1;
        for (Edge E : Edges) {
            if (Dist[E.V] > Dist[E.U] + E.W) {
                Dist[E.V] = Dist[E.U] + E.W;
                Parent[E.V] = E.U;
                Bad = E.V;
            }
        }
    }
 
    if (Bad == -1) {
        std::cout << "NO" << std::endl;
    } else {
        int V = Bad;
        for (int I = 0; I < N; I++) {
            V = Parent[V];
        }
        for (int U = V; ; U = Parent[U]) {
            NegCycle.push_back(U);
            if (U == V && NegCycle.size() > 1) break;
        }
        std::reverse(NegCycle.begin(), NegCycle.end());
         
        std::cout << "YES" << std::endl;
        std::cout << NegCycle.size() << std::endl;
        for (int V : NegCycle) {
            std::cout << V + 1 << ' ';
        }
        std::cout << std::endl;
    }
  
    return 0;
}
