#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

bool Found = false;
int N, M;
std::vector<std::vector<int>> G;
std::vector<int> Parent;
std::vector<int> Visited;

void outputCycle(int V) {
    int U = V;
    std::cout << "YES" << std::endl;
    std::stack<int> Vs;
    do {
        Vs.push(U);
        U = Parent[U];
    } while (U != V);
    while (!Vs.empty()) {
        U = Vs.top();
        std::cout << U + 1 << ' ';
        Vs.pop();
    }
    std::cout << std::endl;
}

void findCycle(int V) {
    if (Found) return;

    for (int U: G[V]) {
        if (Visited[U] && !Found) {
            Found = true;
            Parent[U] = V;
            outputCycle(U);
            return;
        } else {
            Parent[U] = V;
            Visited[U] = true;
            findCycle(U);
            Visited[U] = false;
            Parent[U] = -1;
        }
    }
}

int main() {
    freopen("cycle.in",  "r", stdin);
    freopen("cycle.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);

    std::cin >> N >> M;

    G.resize(N);
    Parent.resize(N);
    Visited.resize(N);

    for (int I = 0; I < N; I++) {
        Parent[I] = -1;
    }

    for (int I = 0; I < M; I++) {
        int U, V;
        std::cin >> U >> V;
        if (U != V) {
            G[U - 1].push_back(V - 1);
        }
    }

    for (int I = 0; I < N; I++) {
        findCycle(I);
    }

    if (!Found) {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
