#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

struct Node {
    map<char, int> next;
};

Node trie[10010];
char str_buf[105];
int n;
int edge_cnt;
int last_node;

void add_string(int l) {
    int p = 0;

    for (int i = l; i < n; i++) {
        char c = str_buf[i];

        if (trie[p].next.count(c) == 0) {
            edge_cnt++;
            trie[p].next[c] = last_node++;
        }

        p = trie[p].next[c];
    }
}

void dfs(int u) {
    for (pair<char, int> kv : trie[u].next) {
        printf("%d %d %c\n", u + 1, kv.second + 1, kv.first);
        dfs(kv.second);
    }
}

int main() {
    freopen("trie.in", "r", stdin);
    freopen("trie.out", "w", stdout);
    
    edge_cnt = 0;
    last_node = 1;
    
    scanf("%s", str_buf);
    n = strlen(str_buf);

    for (int i = 0; i < n; i++) {
        add_string(i);
    }

    printf("%d %d\n", edge_cnt + 1, edge_cnt);
    dfs(0);
    return 0;
}
