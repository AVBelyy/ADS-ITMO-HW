#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

const int infty = 1e9;

int d[2000014];
int a[500000];

void build(int vget, int curl, int curr) {
    if (curl != curr) {
        int mid = (curl + curr) / 2;
        build(vget * 2, curl, mid);
        build(vget * 2 + 1, mid + 1, curr);
        d[vget] = min(d[vget * 2], d[vget * 2 + 1]);
    } else {
        d[vget] = a[curl - 1];
    }
}

void update(int vget, int curl, int curr, int pos, int x) {
    if (curl != curr) {
        int mid = (curl + curr) / 2;
        if (pos <= mid) {
            update(vget * 2, curl, mid, pos, x);
        } else {
            update(vget * 2 + 1, mid + 1, curr, pos, x);
        }
        d[vget] = min(d[vget * 2], d[vget * 2 + 1]);
    } else {
        d[vget] = x;
    }
}

int acquire(int vget, int curl, int curr, int l, int r) {
    if (l > r) {
        return infty;
    } else if (l == curl && r == curr) {
        return d[vget];
    } else {
        int mid = (curl + curr) / 2;
        return min(acquire(vget * 2, curl, mid, l, min(mid, r)), acquire(vget * 2 + 1, mid + 1, curr, max(mid + 1, l), r));
    }
}

int main() {
    int n, x, X, Y;
    string cmd;
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= 500000; i++) {
        d[i] = infty;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(1, 1, n);
    while (true) {
        if (!(cin >> cmd >> X >> Y)) break;
        if (cmd == "min") {
            cout << acquire(1, 1, n, X, Y) << endl;
        } else {
            update(1, 1, n, X, Y);
        }
    }
    return 0;
}
