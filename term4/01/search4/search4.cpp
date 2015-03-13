#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int ALPHABET_SIZE = 26;

struct State {
    int next_trie[ALPHABET_SIZE];
    int next_auto[ALPHABET_SIZE];
    int parent;
    int suff_link;
    int up;
    char edge_char;
    vector<int> patterns;
};

State S[1000005];
char pat_buf[1000005];
char text[1000005];
bool found[1000005];
int last_state;

void init(State & s, int p, char c) {
    memset(s.next_trie, 255, ALPHABET_SIZE * sizeof(int));
    memset(s.next_auto, 255, ALPHABET_SIZE * sizeof(int));
    if (p != -1) {
        S[p].next_trie[c] = last_state;
    }
    s.parent = p;
    s.suff_link = -1;
    s.up = -1;
    s.edge_char = c;
    last_state++;
}

void add_pattern(int pattern_id) {
    int p = 0;
    int n = strlen(pat_buf);
    
    for (int i = 0; i < n; i++) {
        char c = pat_buf[i] - 'a';

        if (S[p].next_trie[c] == -1) {
            init(S[last_state], p, c);
        }

        p = S[p].next_trie[c];
    }

    S[p].patterns.push_back(pattern_id);
}

int get_auto(int p, char c);

int get_link(int p) {
    if (S[p].suff_link == -1) {
        if (p == 0 || S[p].parent == 0) {
            S[p].suff_link = 0;
        } else {
            S[p].suff_link = get_auto(get_link(S[p].parent), S[p].edge_char);
        }
    }

    return S[p].suff_link;
}

int get_auto(int p, char c) {
    if (S[p].next_auto[c] == -1) {
        if (S[p].next_trie[c] != -1) {
            S[p].next_auto[c] = S[p].next_trie[c];
        } else if (p == 0) {
            S[p].next_auto[c] = 0;
        } else {
            S[p].next_auto[c] = get_auto(get_link(p), c);
        }
    }

    return S[p].next_auto[c];
}

int get_up(int p) {
    if (S[p].up == -1) {
        int u = get_link(p);
        if (u == 0) {
            S[p].up = 0;
        } else if (S[u].patterns.size() != 0) {
            S[p].up = u;
        } else {
            S[p].up = get_up(u);
        }
    }

    return S[p].up;
}

int main() {
    freopen("search4.in",  "r", stdin);
    freopen("search4.out", "w", stdout);

    last_state = 0;
    init(S[0], -1, -'a');

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", pat_buf);
        add_pattern(i);
    }

    int tlen;
    scanf("%s", text);
    tlen = strlen(text);

    int p = 0;
    for (int i = 0; i < tlen; i++) {
        char c = text[i] - 'a';
        p = get_auto(p, c);
        for (int pp = p; pp != 0; pp = get_up(pp)) {
            for (int j = 0; j < S[pp].patterns.size(); j++) {
                int index = S[pp].patterns[j];
                if (found[index]) {
                    goto next_char;
                } else {
                    found[index] = true;
                }
            }
        }
        next_char:
        continue;
    }

    for (int i = 0; i < n; i++) {
        printf(found[i] ? "YES\n" : "NO\n");
    }

    return 0;
}
