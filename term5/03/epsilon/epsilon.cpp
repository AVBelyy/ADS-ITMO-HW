#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <set>

using namespace std;

int n;
char S;

map<char, vector<vector<char>>> g;
set<char> bad;

bool nterm(char c) {
    return 'A' <= c && c <= 'Z';
}

int main() {
    string buf;

    freopen("epsilon.in",  "r", stdin);
    freopen("epsilon.out", "w", stdout);

    cin >> n >> S;
    getline(cin, buf);
    for (int i = 0; i < n; i++) {
        getline(cin, buf);
        char c = buf[0];
        vector<char> r;
        for (int j = 5; j < buf.size(); j++) {
            r.push_back(buf[j]);
        }
        g[c].push_back(r);
    }
    bool changed;
    do {
        changed = false;
        for (auto & r : g) {
            char c = r.first;
            auto & rs = r.second;
            for (auto & r : rs) {
                bool flag = true;
                for (char d : r) {
                    if (nterm(d) && bad.count(d)) {
                        flag = true;
                    } else {
                        flag = false;
                        break;
                    }
                }
                if (flag && bad.count(c) == 0) {
                    changed = true;
                    bad.insert(c);
                    break;
                }
            }
        }
    } while (changed);
    for (char c : bad) {
        cout << c << ' ';
    }
    cout << endl;

    return 0;
}
