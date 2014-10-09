#include <stdio.h>
#include <string.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

struct Info {
    int min;
    int max;
    int count;
    int rank;
};

struct Info info[100500];
int p[100500];

int Get(int x) {
    if (p[x] == x) {
        return x;
    } else {
        return p[x] = Get(p[x]);
    }
}

void Union(int x, int y) {
    int X = Get(x), Y = Get(y);
    if (X != Y) {
        if (info[X].rank == info[Y].rank) {
            info[X].rank++;
        }
        if (info[X].rank < info[Y].rank) {
            p[X] = Y;
            info[Y].max = max(info[X].max, info[Y].max);
            info[Y].min = min(info[X].min, info[Y].min);
            info[Y].count += info[X].count;
        } else {
            p[Y] = X;
            info[X].max = max(info[X].max, info[Y].max);
            info[X].min = min(info[X].min, info[Y].min);
            info[X].count += info[Y].count;
        }
    }
}

int main() {
    int n, i;
    char cmd[8];
    freopen("dsu.in",  "r", stdin);
    freopen("dsu.out", "w", stdout);
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        info[i].min = i;
        info[i].max = i;
        info[i].count = 1;
        info[i].rank = 0;
        p[i] = i;
    }
    while(1) {
        if(scanf("%s", cmd) == EOF) {
            break;
        }
        if(strcmp(cmd, "union") == 0) {
            int x, y;
            scanf("%d%d", &x, &y);
            Union(x, y);
        } else {
            int x;
            scanf("%d", &x);
            int X = Get(x);
            printf("%d %d %d\n", info[X].min, info[X].max, info[X].count);
        }
    }
    return 0;
}
