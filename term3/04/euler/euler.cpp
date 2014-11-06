#include <cstdio>
#include <stack>
#include <vector>

int N;
std::vector<int> EulerianPath;
std::vector<std::vector<int>> AdjacencyMatrix;
std::vector<int> AdjacencyLines;

void findEulerianPath(int Start) {
    std::stack<int> VertexStack;

    VertexStack.push(Start);

    while (!VertexStack.empty()) {
        int V = VertexStack.top();
        if (AdjacencyLines[V] == 0) { // if there are no neighbors of V left
            EulerianPath.push_back(VertexStack.top());
            VertexStack.pop();
        } else {
            for (int U = 0; U < N; U++) {
                if (AdjacencyMatrix[V][U] > 0) {
                    AdjacencyMatrix[V][U]--;
                    AdjacencyMatrix[U][V]--;
                    AdjacencyLines[V]--;
                    AdjacencyLines[U]--;
                    VertexStack.push(U);
                    break;
                }
            }
        }
    }
}

int main() {
    int OddDegVertices = 0, Start = 0;

    freopen("euler.in",  "r", stdin);
    freopen("euler.out", "w", stdout);

    scanf("%d", &N);

    AdjacencyMatrix.resize(N);
    AdjacencyLines.resize(N);

    for (int I = 0; I < N; I++) {
        AdjacencyMatrix[I].resize(N);
    }

    for (int I = 0; I < N; I++) {
        int CurM;
        
        scanf("%d", &CurM);

        if (CurM % 2 != 0) {
            OddDegVertices++;
            Start = I;
        }

        for (int J = 0; J < CurM; J++) {
            int To;

            scanf("%d", &To);
            To--;

            AdjacencyMatrix[I][To]++;
            AdjacencyLines[I]++;
        }
    }

    if (OddDegVertices == 0 || OddDegVertices == 2) {
        findEulerianPath(Start);

        printf("%d\n", (int)EulerianPath.size() - 1);
        for (int V : EulerianPath) {
            printf("%d ", V + 1);
        }
        putchar('\n');
    } else {
        printf("-1\n");
    }
}
