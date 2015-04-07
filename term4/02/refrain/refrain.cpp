#include <iostream>
#include <cstdio>
#include <map>
  
using namespace std;
  
int suf[150015];
int lcp[150015];
char str[150015];
int slen;
 
struct Node {
    int l, r;
    int depth;
    int parent;
    int suffLink;
    map<char, int> children;
  
    Node(int l = 0, int r = 0, int parent = -1) {
        this->l = l;
        this->r = r;
        this->parent = parent;
        this->depth = -1;
        this->suffLink = -1;
    }
  
    int length() {
        return r - l;
    }
 
    int &get(char c) {
        if (children.count(c) == 0) {
            children[c] = -1;
        }
        return children[c];
    }
};

struct triple {
    int64_t w;
    int id, h;

    triple() : w(0), id(0), h(0) {
    }

    triple(int64_t w, int id, int h) : w(w), id(id), h(h) {
    }
};
  
Node tree[300030];
int tlen;
  
struct State {
    int v, pos;
    State(int v, int pos) {
        this->v = v;
        this->pos = pos;
    }
};
  
State ptr(0, 0);
  
State go(State st, int l, int r) {
    while (l < r) {
        if (st.pos == tree[st.v].length()) {
            st = State(tree[st.v].get(str[l]), 0);
  
            if (st.v == -1) {
                return st;
            }
        } else {
            if (str[tree[st.v].l + st.pos] != str[l]) {
                return State(-1, -1);
            }
              
            if (r - l < tree[st.v].length() - st.pos) {
                return State(st.v, st.pos + r - l);
            }
              
            l += tree[st.v].length() - st.pos;
            st.pos = tree[st.v].length();
        }
    }
      
    return st;
}
 
int depth(int u) {
    if (u == -1) {
        return 0;
    } else if (tree[u].depth != -1) {
        return tree[u].depth;
    } else {
        return tree[u].depth = tree[u].length() + depth(tree[u].parent);
    }
}
  
int split(State st) {
    if (st.pos == tree[st.v].length()) {
        return st.v;
    }
  
    if (st.pos == 0) {
        return tree[st.v].parent;
    }
  
    Node v = tree[st.v];
    int id = tlen++;
    tree[id] = Node(v.l, v.l + st.pos, v.parent);
    tree[v.parent].get(str[v.l]) = id;
    tree[id].get(str[v.l + st.pos]) = st.v;
    tree[st.v].parent = id;
    tree[st.v].l += st.pos;
    depth(id);
    return id;
}
  
int getLink(int v) {
    if (tree[v].suffLink != -1) {
        return tree[v].suffLink;
    }
  
    if (tree[v].parent == -1) {
        return 0;
    }
  
    int to = getLink(tree[v].parent);
    return tree[v].suffLink = split(go(State(to, tree[to].length()), tree[v].l + (tree[v].parent == 0), tree[v].r));
}
  
void addPrefix(int pos) {
    while (true) {
        State nptr = go(ptr, pos, pos + 1);
  
        if (nptr.v != -1) {
            ptr = nptr;
            return;
        }
  
        int mid = split(ptr);
        int leaf = tlen++;
        tree[leaf] = Node(pos, slen, mid);
        tree[mid].get(str[pos]) = leaf;
        ptr.v = getLink(mid);
        ptr.pos = tree[ptr.v].length();
        depth(leaf);
          
        if (mid == 0) {
            break;
        }
    }
}
  
void buildTree() {
    tlen = 1;
    for (int i = 0; i < slen; i++) {
        addPrefix(i);
    }
}
 
int pos = 0;
int minNode = 0;

int dfs_stack[300030];

void dfs(int start) {
    int st = 0;
    dfs_stack[st++] = start;
    while (st != 0) {
        int u = dfs_stack[--st];
        if (u != 0) {
            int v = tree[u].parent;
            if (depth(v) < depth(minNode)) {
                minNode = v;
            }
        }
        if (tree[u].children.size() == 0) {
            suf[pos] = slen - depth(u);
            lcp[pos] = depth(minNode);
            pos++;
            minNode = u;
        } else {
            for (map<char, int>::reverse_iterator it = tree[u].children.rbegin(); it != tree[u].children.rend(); it++) {
                int v = it->second;
                dfs_stack[st++] = v;
            }
        }
    }
}

triple stack[300030];
  
int main() {
    freopen("refrain.in", "r", stdin);
    freopen("refrain.out", "w", stdout);

    int moosor;
    cin >> slen >> moosor;
    
    for (int i = 0; i < slen; i++) {
        int num;
        cin >> num;
        str[i] = '0' + num;
    }
    str[slen++] = '$';
  
    buildTree();
     
    dfs(0);

    lcp[slen] = 0;
    int maxH = slen - 1;
    int64_t maxW = 1;
    int st = 0;
    int start = 0;

    for (int i = 1; i <= slen; i++) {
        int64_t x = 1;

        while (st != 0 && lcp[i] <= stack[st - 1].h) {
            triple t = stack[--st];
            x += t.w;

            if (x * t.h > maxW * maxH) {
                maxW = x;
                maxH = t.h;
                start = suf[t.id];
            }
        }

        if (st == 0 || lcp[i] > stack[st - 1].h) {
            stack[st++] = triple(x, i, lcp[i]);
        }
    }

    cout << maxW * maxH << endl;
    cout << maxH << endl;
    for (int i = 0; i < maxH; i++) {
        cout << (int) (str[start + i] - '0') << ' ';
    }
    cout << endl;
  
    return 0;
}
