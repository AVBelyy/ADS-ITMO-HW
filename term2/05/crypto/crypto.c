#include <stdio.h>
#include <stdint.h>

int r;

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

typedef struct {
    int a, b, c, d;
} matrix;

matrix id;

matrix d[800008];
matrix ms[200000];

matrix mmul(matrix x, matrix y) {
    matrix z;
    z.a = ((x.a * y.a) % r + (x.b * y.c) % r) % r;
    z.b = ((x.a * y.b) % r + (x.b * y.d) % r) % r;
    z.c = ((x.c * y.a) % r + (x.d * y.c) % r) % r;
    z.d = ((x.c * y.b) % r + (x.d * y.d) % r) % r;
    return z;
}

void build(int vget, int curl, int curr) {
    if (curl != curr) {
        int mid = (curl + curr) / 2;
        build(vget * 2, curl, mid);
        build(vget * 2 + 1, mid + 1, curr);
        d[vget] = mmul(d[vget * 2], d[vget * 2 + 1]);
    } else {
        d[vget] = ms[curl - 1];
    }
}

matrix acquire(int vget, int curl, int curr, int l, int r) {
    if (l > r) {
        return id;
    } else if (l == curl && r == curr) {
        return d[vget];
    } else {
        int mid = (curl + curr) / 2;
        return mmul(acquire(vget * 2, curl, mid, l, min(mid, r)), acquire(vget * 2 + 1, mid + 1, curr, max(mid + 1, l), r));
    }
}

int main() {
    int n, m;
    id.a = 1; id.b = 0;
    id.c = 0; id.d = 1;
    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);
    scanf("%d%d%d", &r, &n, &m);
    for (int i = 1; i <= 500000; i++) {
        d[i] = id;
    }
    for (int i = 0; i < n; i++) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        ms[i].a = a; ms[i].b = b;
        ms[i].c = c; ms[i].d = d;
    }
    build(1, 1, n);
    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        matrix ans = acquire(1, 1, n, l, r);
        printf("%d %d\n%d %d\n\n", ans.a, ans.b, ans.c, ans.d);
    }
    return 0;
}
