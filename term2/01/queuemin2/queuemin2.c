#include <stdio.h>
#include <stdint.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

struct Stack {
    int first;
    int second;
};

struct Stack S1[16000016], S2[16000016];
int K[1000], sz1, sz2;

void push(int x) {
    int i;
    S1[sz1].first = x;
    S1[sz1].second = sz1 == 0 ? x : min(x, S1[sz1 - 1].second);
    sz1++;
    if (sz1 >= 16000000) {
        for (i = sz1 - 1; i >= 0; i--) {
            int el = S1[i].first;
            S2[sz2].first = el;
            S2[sz2].second = sz2 == 0 ? el : min(el, S2[sz2 - 1].second);
            sz2++;
        }
        sz1 = 0;
    }
}

void pop() {
    int i;
    if (sz2 == 0) {
        for (i = sz1 - 1; i >= 0; i--) {
            S2[sz2].first = S1[i].first;
            S2[sz2].second = sz2 == 0 ? S2[sz2].first : min(S2[sz2].first, S2[sz2 - 1].second);
            sz2++;
        }
        sz1 = 0;
    }
    sz2--;
}

int find_min() {
    if (sz2 == 0) {
        return S1[sz1 - 1].second;
    } else {
        return min(S1[sz1 - 1].second, S2[sz2 - 1].second);
    }
}

int main() {
    int n, m, k;
    int64_t a, b, c;
    int i;
    int64_t new, ans = 0;
    sz1 = sz2 = 0;
    freopen("queuemin2.in",  "r", stdin);
    freopen("queuemin2.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    scanf("%lld%lld%lld", &a, &b, &c);
    for (i = 0; i < k; i++) {
        scanf("%d", &K[i]);
    }
    for (i = 0; i < m; i++) {
        if (i < k) {
            push(K[i]);
            continue;
        } else {
            if (sz1 >= 2) {
                new = a * S1[sz1 - 2].first + b * S1[sz1 - 1].first + c;
            } else if (sz1 == 1) {
                new = a * S2[0].first + b * S1[0].first + c;
            } else {
                new = a * S2[1].first + b * S2[0].first + c;
            }
            push(new);
        }
    }
    ans = find_min();
    for (i = m; i < k; i++) {
        pop();
        push(K[i]);
        ans += find_min();
    }
    int t;
    if (m > k) {
        t = m;
    } else {
        t = k;
    }
    for (i = 1; i <= n - t; i++) {
        pop();
        if (sz1 >= 2) {
            new = a * S1[sz1 - 2].first + b * S1[sz1 - 1].first + c;
        } else if (sz1 == 1) {
            new = a * S2[0].first + b * S1[0].first + c;
        } else {
            new = a * S2[1].first + b * S2[0].first + c;
        }
        push(new);
        ans += find_min();
    }
    printf("%lld\n", ans);
    return 0;
}
