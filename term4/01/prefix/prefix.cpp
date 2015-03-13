#include <cstdio>
#include <cstring>

int n;
int p[1000010];
char s[1000010];

void prefix() {
    int i = 2;
    for (; i <= n; i++) {
        int k = p[i - 1];
        while (k > 0 && s[i - 1] != s[k]) {
            k = p[k];
        }
        if (s[i - 1] == s[k]) {
            k++;
        }
        p[i] = k;
    }
}

int main() {
    freopen("prefix.in", "r", stdin);
    freopen("prefix.out", "w", stdout);

    scanf("%s", s);
    n = strlen(s);
    
    prefix();

    int i = 1;
    for (; i <= n; i++) {
        printf("%d ", p[i]);
    }
    printf("\n");
}
