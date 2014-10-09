#include <iostream>
#include <list>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <string>

const int MOD = 100;

using namespace std;

typedef string Key;
typedef string Value;
typedef pair<Key, Value> Pair;
typedef list<Pair> HashTable;

HashTable hashtable[MOD];

string none = "none";

int hasher(const string key) {
    int res = 0, len = key.size();
    for (int i = 0; i < len; i++) {
        res = (res + (key[i] - 'A' + 1) * (i + 1)) % MOD;
    }
    return res;
}

void put(Key key, Value value) {
    int x = hasher(key);
    HashTable &bucket = hashtable[x];
    for (HashTable::iterator it = bucket.begin(); it != bucket.end(); it++) {
        if (it->first == key) {
            it->second = value;
            return;
        }
    }
    bucket.push_back(Pair(key, value));
}

void remove(Key key) {
    int x = hasher(key);
    HashTable &bucket = hashtable[x];
    for (HashTable::iterator it = bucket.begin(); it != bucket.end(); it++) {
        if (it->first == key) {
            bucket.erase(it);
            return;
        }
    }
}

Value &get(const Key key) {
    int x = hasher(key);
    HashTable &bucket = hashtable[x];
    for (HashTable::iterator it = bucket.begin(); it != bucket.end(); it++) {
        if (it->first == key) {
            return it->second;
        }
    }
    return none;
}

int main() {
    string cmd, k, v;
    int x;
    freopen("map.in",  "r", stdin);
    freopen("map.out", "w", stdout);
    while (true) {
        cin >> cmd >> k;
        if (feof(stdin)) break;
        switch(cmd[0]) {
            case 'p':
                cin >> v;
                put(k, v);
                break;
            case 'd':
                remove(k);
                break;
            case 'g':
                cout << get(k) << endl;
                break;
        }
    }
    return 0;
}
