#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <set>

using namespace std;

int n;
char S;

struct rule {
    char c;
    vector<char> to;

    rule(char c, vector<char> & to) : c(c), to(to) {}
};

vector<rule> g;
set<char> all;
set<char> good1;
set<char> good2;

bool nterm(char c) {
    return 'A' <= c && c <= 'Z';
}

int main() {
    string buf;

    freopen("useless.in",  "r", stdin);
    freopen("useless.out", "w", stdout);

    cin >> n >> S;
    getline(cin, buf);
    for (int i = 0; i < n; i++) {
        getline(cin, buf);
        char c = buf[0];
        vector<char> r;
        all.insert(c);
        bool flag = true;
        for (int j = 5; j < buf.size(); j++) {
            r.push_back(buf[j]);
            if (nterm(buf[j])) {
                all.insert(buf[j]);
                flag = false;
            }
        }
        if (flag) {
            good1.insert(c);
        }
        g.emplace_back(c, r);
    }
    bool changed;
    do {
        changed = false;
        for (auto & r : g) {
            char c = r.c;
            auto & rs = r.to;
            bool flag = true;
            for (char d : rs) {
                if (nterm(d) && !good1.count(d)) {
                    flag = false;
                    break;
                }
            }
            if (flag && good1.count(c) == 0) {
                changed = true;
                good1.insert(c);
            }
        }
    } while (changed);
    // filter
    vector<rule> gg;
    for (auto & r : g) {
        char c = r.c;
        bool flag = good1.count(c);
        for (char d : r.to) {
            if (nterm(d) && !good1.count(d)) {
                flag = false;
                break;
            }
        }
        if (flag) {
            gg.push_back(r);
        }
    }
    g = gg;
 
    good2.insert(S);
    do {
        changed = false;
        for (auto & r : g) {
            char c = r.c;
            auto & rs = r.to;
            if (good2.count(c)) {
                for (char d : rs) {
                    if (nterm(d)) {
                        if (good2.count(d) == 0) {
                            changed = true;
                            good2.insert(d);
                        }
                    }
                }
            }
        }
    } while (changed);
    // filter
    vector<rule> ggg;
    for (auto & r : g) {
        char c = r.c;
        bool flag = good2.count(c);
        for (char d : r.to) {
            if (nterm(d) && !good2.count(d)) {
                flag = false;
                break;
            }
        }
        if (flag) {
            ggg.push_back(r);
        }
    }
    g = ggg;

    for (char C : all) {
        bool flag = false;
        for (auto & r : g) {
            flag |= C == r.c;
            for (char d : r.to) {
                flag |= C == d;
            }
        }
        if (!flag) {
            cout << C << ' ';
        }
    }
    cout << endl;

    return 0;
}
