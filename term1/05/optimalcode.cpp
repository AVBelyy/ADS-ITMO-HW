#include <algorithm>
#include <stdint.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <list>

const int64_t INF = 1E16;

using namespace std;

class Leaf
{
    public:
    int f;
    bool original;
    int d;
    Leaf *c1;
    Leaf *c2;
    Leaf() {}
    Leaf(int f_): f(f_), original(false), c1(NULL), c2(NULL) {}
};

list<Leaf*> L1, L2, L3;
uint64_t ans = 0;

void W1(Leaf *l, int depth)
{
    l->d = depth;
    if(l->c1 != NULL)
    {
        W1(l->c1, depth + 1);
        W1(l->c2, depth + 1);
    } else {
        ans += l->f * depth;
    }
}

void W2(Leaf *l, string code)
{
    if(l->c1 != NULL)
    {
        W2(l->c1, code + "0");
        W2(l->c2, code + "1");
    } else {
        cout << code << endl;
    }
}

int main()
{
    int n;
    freopen("optimalcode.in",  "r", stdin);
    freopen("optimalcode.out", "w", stdout);
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        int f;
        cin >> f;
        Leaf *leaf = new Leaf(f);
        leaf->original = true;
        L1.push_back(leaf);
        L2.push_back(leaf);
    }
    if(n == 1)
    {
        cout << (*L1.begin())->f << endl;
        cout << 0 << endl;
        return 0;
    }
    list<Leaf*>::iterator begin = L1.begin();
    for(int i = 0; i < n - 1; i++)
    {
        // extract the minimal compatible pair
        list<Leaf*>::iterator it, mint, mint2, aaa, bbb, end = L1.end();
        int64_t t, min = INF;
        for(it = begin; it != end; it++)
        {
            aaa = it;
            aaa++;
            int64_t T = (*it)->f;
            for(; aaa != end; aaa++)
            {
                t = T + (*aaa)->f;
                if(min > t)
                {
                    min = t;
                    mint = it;
                    mint2 = aaa;
                }
                if((*aaa)->original) break;
            }
        }
        // and create a new leaf
        Leaf *new_leaf = new Leaf(min);
        new_leaf->c1 = *mint;
        new_leaf->c2 = *mint2;
        *mint = new_leaf;
        L1.erase(mint2);
    }
    // Computing leaf depths
    W1(*L1.begin(), 0);
    // Rebuilding tree
    list<Leaf*>::iterator aaa;
    for(;;)
    {
        aaa = L3.begin();
        aaa++;
        if(L3.size() < 2 || (*L3.begin())->d != (*aaa)->d)
        {
            L3.push_front(L2.front());
            L2.pop_front();
        } else {
            Leaf *new_leaf = new Leaf;
            new_leaf->c2 = L3.front();
            L3.pop_front();
            new_leaf->c1 = L3.front();
            L3.pop_front();
            new_leaf->d = new_leaf->c1->d - 1;
            L3.push_front(new_leaf);
            if(new_leaf->d == 0 && L3.size() == 1)
            {
                break;
            }
        }
    }
    cout << ans << endl;
    W2(*L3.begin(), "");
    return 0;
}
