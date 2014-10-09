#include <iostream>
#include <cstdio>

int n, A[100002];

int binsearch(int x, bool f) {
    int l = 0, r = n + 1;
    if (f) {
        while (r > l + 1) {
            int m = (l + r) / 2;
            if (A[m] < x) {
                l = m;
            } else {
                r = m;
            }
        }
        return r;
    } else {
        while (r > l + 1) {
            int m = (l + r) / 2;
            if (A[m] <= x) {
                l = m;
            } else {
                r = m;
            }
        }
        return l;
    }
}

int main() {
    int m;
    freopen("binsearch.in",  "r", stdin);
    freopen("binsearch.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int t;
        scanf("%d", &t);
        int l = binsearch(t, true), r = binsearch(t, false);
        if (l - r > 0) {
            printf("-1 -1\n");
        } else {
            printf("%d %d\n", l, r);
        }
    }
    return 0;
}
