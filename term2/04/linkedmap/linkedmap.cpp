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

struct Node {
    Value value;
    Node  *prev;
    Node  *next;
};

typedef pair<Key, Node*> Pair;
typedef list<Pair> HashTable;

HashTable hashtable[MOD];

Node *head = NULL, *tail = NULL;

string none = "none";

int hasher(const string key) {
    int res = 0, len = key.size();
    for (int i = 0; i < len; i++) {
        res = (res + (key[i] - 'A' + 1) * i) % MOD;
    }
    return res;
}

void put(Key key, Value value) {
    int x = hasher(key);
    HashTable &bucket = hashtable[x];
    for (HashTable::iterator it = bucket.begin(); it != bucket.end(); it++) {
        if (it->first == key) {
            it->second->value = value;
            return;
        }
    }
    Node *node = new Node;
    node->prev = tail;
    node->next = NULL;
    node->value = value;
    if (tail != NULL) {
        tail->next = node;
    }
    tail = node;
    if (head == NULL) {
        head = node;
    }
    bucket.push_back(Pair(key, node));
}

void remove(Key key) {
    int x = hasher(key);
    HashTable &bucket = hashtable[x];
    for (HashTable::iterator it = bucket.begin(); it != bucket.end(); it++) {
        if (it->first == key) {
            Node *node = it->second;
            if (head != node && tail != node) {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
            if (head == node) {
                head = head->next;
                if (head != NULL) {
                    head->prev = NULL;
                }
            }
            if (tail == node) {
                tail = tail->prev;
                if (tail != NULL) {
                    tail->next = NULL;
                }
            }
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
            return it->second->value;
        }
    }
    return none;
}

Value &prev(const Key key) {
    int x = hasher(key);
    HashTable &bucket = hashtable[x];
    for (HashTable::iterator it = bucket.begin(); it != bucket.end(); it++) {
        if (it->first == key) {
            return it->second->prev ? it->second->prev->value : none;
        }
    }
    return none;
}

Value &next(const Key key) {
    int x = hasher(key);
    HashTable &bucket = hashtable[x];
    for (HashTable::iterator it = bucket.begin(); it != bucket.end(); it++) {
        if (it->first == key) {
            return it->second->next ? it->second->next->value : none;
        }
    }
    return none;
}

int main() {
    string cmd, k, v;
    int x;
    freopen("linkedmap.in",  "r", stdin);
    freopen("linkedmap.out", "w", stdout);
    while (true) {
        cin >> cmd >> k;
        if (feof(stdin)) break;
        switch(cmd[0] + cmd[1]) {
            case 'p' + 'u':
                cin >> v;
                put(k, v);
                break;
            case 'd' + 'e':
                remove(k);
                break;
            case 'g' + 'e':
                cout << get(k) << endl;
                break;
            case 'p' + 'r':
                cout << prev(k) << endl;
                break;
            case 'n' + 'e':
                cout << next(k) << endl;
                break;
        }
    }
    return 0;
}
