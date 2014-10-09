#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

int main() {
    int N, M;
    std::vector<int> Ordering;

    freopen("topsort.in",  "r", stdin);
    freopen("topsort.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);

    std::cin >> N >> M;

    std::vector<std::vector<int>> G(N);
    std::vector<int> Ginv(N);
    std::vector<bool> Visited(N);
    std::stack<int> Zeroes;

    for (int I = 0; I < M; I++) {
        int U, V;
        std::cin >> U >> V;
        G[U - 1].push_back(V - 1);
        Ginv[V - 1]++;
    }
    
    for (int I = 0; I < N; I++) {
        if (Ginv[I] == 0) {
            Zeroes.push(I);
        }
    }
    
    while (Zeroes.size() != 0) {
        int NextV = Zeroes.top();
        Zeroes.pop();
        Ordering.push_back(NextV);
        Visited[NextV] = true;
        for (int V: G[NextV]) {
            if (Visited[V]) continue;
            Ginv[V]--;
            if (Ginv[V] == 0) {
                Zeroes.push(V);
            }
        }
    }
    
    if (Ordering.size() == N) {
        for (int V: Ordering) {
            std::cout << V + 1 << ' ';
        }
        std::cout << std::endl;
    } else {
        std::cout << -1 << std::endl;
    }

    return 0;
}
