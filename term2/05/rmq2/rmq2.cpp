#include <cstdio>
#include <stdint.h>
#include <iostream>
#include <utility>
#include <string>
#include <algorithm>

using namespace std;

const int64_t infty = 2e18;

pair<int64_t, int> d[800000];
int64_t ans[800000];
int64_t a[200000];

void build(int vget, int curl, int curr) {
    if (curl != curr) {
        int mid = (curl + curr) / 2;
        build(vget * 2, curl, mid);
        build(vget * 2 + 1, mid + 1, curr);
        ans[vget] = min(ans[vget * 2], ans[vget * 2 + 1]);
    } else {
        ans[vget] = a[curl - 1];
    }
}

void push(int vget) {
    d[vget * 2].first = d[vget * 2].first * d[vget].second + d[vget].first;
    d[vget * 2].second *= d[vget].second;
    d[vget * 2 + 1].first = d[vget * 2 + 1].first * d[vget].second + d[vget].first;
    d[vget * 2 + 1].second *= d[vget].second;
    d[vget].first = 0;
    d[vget].second = 1;
}

void add(int vget, int curl, int curr, int l, int r, int64_t x) {
    if (l > r) {
        return;
    } else if (l == curl && r == curr) {
        d[vget].first += x;
    } else {
        int mid = (curl + curr) / 2;
        push(vget);
        add(vget * 2, curl, mid, l, min(mid, r), x);
        add(vget * 2 + 1, mid + 1, curr, max(mid + 1, l), r, x);
        ans[vget] = min(ans[vget * 2] * d[vget * 2].second + d[vget * 2].first,
                        ans[vget * 2 + 1] * d[vget * 2 + 1].second + d[vget * 2 + 1].first);
    }
}

void set(int vget, int curl, int curr, int l, int r, int64_t x) {
    if (l > r) {
        return;
    } else if (l == curl && r == curr) {
        d[vget].first = x;
        d[vget].second = 0;
    } else {
        int mid = (curl + curr) / 2;
        push(vget);
        set(vget * 2, curl, mid, l, min(mid, r), x);
        set(vget * 2 + 1, mid + 1, curr, max(mid + 1, l), r, x);
        ans[vget] = min(ans[vget * 2] * d[vget * 2].second + d[vget * 2].first,
                        ans[vget * 2 + 1] * d[vget * 2 + 1].second + d[vget * 2 + 1].first);
    }
}

int64_t minimum(int vget, int curl, int curr, int l, int r) {
    if (l > r) {
        return infty;
    } else if (l == curl && r == curr) {
        return ans[vget] * d[vget].second + d[vget].first;
    } else {
        int mid = (curl + curr) / 2;
        push(vget);
        int64_t leftans = minimum(vget * 2, curl, mid, l, min(mid, r));
        int64_t rightans = minimum(vget * 2 + 1, mid + 1, curr, max(mid + 1, l), r);
        ans[vget] = min(ans[vget * 2] * d[vget * 2].second + d[vget * 2].first,
                        ans[vget * 2 + 1] * d[vget * 2 + 1].second + d[vget * 2 + 1].first);
        return min(leftans, rightans);
    }
}

int main() {
    int n;
    int64_t X, Y, Z;
    string cmd;
    ios::sync_with_stdio(0);
    freopen("rmq2.in",  "r", stdin);
    freopen("rmq2.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= 800000; i++) {
        ans[i] = infty;
        d[i].first = 0;
        d[i].second = 1;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(1, 1, n);
    while(1) {
        if(!(cin >> cmd >> X >> Y)) break;
        if (cmd == "min") {
            cout << minimum(1, 1, n, X, Y) << endl;
        } else if (cmd == "set") {
            cin >> Z;
            set(1, 1, n, X, Y, Z);
        } else {
            cin >> Z;
            add(1, 1, n, X, Y, Z);
        }
    }
}
