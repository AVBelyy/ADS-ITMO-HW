#include <stdio.h>

int h[100001];

int main() {
    int n, i, flag = 1;
    freopen("isheap.in",  "r", stdin);
    freopen("isheap.out", "w", stdout);
    scanf("%d", &n);
    scanf("%d", &h[1]);
    for (i = 2; i <= n; i++) {
        scanf("%d", &h[i]);
        if (h[i/2] > h[i]) {
            flag = 0;
            break;
        }
    }
    printf(flag ? "YES\n" : "NO\n");
    return 0;
}
