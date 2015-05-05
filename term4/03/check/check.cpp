#include <iostream>
#include <cstdio>
#include <bitset>

using namespace std;

const int NMAX = 10;

inline int count_ones(int n) {
    int count = 0;
    while (n != 0) {
        n &= n - 1;
        count++;
    }
    return count;
}

bool is_matroid(bitset<1 << NMAX> & ind) {
    // ax. 1
    if (!ind.test(0)) {
        return false;
    }

    // ax. 2
    for (int i = 0; i < 1 << NMAX; i++) {
        if (ind.test(i)) {
            for (int j = 0; j < 1 << NMAX; j++) {
                if ((i & j) == j && !ind.test(j)) {
                    return false;
                }
            }
        }
    }

    // ax. 3
    for (int i = 0; i < 1 << NMAX; i++) {
        for (int j = 0; j < 1 << NMAX; j++) {
            if (ind.test(i) && ind.test(j) && count_ones(i) > count_ones(j)) {
                int diff = i & ~j;
                int elem = 0;
                bool ok = false;
                while (diff != 0) {
                    if (diff & 1 && ind.test(j | (1 << elem))) {
                        ok = true;
                        break;
                    }
                    diff >>= 1;
                    elem++;
                }
                if (!ok) {
                    return false;
                }
            }
        }
    }

    // it is matroid
    return true;
}

int main() {
    int n, m;
    bitset<1 << NMAX> ind;

    freopen("check.in",  "r", stdin);
    freopen("check.out", "w", stdout);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int size, subset = 0;
        cin >> size;
        for (int j = 0; j < size; j++) {
            int elem;
            cin >> elem;
            subset |= 1 << (elem - 1);
        }
        ind.set(subset);
    }

    cout << (is_matroid(ind) ? "YES" : "NO") << endl;

    return 0;
}
