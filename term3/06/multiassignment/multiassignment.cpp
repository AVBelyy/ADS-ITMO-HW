#include <iostream>
#include <cstdio>
#include <vector>
#include <deque>
 
const int Inf = 1e9 + 2015;
 
struct Edge {
    int To;
    int Capacity;
    int Cost;
    int Flow;
    size_t BackEdge;
};
 
int N, K;
int S, T;
std::vector<std::vector<Edge>> G;
 
void addEdge(int U, int V, int Capacity, int Cost) {
    Edge E1 = {V, Capacity, Cost, 0, G[V].size()};
    Edge E2 = {U, 0, -Cost, 0, G[U].size()};
     
    G[U].push_back(E1);
    G[V].push_back(E2);
}
 
int minCostFlow() {
    int Flow = 0;
    int Cost = 0;
     
    while (true) {
        std::vector<int> Color(N);
        std::vector<int> Dist(N, Inf);
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
            Cost += G[PV][PE].Cost * AddFlow;
        }
 
        Flow += AddFlow;
    }
 
    return Cost;
}
 
std::vector<int> Matching;
std::vector<bool> Visited;
std::vector<int> Px;
std::vector<int> Py;
 
bool dfs(int X) {
    if (Visited[X]) {
        return false;
    }
 
    Visited[X] = true;
 
    for (Edge & E : G[X + 1]) {
        int Y = E.To - N - 1;
        if (E.Flow > 0) {
            if (Py[Y] == -1) {
                Py[Y] = X;
                Px[X] = Y;
                return true;
            } else if (dfs(Py[Y])) {
                Py[Y] = X;
                Px[X] = Y;
                return true;
            }
        }
    }
 
    return false;
}
 
void completeMatching() {
    Matching.clear();
    Px.assign(N, -1);
    Py.assign(N, -1);
 
    bool IsPath = true;
    while (IsPath) {
        IsPath = false;
        Visited.assign(N, false);
        for (int X = 0; X < N; X++) {
            if (Px[X] == -1) {
                if (dfs(X)) {
                    IsPath = true;
                }
            }
        }
    }
 
    for (int X = 0; X < N; X++) {
        for (Edge & E : G[X + 1]) {
            int Y = E.To - N - 1;
            if (Px[X] == Y) {
                Matching.push_back(Y);
                E.Flow = 0;
                break;
            }
        }
    }
}
 
int main() {
    freopen("multiassignment.in",  "r", stdin);
    freopen("multiassignment.out", "w", stdout);
 
    std::cin >> N >> K;
 
    S = 0;
    T = 2 * N + 1;
 
    G.resize(2 * N + 2);
     
    // construct edges from S to L
    for (int V = 1; V <= N; V++) {
        addEdge(0, V, K, 0);
    }
 
    // and from R to T
    for (int U = N + 1; U <= 2 * N; U++) {
        addEdge(U, 2 * N + 1, K, 0);
    }
     
    // construct bipartite graph
    for (int U = 1; U <= N; U++) {
        for (int V = N + 1; V <= 2 * N; V++) {
            int C;
            std::cin >> C;
            addEdge(U, V, 1, C);
        }
    }
 
    N = 2 * N + 2;
     
    // run min cost flow algorithm on G
    std::cout << minCostFlow() << std::endl;
     
    N = (N - 2) / 2;
 
    // search for K complete matchings in G
    for (int T = 0; T < K; T++) {
        completeMatching();
        for (int I = 0; I < Matching.size(); I++) {
            std::cout << Matching[I] + 1 << ' ';
        }
        std::cout << std::endl;
    }
 
    return 0;
}
