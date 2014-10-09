#include <iostream>
#include <cstdio>
#include <string>
#include <stdint.h>

using namespace std;

int64_t d[2000014];
int64_t a[500000];

void build(int vget, int curl, int curr) {
    if (curl != curr) {
        int mid = (curl + curr) / 2;
        build(vget * 2, curl, mid);
        build(vget * 2 + 1, mid + 1, curr);
        d[vget] = d[vget * 2] + d[vget * 2 + 1];
    } else {
        d[vget] = a[curl - 1];
    }
}

void update(int vget, int curl, int curr, int pos, int64_t x) {
    if (curl != curr) {
        int mid = (curl + curr) / 2;
        if (pos <= mid) {
            update(vget * 2, curl, mid, pos, x);
        } else {
            update(vget * 2 + 1, mid + 1, curr, pos, x);
        }
        d[vget] = d[vget * 2] + d[vget * 2 + 1];
    } else {
        d[vget] = x;
    }
}

int64_t acquire(int vget, int curl, int curr, int l, int r) {
    if (l > r) {
        return 0;
    } else if (l == curl && r == curr) {
        return d[vget];
    } else {
        int mid = (curl + curr) / 2;
        return acquire(vget * 2, curl, mid, l, min(mid, r)) + acquire(vget * 2 + 1, mid + 1, curr, max(mid + 1, l), r);
    }
}

int main() {
    int n;
    int64_t X, Y;
    string cmd;
    freopen("rsq.in", "r", stdin);
    freopen("rsq.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= 500000; i++) {
        d[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(1, 1, n);
    while (true) {
        if (!(cin >> cmd >> X >> Y)) break;
        if (cmd == "sum") {
            cout << acquire(1, 1, n, X, Y) << endl;
        } else {
            update(1, 1, n, X, Y);
        }
    }
    return 0;
}
