#include <stdio.h>
#include <string.h>

int A[100001];  // heap
int AH[100001]; // addr -> heap
int HA[100001]; // heap -> addr
int cnt = 0, pcnt = 0;

void _swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void swap(int i, int j) {
    _swap(&A[i], &A[j]);
    _swap(&HA[i], &HA[j]);
    _swap(&AH[HA[i]], &AH[HA[j]]);
}

void siftUp(int x) {
    if (x == 1) return;
    if (A[x] < A[x / 2]) {
        swap(x, x / 2);
        siftUp(x / 2);
    }
}

void siftDown(int x) {
    if ((A[2 * x] < A[2 * x + 1] || (A[2 * x] == A[2 * x + 1] && A[2 * x] != 2*1e9)) && A[x] > A[2 * x]) {
        swap(x, 2 * x);
        siftDown(2 * x);
    } else if (A[2 * x] > A[2 * x + 1] && A[x] > A[2 * x + 1]) {
        swap(x, 2 * x + 1);
        siftDown(2 * x + 1);
    }
}

int main() {
    int i;
    freopen("priorityqueue.in",  "r", stdin);
    freopen("priorityqueue.out", "w", stdout);
    for (i = 0; i <= 1e5; i++) {
        A[i] = 2*1e9;
    }
    while(1) {
        char cmd[16];
        if (scanf("%s", cmd) == EOF) {
            break;
        }
        pcnt++;
        if (strcmp(cmd, "push") == 0) {
            int x;
            scanf("%d", &x);
            cnt++;
            A[cnt] = x;
            AH[pcnt] = cnt;
            HA[cnt] = pcnt;
            siftUp(cnt);
        } else if (strcmp(cmd, "extract-min") == 0) {
            if (cnt == 0) {
                printf("*\n");
            } else {
                printf("%d\n", A[1]);
                swap(1, cnt);
                A[cnt] = 2*1e9;
                AH[HA[cnt]] = -1;
                cnt--;
                siftDown(1);
            }
        } else if (strcmp(cmd, "decrease-key") == 0) {
            int x, y;
            scanf("%d%d", &x, &y);
            int prev = A[AH[x]];
            A[AH[x]] = y;
            if (prev > y) {
                siftUp(AH[x]);
            } else {
                siftDown(AH[x]);
            }
        }
    }
    return 0;
}
