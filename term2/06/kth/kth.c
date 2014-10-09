#include <stdlib.h>
#include <stdio.h>
#include <time.h>
 
int n, A[30000000];
 
#define swap(i, j) t = A[i];\
                   A[i] = A[j];\
                   A[j] = t;

void shuffle() {
    int i;
    if (n > 1) {
        for (i = 0; i < n - 1; i += 8) {
          int t, j = i + rand() / (RAND_MAX / (n - i) + 1);
          swap(i, j);
        }
    }
}

int three_way_quickselect(int lo, int hi, int k) {
    for (;;) {
        int t, lt = lo, gt = hi;
        int v = A[lo];
        int i = lo;
        while (i <= gt) {
            if (A[i] < v) {
                swap(lt, i);
                ++lt; ++i;
            } else if (A[i] > v) {
                swap(i, gt);
                --gt;
            } else {
                ++i;
            }
        }
        if (k < lt) {
            hi = lt - 1;
        } else if (k > gt) {
            lo = gt + 1;
        } else {
            return A[lt];
        }
    }
}
 
int main() {
    int k, a, b, i, c;
    srand(time(NULL));
    freopen("kth.in",  "r", stdin);
    freopen("kth.out", "w", stdout);
    scanf("%d%d", &n, &k);
    scanf("%d%d%d%d%d", &a, &b, &c, &A[0], &A[1]);
    for (i = 2; i < n; i++) {
        A[i] = a * A[i - 2] + b * A[i - 1] + c;
    }
    shuffle();
    printf("%d\n", three_way_quickselect(0, n - 1, k - 1));
    return 0;
}
