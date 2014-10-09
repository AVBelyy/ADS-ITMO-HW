#include <iostream>
#include <list>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <string>
 
const int MOD = 509;
 
using namespace std;
 
typedef string Key;
typedef string Value;
typedef list<Value> HashTable;
 
typedef struct { HashTable x[MOD]; } HashMap;
 
typedef pair<Key, HashMap> MultiPair;
typedef list<MultiPair> MultiHashTable;
 
 
MultiHashTable multihashtable[MOD];
int P[] = {1,      59,      3481,   205379, 687068,  1347436, 1119572, 738788, 1133118, 1538002,
           932673, 1142040, 431501, 965074, 1420800, 549351,  1386628, 166102, 2624,    154816};
 
int hasher(const string key) {
    int res = 0, len = key.size();
    for (int i = 0; i < len; i++) {
        res = (res + (key[i] - 'A' + 1) * P[i]) % MOD;
    }
    return res;
}
 
void put(HashMap &hashtable, Value value) {
    int x = hasher(value);
    HashTable &bucket = hashtable.x[x];
    for (HashTable::iterator it = bucket.begin(); it != bucket.end(); it++) {
        if (*it == value) {
            return;
        }
    }
    bucket.push_back(value);
}
 
void multiput(Key multikey, Value value) {
    int x = hasher(multikey);
    MultiHashTable &multibucket = multihashtable[x];
    for (MultiHashTable::iterator it = multibucket.begin(); it != multibucket.end(); it++) {
        if (it->first == multikey) {
            put(it->second, value);
            return;
        }
    }
    MultiPair pair;
    pair.first = multikey;
    put(pair.second, value);
    multibucket.push_back(pair);
}
 
void remove(HashMap &hashtable, Value value) {
    int x = hasher(value);
    HashTable &bucket = hashtable.x[x];
    for (HashTable::iterator it = bucket.begin(); it != bucket.end(); it++) {
        if (*it == value) {
            bucket.erase(it);
            return;
        }
    }
}
 
void multiremove(Key multikey, Value value) {
    int multix = hasher(multikey);
    MultiHashTable &multibucket = multihashtable[multix];
    for (MultiHashTable::iterator it = multibucket.begin(); it != multibucket.end(); it++) {
        if (it->first == multikey) {
            remove(it->second, value);
            return;
        }
    }
}
 
void multiremoveall(Key multikey) {
    int multix = hasher(multikey);
    MultiHashTable &multibucket = multihashtable[multix];
    for (MultiHashTable::iterator it = multibucket.begin(); it != multibucket.end(); it++) {
        if (it->first == multikey) {
            multibucket.erase(it);
            return;
        }
    }
}
 
void multiget(const Key multikey) {
    int multix = hasher(multikey);
    MultiHashTable &multibucket = multihashtable[multix];
    for (MultiHashTable::iterator it = multibucket.begin(); it != multibucket.end(); it++) {
        if (it->first == multikey) {
            list<Value> ans;
            HashMap &hashmap = it->second;
            for (int i = 0; i < MOD; i++) {
                HashTable &bucket = hashmap.x[i];
                for (HashTable::iterator it = bucket.begin(); it != bucket.end(); it++) {
                    ans.push_back(*it);
                }
            }
            printf("%d", (int)ans.size());
            for (list<Value>::iterator it = ans.begin(); it != ans.end(); it++) {
                printf(" %s", it->c_str());
            }
            putchar('\n');
            return;
        }
    }
    printf("0\n");
}
 
int main() {
    string cmd, x, y;
    freopen("multimap.in",  "r", stdin);
    freopen("multimap.out", "w", stdout);
    while (true) {
        cin >> cmd >> x;
        if (feof(stdin)) break;
        switch(cmd[0]) {
            case 'p':
                cin >> y;
                multiput(x, y);
                break;
            case 'd':
                if (cmd == "delete") {
                    cin >> y;
                    multiremove(x, y);
                } else {
                    multiremoveall(x);
                }
                break;
            case 'g':
                multiget(x);
                break;
        }
    }
    return 0;
}
