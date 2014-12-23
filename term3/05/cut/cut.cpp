#include <iostream>
#include <cstdio>
#include <vector>

const int Inf = 1e9 + 2007;

int N, M;
int BestCost;
std::vector<std::vector<int>> G;
std::vector<int> BestCut;

void minCut() {
    std::vector<std::vector<int>> CV(N);
    std::vector<int> W(N);
    std::vector<bool> Exists(N, true);
    std::vector<bool> InA(N);

    BestCost = Inf;

    for (int I = 0; I < N; I++) {
        CV[I].assign(1, I);
    }

    for (int Phase = 0; Phase < N - 1; Phase++) {
        InA.assign(N, false);
        W.assign(N, 0);

        for (int It = 0, Prev; It < N - Phase; It++) {
            int Cur = -1;
            
            for (int I = 0; I < N; I++) {
                if (Exists[I] && !InA[I] && (Cur == -1 || W[I] > W[Cur])) {
                    Cur = I;
                }
            }
            // last iteration occurred
            if (It == N - Phase - 1) {
                if (BestCost > W[Cur]) {
                    BestCost = W[Cur];
                    BestCut = CV[Cur];
                }
                CV[Prev].insert(CV[Prev].end(), CV[Cur].begin(), CV[Cur].end());
                for (int I = 0; I < N; I++) {
                    G[Prev][I] = G[I][Prev] += G[Cur][I];
                }
                Exists[Cur] = false;
            } else {
                InA[Cur] = true;
                for (int I = 0; I < N; I++) {
                    W[I] += G[Cur][I];
                }
                Prev = Cur;
            }
        }
    }
}

int main() {
    freopen("cut.in",  "r", stdin);
    freopen("cut.out", "w", stdout);

    scanf("%d%d", &N, &M);

    G.assign(N, std::vector<int>(N));

    // read graph
    for (int I = 0; I < M; I++) {
        int U, V, C;
        scanf("%d%d%d", &U, &V, &C);
        G[U - 1][V - 1] += C;
        G[V - 1][U - 1] += C;
    }

    // compute T set
    minCut();

    // compute S set
    std::vector<bool> InS(N, true);
    for (int I = 0; I < BestCut.size(); I++) {
        InS[BestCut[I]] = false;
    }

    // output S set
    std::cout << N - BestCut.size() << std::endl;
    for (int I = 0; I < N; I++) {
        if (InS[I]) {
            std::cout << I + 1 << ' ';
        }
    }
    std::cout << std::endl;
    
    return 0;
}
