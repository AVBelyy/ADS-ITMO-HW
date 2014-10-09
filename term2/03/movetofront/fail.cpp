
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <utility>
 
using namespace std;
 
#define getSize(t) ((t) != NULL ? (t)->size : 0)
 
class Treap {
    public:
        int priority;
        int cost;
        int size;
        Treap *parent;
        Treap *left;
        Treap *right;
 
        Treap(int);
        static Treap *merge(Treap*, Treap*);
        static pair<Treap*, Treap*> split(Treap*, int, int);
};
 
Treap::Treap(int cost) {
    this->cost = cost;
    this->priority = rand();
    this->size = 1;
}
 
Treap *Treap::merge(Treap *t1, Treap *t2) {
    Treap *t;
    if (!t1 || !t2) {
        t = t1 ? t1 : t2;
    } else if (t1->priority > t2->priority) {
        t1->right = merge(t1->right, t2);
        t = t1;
    } else {
        t2->left = merge(t1, t2->left);
        t = t2;
    }
    t->size = getSize(t->left) + getSize(t->right) + 1;
    return t;
}
 
pair<Treap*, Treap*> Treap::split(Treap *t, int key, int add = 0) {
    Treap *t1 = NULL, *t2 = NULL;
    if (t != NULL) {
        int curKey = add + getSize(t->left);
        if (key <= curKey) {
            pair<Treap*, Treap*> p = split(t->left, key, add);
            t1 = p.first;
            t->left = p.second;
            t2 = t;
        } else {
            pair<Treap*, Treap*> p = split(t->right, key, add + getSize(t->left) + 1);
            t->right = p.first;
            t2 = p.second;
            t1 = t;
        }
        t->size = getSize(t->left) + getSize(t->right) + 1;
    }
    return pair<Treap*, Treap*>(t1, t2);
}
 
int main() {
    int n, a, m, b;
    srand(time(NULL));
 
    freopen("movetofront.in",  "r", stdin);
    freopen("movetofront.out", "w", stdout);
     
    scanf("%d%d", &n, &m);
     
    Treap *t = new Treap(1);
    for (int i = 2; i <= n; i++) {
        t = Treap::merge(t, new Treap(i));
    }
 
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        pair<Treap*, Treap*> p1 = Treap::split(t, a - 1);
        pair<Treap*, Treap*> p2 = Treap::split(p1.second, b - a + 1);
        Treap *ptr = p1.second;
        while (ptr->right != NULL) ptr = ptr->right;
        t = Treap::merge(p2.first, p1.first);
        t = Treap::merge(t, p2.second);
    }
 
    for (int i = 0; i < n; i++) {
        pair<Treap*, Treap*> p = Treap::split(t, 1);
        printf("%d ", p.first->cost);
        t = p.second;
    }
    printf("\n");
    return 0;
}
