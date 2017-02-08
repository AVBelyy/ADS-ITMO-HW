#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <queue>
#include <map>

using namespace std;

char S;

vector<map<char, vector<char>>> g;
int tr[256];
bool used[256][10000];

bool bfs(string & w) {
    int len = w.size();
    queue<pair<int, int>> q;
    q.emplace(tr[S], 0);
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        int u = p.first, i = p.second;
        if (i == len) {
            if (u == 0) {
                return true;
            } else {
                continue;
            }
        }
        for (char v : g[u][w[i]]) {
            if (!used[v][i + 1]) {
                q.emplace(tr[v], i + 1);
                used[v][i + 1] = true;
            }
        }
    }
    return false;
}

int main() {
    int n, m;
    string buf;
    freopen("automaton.in",  "r", stdin);
    freopen("automaton.out", "w", stdout);

    cin >> n >> S;
    getline(cin, buf);
    g.resize(n + 1);
    int vertexCount = 0;
    for (int i = 0; i < n; i++) {
        getline(cin, buf);
        char u = buf[0], v = buf[6], c = buf[5];
        if (!('A' <= v && v <= 'Z')) {
            v = 0;
        }
        if (tr[u] == 0) {
            tr[u] = ++vertexCount;
        }
        g[tr[u]][c].push_back(v);
    }
    string w;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> w;
        for (int t1 = 0; t1 < 256; t1++) {
            for (int t2 = 0; t2 < 10000; t2++) {
                used[t1][t2] = 0;
            }
        }
        cout << (bfs(w) ? "yes" : "no") << endl;
    }

    return 0;
}
