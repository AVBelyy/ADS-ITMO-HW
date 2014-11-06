#include <unordered_map>
#include <iostream>
#include <cstdio>
#include <vector>
#include <list>

struct Edge_t {
    int Other;
    bool Visited;

    Edge_t(int Other, bool Visited) : Other(Other), Visited(Visited) {}
};

int N, M, VisitedEdges = 0;
std::vector<std::vector<Edge_t *>> Graph;

bool FoundPath;
std::vector<bool> Visited;
std::vector<Edge_t *> BackEdgesTmp;
std::vector<Edge_t *> BackEdges;
std::list<int> FreeVertices;
std::unordered_map<int, std::list<int>::iterator> FreeVerticesMapping;
std::vector<std::list<Edge_t *>> FreeEdges;
std::vector<std::unordered_map<int, std::list<Edge_t *>::iterator>> FreeEdgesMapping;

void occupyEdge(int U, Edge_t * E) {
    int V = U ^ E->Other;
    E->Visited = true;
    VisitedEdges++;
    auto ItUV = FreeEdgesMapping[U][V];
    FreeEdgesMapping[U][V] = FreeEdges[U].end();
    FreeEdges[U].erase(ItUV);
    auto ItVU = FreeEdgesMapping[V][U];
    FreeEdgesMapping[V][U] = FreeEdges[V].end();
    FreeEdges[V].erase(ItVU);
}

void occupyVertex(int V) {
    auto Iter = FreeVerticesMapping[V];
    FreeVerticesMapping[V] = FreeVertices.end();
    FreeVertices.erase(Iter);
}

void findPath(int V, int End, bool IsSimple, Edge_t * UsingE = nullptr) {
    if (FoundPath) return;
    Visited[V] = true;

    if (UsingE == nullptr) {
        for (Edge_t * E : Graph[V]) {
            if (!E->Visited) {
                int U = V ^ E->Other;
                if ((IsSimple || Visited[U]) && U == End && !FoundPath) {
                    FoundPath = true;
                    BackEdgesTmp[U] = E;
                    BackEdges = BackEdgesTmp;
                    return;
                } else if (!Visited[U]) {
                    BackEdgesTmp[U] = E;
                    E->Visited = true;
                    findPath(U, End, IsSimple);
                    E->Visited = false;
                    BackEdgesTmp[U] = nullptr;
                }
            }
        }
    } else {
        int U = V ^ UsingE->Other;
        BackEdgesTmp[U] = UsingE;
        UsingE->Visited = true;
        findPath(U, End, IsSimple);
        UsingE->Visited = false;
        BackEdgesTmp[U] = nullptr;
    }

    Visited[V] = false;
}

std::list<int> getPath(int Start, int End, Edge_t * UsingE = nullptr) {
    std::list<int> Path;

    FoundPath = false;
    Visited = std::vector<bool>(N);
    BackEdgesTmp = std::vector<Edge_t *>(N);
    
    findPath(Start, End, Start != End, UsingE);
    if (FoundPath) {
        int U = End;
        do {
            Path.push_back(U);
            Edge_t * E = BackEdges[U];
            occupyEdge(U, E);
            U = U ^ E->Other;
        } while (U != Start);
        Path.push_back(Start);
    }
    
    return Path;
}

void extractFreeVerticesFromPath(std::list<int> & Path) {
    for (int V : Path) {
        bool IsFree = false;
        for (Edge_t * E : Graph[V]) {
            if (!E->Visited) {
                IsFree = true;
                break;
            }
        }
        FreeVertices.push_back(V);
        auto Iter = FreeVertices.end();
        --Iter;
        FreeVerticesMapping[V] = Iter;
    }
}

std::list<int> findEulerianPath(std::list<int> InitialPath) {
    std::list<int> EulerianPath = InitialPath;
    extractFreeVerticesFromPath(InitialPath);
    
    while (VisitedEdges != M) {
        for (auto Iter = EulerianPath.begin(); Iter != EulerianPath.end(); Iter++) {
            int V = *Iter;
            std::cout << VisitedEdges << std::endl;
            if (!FreeEdges[V].empty()) {
                Edge_t * E = *FreeEdges[V].begin();
                auto NextIter = Iter;
                NextIter++;
                EulerianPath.erase(Iter);
                auto NewCycle = getPath(V, V, E);
                extractFreeVerticesFromPath(NewCycle);
                EulerianPath.splice(NextIter, NewCycle);
                for (int V : FreeVertices) {
                    bool IsOccupied = true;
                    for (Edge_t * E : Graph[V]) {
                        if (!E->Visited) {
                            IsOccupied = false;
                            break;
                        }
                    }
                    if (IsOccupied) {
                        occupyVertex(V);
                    }
                }
                break;
            }
        }
    }

    return EulerianPath;
}

int main() {
    freopen("euler.in",  "r", stdin);
    //freopen("euler.out", "w", stdout);

    scanf("%d", &N);

    Graph.resize(N);
    FreeEdges.resize(N);
    FreeEdgesMapping.resize(N);

    std::vector<int> OddDegVertices;
    
    for (int I = 0; I < N; I++) {
        int CurM;

        scanf("%d", &CurM);

        M += CurM;
        if (CurM % 2 != 0) {
            OddDegVertices.push_back(I);
        }

        for (int J = 0; J < CurM; J++) {
            int To;

            scanf("%d", &To);
            To--;
            if (I < To) {
                // To hell with leaking memory
                Edge_t * E = new Edge_t(I ^ To, false);

                Graph[I].push_back(E);
                Graph[To].push_back(E);
                FreeEdges[I].push_back(E);
                FreeEdges[To].push_back(E);
                auto IterI = FreeEdges[I].end();
                auto IterTo = FreeEdges[To].end();
                --IterI;
                --IterTo;
                FreeEdgesMapping[I][To] = IterI;
                FreeEdgesMapping[To][I] = IterTo;
            }
        }
    }

    M /= 2;

    if (OddDegVertices.size() == 0) {
        auto EulerianCycle = findEulerianPath(getPath(0, 0));
        
        std::cout << M << std::endl;
        for (int To : EulerianCycle) {
            std::cout << To + 1 << " ";
        }
        std::cout << std::endl;
    } else if (OddDegVertices.size() == 2) {
        int Start = OddDegVertices[0];
        int End = OddDegVertices[1];
        auto EulerianPath = findEulerianPath(getPath(Start, End));
        
        std::cout << M << std::endl;
        for (int To : EulerianPath) {
            std::cout << To + 1 << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << -1 << std::endl;
    }

    return 0;
}
