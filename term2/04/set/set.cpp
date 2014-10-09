#include <iostream>
#include <list>
#include <algorithm>
#include <cstdio>
 
const int MOD = 10000;
 
using namespace std;
 
list<int> hashtable[MOD];
 
void insert(int x) {
    list<int> &bucket = hashtable[x % MOD];
    if(find(bucket.begin(), bucket.end(), x) == bucket.end()) {
        bucket.push_back(x);
    }
}
 
void remove(int x) {
    list<int> &bucket = hashtable[x % MOD];
    list<int>::iterator iter = find(bucket.begin(), bucket.end(), x);
    if(iter != bucket.end()) {
        bucket.erase(iter);
    }
}
 
bool exists(int x) {
    list<int> &bucket = hashtable[x % MOD];
    return find(bucket.begin(), bucket.end(), x) != bucket.end();
}
 
int main() {
    char cmd[8];
    int x;
    freopen("set.in",  "r", stdin);
    freopen("set.out", "w", stdout);
    while(scanf("%s%d", cmd, &x) != EOF) {
        switch(cmd[0]) {
            case 'i':
                insert(x + 1e9);
                break;
            case 'd':
                remove(x + 1e9);
                break;
            case 'e':
                printf(exists(x + 1e9) ? "true\n" : "false\n");
                break;
        }
    }
    return 0;
}
