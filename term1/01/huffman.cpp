#include <iostream>
#include <list>
#include <string>
#include <algorithm>

#include <stdint.h>

using namespace std;

#define k 2

class Node {
    public:
    list<Node*> children;
    int id;
    uint64_t freq;
    Node(list<Node*> c, int i, uint64_t f) : children(c), id(i), freq(f) {}
    static bool compare(Node *a, Node *b)
    {
        return a->freq < b->freq;
    }
};

list<Node*> N;
uint64_t F[1000];
uint64_t L[1000];

void walk(Node *n, int d) {
    if(n->children.size() == 0)
    {
        // terminal node
        L[n->id] = d;
    } else {
        for(list<Node*>::iterator it = n->children.begin(); it != n->children.end(); it++)
        {
            walk(*it, d + 1);
        }
    }
}

int main() {
    int n, i;
    uint64_t ans = 0;
    freopen("huffman.in",  "r", stdin);
    freopen("huffman.out", "w", stdout);
    cin >> n;
    // create nodes
    for(i = 0; i < n; i++)
    {
        uint64_t freq;
        cin >> freq;
        Node *n = new Node(list<Node*>(), i, freq);
        F[i] = freq;
        N.push_back(n);
    }
    // build the tree
    while(N.size() > 1)
    {
        list<Node*>::iterator ms[k];
        uint64_t freq = 0;
        list<Node*> ns;
        for(i = 0; i < k; i++)
        {
            ms[i] = min_element(N.begin(), N.end(), Node::compare);
            if(ms[i] == N.end()) break; 
            ns.push_back(*ms[i]);
            freq += (*ms[i])->freq;
            N.erase(ms[i]);
        }
        Node *n = new Node(ns, -1, freq);
        N.push_back(n);
    }
    // walk the tree
    walk(N.front(), 0);
    for(int i = 0; i < n; i++)
    {
        ans += F[i] * L[i];
    }
    cout << ans << endl;
    return 0;
}
