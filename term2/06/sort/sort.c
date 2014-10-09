#include <stdio.h>
#include <string.h>

int A[200001];
int cnt = 0;

void swap(int i, int j) {
    int t = A[i];
    A[i] = A[j];
    A[j] = t;
}

void siftUp(int x) {
    if (x == 1) return;
    if (A[x] < A[x / 2]) {
        swap(x, x / 2);
        siftUp(x / 2);
    }
}

void siftDown(int x) {
    if (x > 1e5) return;
    if ((A[2 * x] < A[2 * x + 1] || (A[2 * x] == A[2 * x + 1] && A[2 * x] != 2*1e9)) && A[x] > A[2 * x]) {
        swap(x, 2 * x);
        siftDown(2 * x);
    } else if (A[2 * x] > A[2 * x + 1] && A[x] > A[2 * x + 1]) {
        swap(x, 2 * x + 1);
        siftDown(2 * x + 1);
    }
}

int main() {
    int i, n;
    freopen("sort.in",  "r", stdin);
    freopen("sort.out", "w", stdout);
    for (i = 0; i <= 2*1e5; i++) {
        A[i] = 2*1e9;
    }
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        int t;
        scanf("%d", &t);
        cnt++;
        A[cnt] = t;
        siftUp(cnt);
    }
    for (i = 0; i < n; i++) {
        printf("%d ", A[1]);
        swap(1, cnt);
        A[cnt] = 2*1e9;
        cnt--;
        siftDown(1);
    }
    printf("\n");
    return 0;
}
