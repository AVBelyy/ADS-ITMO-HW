#include <iostream>
#include <cstdio>
#include <vector>
 
const int Inf = 1e6 + 2015;
 
int main() {
    freopen("assignment.in",  "r", stdin);
    freopen("assignment.out", "w", stdout);
 
    int N;
 
    std::cin >> N;
 
    int C[N + 1][N + 1];
 
    for (int I = 1; I <= N; I++) {
        for (int J = 1; J <= N; J++) {
            std::cin >> C[I][J];
        }
    }
 
    std::vector<int> U(N + 1);
    std::vector<int> V(N + 1);
    std::vector<int> Matching(N + 1);
    std::vector<int> Parent(N + 1);
 
    for (int I = 1; I <= N; I++) {
        Matching[0] = I;
        int J2 = 0;
        std::vector<int> MinV(N + 1, Inf);
        std::vector<bool> Used(N + 1, false);
 
        do {
            Used[J2] = true;
            int I2 = Matching[J2];
            int Delta = Inf;
            int J1;
 
            for (int J = 1; J <= N; J++) {
                if (!Used[J]) {
                    int Cur = C[I2][J] - U[I2] - V[J];
                    if (MinV[J] > Cur) {
                        MinV[J] = Cur;
                        Parent[J] = J2;
                    }
                    if (Delta > MinV[J]) {
                        Delta = MinV[J];
                        J1 = J;
                    }
                }
            }
 
            for (int J = 0; J <= N; J++) {
                if (Used[J]) {
                    U[Matching[J]] += Delta;
                    V[J] -= Delta;
                } else {
                    MinV[J] -= Delta;
                }
            }
 
            J2 = J1;
        } while (Matching[J2] != 0);
 
        do {
            int J1 = Parent[J2];
            Matching[J2] = Matching[J1];
            J2 = J1;
        } while (J2 != 0);
    }
 
    std::vector<int> Ans(N + 1);
    for (int I = 1; I <= N; I++) {
        Ans[Matching[I]] = I;
    }
 
    std::cout << -V[0] << std::endl;
    for (int I = 1; I <= N; I++) {
        std::cout << I << " " << Ans[I] << std::endl;
    }
 
    return 0;
}
