#include <iostream>
#include <utility>
#include <cstdio>
#include <list>

using namespace std;

list< pair<int, int> > N[9];

int S[9][17] = {
    {8, 1, 2, 3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16},
    {8, 1, 3, 2,  4,  5,  7,  6,  8,  9,  11, 10, 12, 13, 15, 14, 16},
    {8, 1, 5, 2,  6,  3,  7,  4,  8,  9,  13, 10, 14, 11, 15, 12, 16},
    {8, 1, 9, 2,  10, 3,  11, 4,  12, 5,  13, 6,  14, 7,  15, 8,  16},
    {7, 2, 3, 4,  13, 14, 15, 5,  9,  6,  11, 7,  10, 8,  12        },
    {7, 2, 5, 12, 15, 8,  14, 3,  9,  7,  13, 4,  11, 6,  10        },
    {6, 4, 6, 8,  10, 12, 14, 3,  5,  7,  9,  11, 13                },
    {4, 6, 9, 10, 13, 4,  7,  8,  11                                },
    {5, 4, 5, 6,  7,  8,  9,  10, 11, 12, 13                        }
};

int main() {
    int n;
    freopen("netbuild.in",  "r", stdin);
    freopen("netbuild.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < 9; i++) {
        for (int j = 1; j < S[i][0] * 2; j += 2) {
            int fst = S[i][j], snd = S[i][j + 1];
            if (fst <= n && snd <= n) {
                N[i].push_back(make_pair(fst, snd));
            }
        }
    };
    int m = 0, k = 0;
    for (int i = 0; i < 9; i++) {
        if (N[i].size() != 0) {
            m += N[i].size();
            k++;
        }
    }
    cout << n << " " << m << " " << k << endl;
    int cnt = 0;
    for (int i = 0; i < 9; i++) {
        if (N[i].size() != 0) {
            cout << N[i].size();
            for (list< pair<int, int> >::iterator it = N[i].begin(); it != N[i].end(); it++) {
                cout << " " << it->first << " " << it->second;
            }
            cout << endl;;
        }
    }
    return 0;
}
