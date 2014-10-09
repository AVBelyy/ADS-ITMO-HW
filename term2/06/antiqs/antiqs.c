#include <stdio.h>

int A[70000];

int main() {
    int n, i, t;
    freopen("antiqs.in",  "r", stdin);
    freopen("antiqs.out", "w", stdout);
    scanf("%d", &n);
    for (i = n - 1; i >= 0; i--) { A[i] = A[((n + i - 1) >> 1)]; A[(n + i - 1) >> 1] = i + 1; }
    for (i = 0;     i < n;  i++) {                    printf("%d ", A[i]);                    }
    return 0;
}
