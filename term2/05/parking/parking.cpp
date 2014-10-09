#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

const int infty = 1e9;

int d[2000000];

void build(int vget, int curl, int curr) {
    if (curl != curr) {
        int mid = (curl + curr) / 2;
        build(vget * 2, curl, mid);
        build(vget * 2 + 1, mid + 1, curr);
        d[vget] = min(d[vget * 2], d[vget * 2 + 1]);
    } else {
        d[vget] = curl;
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
    int n, m, x, X;
    string cmd;
    freopen("parking.in", "r", stdin);
    freopen("parking.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= 500000; i++) {
        d[i] = infty;
    }
    build(1, 1, n);
    for (int i = 0; i < m; i++) {
        cin >> cmd >> X;
        if (cmd == "enter") {
            int x = acquire(1, 1, n, X, n);
            if (x == infty) x = acquire(1, 1, n, 1, X - 1);
            update(1, 1, n, x, infty);
            cout << x << endl;
        } else {
            update(1, 1, n, X, X);
        }
    }
    return 0;
}
