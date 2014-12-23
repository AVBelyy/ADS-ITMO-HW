#include <iostream>
#include <cstdio>
#include <vector>
#include <deque>

const int64_t Inf = 1e9 + 2015;

struct Edge {
    int To;
    int Capacity;
    int Cost;
    int Flow;
    size_t BackEdge;
};

int main() {
    int N, M;

    freopen("mincost.in",  "r", stdin);
    freopen("mincost.out", "w", stdout);

    std::cin >> N >> M;
    
    const int S = 0, T = N - 1;
    std::vector<std::vector<Edge>> G(N);

    for (int I = 0; I < M; I++) {
        int U, V, Capacity, Cost;
        std::cin >> U >> V >> Capacity >> Cost;
        U--; V--;
        Edge E1 = {V, Capacity, Cost, 0, G[V].size()};
        Edge E2 = {U, 0, -Cost, 0, G[U].size()};
        G[U].push_back(E1);
        G[V].push_back(E2);
    }

    int Flow = 0;
    int64_t Cost = 0;
    while (true) {
        std::vector<int> Color(N);
        std::vector<int64_t> Dist(N, Inf);
        std::vector<int> ParentV(N);
        std::vector<int> ParentE(N);
        std::deque<int> Q = {S};
        
        Dist[S] = 0;
        
        while (!Q.empty()) {
            int V = Q.front();
            Q.pop_front();
            Color[V] = 2;

            for (int I = 0; I < G[V].size(); I++) {
                Edge & E = G[V][I];
                
                if (E.Flow < E.Capacity && Dist[E.To] > Dist[V] + E.Cost) {
                    Dist[E.To] = Dist[V] + E.Cost;
                    
                    if (Color[E.To] == 0) {
                        Q.push_back(E.To);
                    } else if (Color[E.To] == 2) {
                        Q.push_front(E.To);
                    }
                    
                    Color[E.To] = 1;
                    ParentV[E.To] = V;
                    ParentE[E.To] = I;
                }
            }
        }
    
        if (Dist[T] == Inf) {
            break;
        }
        
        int AddFlow = Inf;

        for (int V = T; V != S; V = ParentV[V]) {
            int PV = ParentV[V];
            int PE = ParentE[V];
            
            AddFlow = std::min(AddFlow, G[PV][PE].Capacity - G[PV][PE].Flow);
        }

        for (int V = T; V != S; V = ParentV[V]) {
            int PV = ParentV[V];
            int PE = ParentE[V];
            int BE = G[PV][PE].BackEdge;

            G[PV][PE].Flow += AddFlow;
            G[V][BE].Flow -= AddFlow;
            Cost += (int64_t) G[PV][PE].Cost * AddFlow;
        }

        Flow += AddFlow;
    }

    std::cout << Cost << std::endl;
    return 0;
}
