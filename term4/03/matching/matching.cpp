#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

std::vector< std::vector<int> > G;
std::vector<bool> Visited;
std::vector<int> Px;
std::vector<int> Py;

bool dfs(int X) {
    if (Visited[X]) {
        return false;
    }

    Visited[X] = true;

    for (int I = 0; I < G[X].size(); I++) {
        int Y = G[X][I];
        if (Py[Y] == -1 || dfs(Py[Y])) {
            Px[X] = Y;
            Py[Y] = X;
            return true;
        }
    }

    return false;
}

int main() {
    freopen("matching.in",  "r", stdin);
    freopen("matching.out", "w", stdout);

    int N;
    scanf("%d", &N);

    G.resize(N);
    Px.assign(N, -1);
    Py.assign(N, -1);

    std::vector< std::pair<int, int> > Ws(N);

    for (int I = 0; I < N; I++) {
        int W;
        scanf("%d", &W);
        Ws.push_back(std::make_pair(W, I));
    }

    sort(Ws.begin(), Ws.end(), std::greater< std::pair<int, int> >());

    for (int U = 0; U < N; U++) {
        int Count = 0;
        scanf("%d", &Count);
        for (int I = 0; I < Count; I++) {
            int V;
            scanf("%d", &V);
            V--;
            G[U].push_back(V);
        }
    }

    for (int I = 0; I < N; I++) {
        int X = Ws[I].second;
        Visited.assign(N, false);
        dfs(X);
    }

    for (int X = 0; X < N; X++) {
        std::cout << Px[X] + 1 << ' ';
    }
    std::cout << std::endl;

    return 0;
}
