#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

char p[1000010];
char t[1000010];
int ans[1000010];
int plen, tlen;

vector<int> matches;

void z() {
    int left = 0;
    int right = 0;
    int n = plen + tlen + 1;
    for (int i = 1; i <= plen; i++) {
        ans[i] = max(0, min(right - i, ans[i - left]));
        while (i + ans[i] < n && p[ans[i]] == p[i + ans[i]]) {
            ans[i]++;
        }
        if (i + ans[i] >= right) {
            left = i;
            right = i + ans[i];
        }
    }
    for (int i = plen + 1; i <= plen + tlen; i++) {
        int zval = max(0, min(right - i, ans[i - left]));
        while (i + zval < n && p[zval] == t[i + zval - plen - 1]) {
            zval++;
        }
        if (i + zval >= right) {
            left = i;
            right = i + zval;
        }
        if (zval == plen) {
            matches.push_back(i - plen - 1);
        }
    }
}

int main() {
    freopen("search2.in",  "r", stdin);
    freopen("search2.out", "w", stdout);

    scanf("%s", p);
    scanf("%s", t);
    plen = strlen(p);
    tlen = strlen(t);
    p[plen] = '#';
    z();

    printf("%d\n", (int) matches.size());
    for (int i = 0; i < matches.size(); i++) {
        printf("%d ", matches[i] + 1);
    }
    printf("\n");
    return 0;
}
