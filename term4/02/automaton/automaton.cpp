#include <cstring>
#include <cstdio>
#include <map>

using namespace std;

struct state {
    int len;
    int suffLink;
    map<char, int> children;
};

char s[100010];
state st[200010];

int vcount;
int ecount;
int last;

void init() {
    vcount = 1;
    last = 0;
    st[0].len = 0; // empty string
    st[0].suffLink = -1;
}

void append(char c) {
    int cur = vcount++;
    int par;

    st[cur].len = st[last].len + 1;

    // find first state that has 'c' edge
    for (par = last; par != -1 && st[par].children.count(c) == 0; par = st[par].suffLink) {
        ecount++;
        st[par].children[c] = cur;
    }

    // if we reached initial state, point cur.suffLink to it
    if (par == -1) {
        st[cur].suffLink = 0;
    } else {
        int q = st[par].children[c];

        if (st[par].len + 1 == st[q].len) {
            // simply point cur.suffLink to q
            st[cur].suffLink = q;
        } else {
            // create auxiliary state clone and point both q and cur suffLink to it
            // deep copy q into clone
            int clone = vcount++;
            st[clone].len = st[par].len + 1;
            ecount += st[q].children.size();
            st[clone].children = st[q].children;
            st[clone].suffLink = st[q].suffLink;

            while (par != -1 && st[par].children[c] == q) {
                st[par].children[c] = clone;
                par = st[par].suffLink;
            }

            st[q].suffLink = clone;
            st[cur].suffLink = clone;
        }
    }

    last = cur;
}

int stack[200010];

void out_states() {
    for (int u = 0; u < vcount; u++) {
        for (map<char, int>::iterator it = st[u].children.begin(); it != st[u].children.end(); it++) {
            char c = it->first;
            int v = it->second;

            printf("%d %d %c\n", u + 1, v + 1, c);
        }
    }
}

int terminals[100010];
int term_cnt;

void find_terminal_states() {
    for (int p = last; p != -1; p = st[p].suffLink) {
        terminals[term_cnt++] = p;
    }
}

int main() {
    freopen("automaton.in",  "r", stdin);
    freopen("automaton.out", "w", stdout);

    scanf("%s", s);
    int n = strlen(s);

    init();
    for (int i = 0; i < n; i++) {
        append(s[i]);
    }

    printf("%d %d\n", vcount, ecount);

    out_states();
    
    find_terminal_states();

    printf("%d\n", term_cnt);
    for (int i = 0; i < term_cnt; i++) {
        printf("%d ", terminals[i] + 1);
    }
    printf("\n");

    return 0;
}
