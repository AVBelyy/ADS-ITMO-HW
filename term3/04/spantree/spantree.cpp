#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <limits>

const int Inf = std::numeric_limits<int>::max();

struct Point {
    int X;
    int Y;
};

int main() {
    int N;

    freopen("spantree.in",  "r", stdin);
    freopen("spantree.out", "w", stdout);

    scanf("%d", &N);

    std::vector<Point> Coordinates(N);
    std::vector<int> Key(N, Inf);
    std::vector<bool> Visited(N);

    for (int I = 0; I < N; I++) {
        int X, Y;
        scanf("%d%d", &X, &Y);
        Coordinates[I] = {X, Y};
    }

    Key[0] = 0;

    while (true) {
        int MinV = -1, MinKey = Inf;
        
        for (int V = 0; V < N; V++) {
            if (MinKey > Key[V] && !Visited[V]) {
                MinKey = Key[V];
                MinV = V;
            }
        }
        
        if (MinV == -1) {
            break;
        } else {
            Visited[MinV] = true;

            for (int U = 0; U < N; U++) {
                int Ux = Coordinates[U].X, Vx = Coordinates[MinV].X;
                int Uy = Coordinates[U].Y, Vy = Coordinates[MinV].Y;
                int W = (Ux - Vx) * (Ux - Vx) + (Uy - Vy) * (Uy - Vy);

                if (!Visited[U] && Key[U] > W) {
                    Key[U] = W;
                }
            }
        }
    }

    double Answer = 0.0;
    for (int I = 0; I < N; I++) {
        Answer += sqrt(Key[I]);
    }

    std::cout << std::setprecision(9) << Answer << std::endl;

    return 0;
}
