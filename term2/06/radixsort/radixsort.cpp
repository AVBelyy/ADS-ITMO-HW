#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <list>

using namespace std;

char* S[1000];
int F[32];
list<char*> R[32];

int main() {
    int n, m, k;
    freopen("radixsort.in",  "r", stdin);
    freopen("radixsort.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        S[i] = (char*)malloc(m + 1);
        scanf("%s", S[i]);
    }
    for (int i = m - 1; i >= m - k; i--) {
        memset(F, 0, sizeof(F));
        for (int j = 0; j < 32; j++) {
            R[j].clear();
        }
        for (int j = 0; j < n; j++) {
            int index = S[j][i] - 'a';
            F[index]++;
            R[index].push_back(S[j]);
        }
        int k = 0;
        for (int j = 0; j < 32; j++) {
            for (list<char*>::iterator it = R[j].begin(); it != R[j].end(); ++it, ++k) {
                S[k] = *it;
            }
        }
        
    }
    for (int i = 0; i < n; i++) {
        printf("%s\n", S[i]);
    }
    return 0;
}
