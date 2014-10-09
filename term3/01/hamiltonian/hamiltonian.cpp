#include <iostream>
#include <utility>
#include <cstdio>
#include <vector>
#include <stack>

int N, M;

std::vector<std::vector<int>> G;
std::vector<int> Ginv;

bool findHamiltonianPath(int S) {
    std::stack<std::pair<int, int>> Q;
    bool Found = false;

    Q.emplace(S, 1);

    while (!Q.empty()) {
        auto P = Q.top();
        int U = P.first;
        int Depth = P.second;
        Q.pop();
        
        if (Depth == N) {
            Found = true;
            break;
        }

        for (int V: G[U]) {
            Ginv[V]--;
            if (Ginv[V] == 0) {
                Q.emplace(V, Depth + 1);
            }
        }
    }

    return Found;
}

int main() {
    freopen("hamiltonian.in",  "r", stdin);
    freopen("hamiltonian.out", "w", stdout);

    scanf("%d%d", &N, &M);

    G.resize(N);
    Ginv.resize(N);

    for (int I = 0; I < M; I++) {
        int U, V;
        scanf("%d%d", &U, &V);
        G[U - 1].push_back(V - 1);
        Ginv[V - 1]++;
    }

    int S = -1;

    for (int I = 0; I < N; I++) {
        if (Ginv[I] == 0) {
            S = I;
            break;
        }
    }

    // S must definitely be set, as graph contains no cycles

    if (findHamiltonianPath(S)) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
