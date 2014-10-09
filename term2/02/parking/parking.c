#include <stdio.h>
#include <string.h>

struct Info {
    int min;
    int count;
    int rank;
};

struct Info info[300005];
int n, p[300005];

int Get(int x) {
    if (p[x] == x) {
        return x;
    } else {
        return p[x] = Get(p[x]);
    }
}

void Union(int x, int y) {
    int flag = x < y;
    x = (x + n) % n;
    y = (y + n) % n;
    if (p[x] == -1 || p[y] == -1) return;
    int X = Get(x), Y = Get(y);
    int min = flag ? info[X].min : info[Y].min;
    if (X != Y) {
        if (info[X].rank == info[Y].rank) {
            info[X].rank++;
        }
        if (info[X].rank < info[Y].rank) {
            p[X] = Y;
            info[Y].min = min;
            info[Y].count += info[X].count;
        } else {
            p[Y] = X;
            info[X].min = min;
            info[X].count += info[Y].count;
        }
    }
}

int main() {
    int i, x;
    freopen("parking.in",  "r", stdin);
    freopen("parking.out", "w", stdout);
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        info[i].min = i;
        info[i].count = 1;
        info[i].rank = 0;
        p[i] = -1;
    }
    for (i = 0; i < n; i++) {
        scanf("%d", &x);
        x--;
        if (p[x] != -1) {
            int X = Get(x);
            x = (info[X].min + info[X].count) % n;
        }
        p[x] = x;
        Union(x, x - 1);
        Union(x, x + 1);
        printf("%d ", x + 1);
    }
    printf("\n");
    return 0;
}
