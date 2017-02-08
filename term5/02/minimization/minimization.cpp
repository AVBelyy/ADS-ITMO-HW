#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

struct row {
    int to[26];
};

struct row2 {
    vector<int> to[26];
};

int n, m, k;
vector<row2> ginv;
vector<vector<int>> g;
vector<row> edges;
vector<bool> reachable;
vector<bool> terminal;
vector<vector<bool>> marked;
vector<int> comp;
int compCount;

void buildReachable(int u) {
    reachable[u] = true;
    for (int v : g[u]) {
        if (!reachable[v]) {
            buildReachable(v);
        }
    }
}

void buildTable() {
    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!marked[i][j] && terminal[i] != terminal[j]) {
                marked[i][j] = marked[j][i] = true;
                q.emplace(i, j);
            }
        }
    }
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        int u = p.first, v = p.second;
        for (char c = 'a'; c <= 'z'; c++) {
            for (int r : ginv[u].to[c - 'a']) {
                for (int s : ginv[v].to[c - 'a']) {
                    if (!marked[r][s]) {
                        marked[r][s] = marked[s][r] = true;
                        q.emplace(r, s);
                    }
                }
            }
        }
    }
}

void minimization() {
    comp.assign(n, -1);
    compCount = 0;
    for (int i = 0; i < n; i++) {
        if (!marked[0][i]) {
            comp[i] = 0;
        }
    }
    for (int i = 1; i < n; i++) {
        if (!reachable[i]) {
            continue;
        }
        if (comp[i] == -1) {
            compCount++;
            comp[i] = compCount;
            for (int j = i + 1; j < n; j++) {
                if (!marked[i][j]) {
                    comp[j] = compCount;
                }
            }
        }
    }
}

int main() {
    freopen("minimization.in",  "r", stdin);
    freopen("minimization.out", "w", stdout);

    cin >> n >> m >> k;
    n++;
    reachable.resize(n);
    g.resize(n);
    ginv.resize(n);
    marked.resize(n);
    terminal.resize(n);
    edges.resize(n);
    
    for (int i = 0; i < k; i++) {
        int t;
        cin >> t;
        terminal[t] = true;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        g[u].push_back(v);
        ginv[v].to[c - 'a'].push_back(u);
        edges[u].to[c - 'a'] = v;
    }
    for (int i = 0; i < n; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            if (edges[i].to[c - 'a'] == 0) {
                ginv[0].to[c - 'a'].push_back(i);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        marked[i].resize(n);
    }

    buildReachable(1);
    buildTable();
    minimization();

    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << marked[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;*/

    // build new DFA
    int newN = compCount;
    vector<row> newEdges(newN + 1);
    for (int i = 0; i < n; i++) {
        if (comp[i] == -1) {
            continue;
        }
        for (char c = 'a'; c <= 'z'; c++) {
            newEdges[comp[i]].to[c - 'a'] = comp[edges[i].to[c - 'a']];
        }
    }
    set<pair<pair<int, int>, char>> brandNewEdges;
    for (int i = 0; i < n; i++) { 
        if (comp[i] == -1) {
            continue;
        }
        for (char c = 'a'; c <= 'z'; c++) {
            if (newEdges[comp[i]].to[c - 'a']) {
                brandNewEdges.insert({{comp[i], newEdges[comp[i]].to[c - 'a']}, c});
            }
        }
    }
    int newM = brandNewEdges.size();
    set<int> newTerminal;
    for (int i = 0; i < n; i++) {
        if (terminal[i] && comp[i]) {
            newTerminal.insert(comp[i]);
        }
    }
    int newK = newTerminal.size();

    // output new DFA
    cout << newN << ' ' << newM << ' ' << newK << endl;
    for (int t : newTerminal) {
        cout << t << ' ';
    }
    cout << endl;
    for (auto & p : brandNewEdges) {
        cout << p.first.first << ' ' << p.first.second << ' ' << p.second << endl;
    }

    return 0;
}
