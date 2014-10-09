#include <iostream>
#include <cstdio>

// just playing around, don't mind this solution.

char set[250000001];

int main() {
    freopen("set.in",  "r", stdin);
    freopen("set.out", "w", stdout);
    char cmd[8];
    int x, i;
    while(true) {
        scanf("%s%d", cmd, &x);
        if (feof(stdin)) break;
        x += 1e9;
        int a = x / 8, b = x % 8;
        switch(cmd[0]) {
            case 'i':
                set[a] |= (1<<b);
                break;
            case 'd':
                set[a] &= ~(1<<b);
                break;
            case 'e':
                printf(set[a] & (1<<b) ? "true\n" : "false\n");
        }
    }
    return 0;
}
