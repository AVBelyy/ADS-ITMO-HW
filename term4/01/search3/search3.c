#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char p[1000001];
char t[1000001];
char zbuf[2000002];
int z1[2000001];
int z2[2000001];
int plen, tlen, anslen;
int ans[1000001];

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

void z(int * z) {
    int left = 0;
    int right = 0;
    int n = plen + tlen + 1;
    int i;
    for (i = 1; i < n; i++) {
        z[i] = max(0, min(right - i, z[i - left]));
        while (i + z[i] < n && zbuf[z[i]] == zbuf[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] >= right) {
            left = i;
            right = i + z[i];
        }
    }
}

void strrev(char * s, int l) {
    int i;
    for (i = 0; i < l / 2; i++) {
        char t = s[i];
        s[i] = s[l - i - 1];
        s[l - i - 1] = t;
    }
}

int main() {
    freopen("search3.in",  "r", stdin);
    freopen("search3.out", "w", stdout);

    scanf("%s", p);
    scanf("%s", t);
    plen = strlen(p);
    tlen = strlen(t);
    anslen = 0;

    // calculate z of P#T
    memcpy(zbuf, p, plen);
    zbuf[plen] = '#';
    memcpy(zbuf + plen + 1, t, tlen);
    z(z1);

    // calculate z of rev(P)#rev(T)
    strrev(zbuf, plen);
    strrev(zbuf + plen + 1, tlen);
    z(z2);

    // calculate positions
    int i;
    for (i = 0; i <= tlen - plen; i++) {
        int i1 = plen + i + 1;
        int i2 = tlen - i + 1;
        int zf = z1[i1] + z2[i2];
        if (z1[i1] == plen) {
            ans[anslen++] = i;
        } else if (zf == plen - 1) {
            ans[anslen++] = i;
        }
    }

    // output positions
    printf("%d\n", anslen);
    for (i = 0; i < anslen; i++) {
        printf("%d ", ans[i] + 1);
    }
    printf("\n");
    return 0;
}
