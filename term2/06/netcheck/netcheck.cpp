#include <iostream>
#include <utility>
#include <cstdio>
#include <list>

using namespace std;

list< pair<int, int> > C[150];

int main() {
    int n, m, k, r;
    freopen("netcheck.in",  "r", stdin);
    freopen("netcheck.out", "w", stdout);
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        cin >> r;
        for (int j = 0; j < r; j++) {
            int a, b;
            cin >> a >> b;
            C[i].push_back(make_pair(min(a - 1, b - 1), max(a - 1, b - 1)));
        }
    }
    int test[16];
    bool flag = true;
    for (int i = 0; i < 1 << n; i++) {
        for (int j = 0; j < n; j++) {
            test[j] = (i & (1 << j)) >> j;
        }
        for (int j = 0; j < k; j++) {
            for (list< pair<int, int> >::iterator it = C[j].begin(); it != C[j].end(); it++) {
                if (test[it->first] > test[it->second]) {
                    int tmp = test[it->first];
                    test[it->first] = test[it->second];
                    test[it->second] = tmp;
                }
            }
        }
        for (int j = 1; j < n; j++) {
            if (test[j - 1] > test[j]) {
                flag = false;
                break;
            }
        }
        if (!flag) break;
    }
    if (flag) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}
