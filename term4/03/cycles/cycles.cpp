#include <iostream>
#include <cstdio>
#include <vector>
#include <bitset>

using namespace std;

const int NMAX = 20;

inline int count_ones(int n) {
    int count = 0;    
    while (n != 0) {
        n &= n - 1;
        count++;
    }
    return count;
}

int main() {
    int n, m;
    bitset<1 << NMAX> ind;
    ind.flip();

    freopen("cycles.in",  "r", stdin);
    freopen("cycles.out", "w", stdout);

    cin >> n >> m;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    for (int i = 0; i < m; i++) {
        int bm = 0, count;
        cin >> count;
        for (int j = 0; j < count; j++) {
            int elem;
            cin >> elem;
            bm |= 1 << (elem - 1);
        }
        for (int j = 0; j < 1 << n; j++) {
            if ((j & bm) == bm) {
                ind.reset(j);
            }
        }
    }
    // find rank of base
    int rank = 0;
    for (int i = (1 << n) - 1; i >= 0; i--) {
        if (ind.test(i)) {
            rank = count_ones(i);
            break;
        }
    }
    // find base with max weight
    int maxw = 0;
    for (int i = 0; i < 1 << n; i++) {
        if (ind.test(i) && count_ones(i) == rank) {
            int s = i;
            int curw = 0;
            for (int j = 0; s != 0; j++, s >>= 1) {
                curw += w[j] * (s & 1);
            }
            if (maxw < curw) {
                maxw = curw;
            }
        }
    }
    cout << maxw << endl;
    return 0;
}
