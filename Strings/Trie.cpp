#include <bits/stdc++.h>
using namespace std;


const int SZ = 26;
char INIT = 'a';
struct Trie { //init->Trie T
    struct Node {
        int wordCnt = 0, cnt = 0;
        array<unique_ptr<Node>,SZ> next{};
    };
    unique_ptr<Node> root = make_unique<Node>();
    void insert(const string &s) {
        Node* curr = root.get();
        for (char c : s) {
            int id = c - INIT;
            if (!curr->next[id])
                curr->next[id] = make_unique<Node>();
            curr = curr->next[id].get();
            curr->cnt++;
        }
        curr->wordCnt++;
    }
    void erase(const string &s) {
        if(!search(s))return;
        Node* curr = root.get();
        for (char c : s) {
            int id = c - INIT;
            curr = curr->next[id].get();
            curr->cnt--;
        }
        curr->wordCnt--;
    }
    bool search(const string &s) {
        Node* curr = root.get();
        for (char c : s) {
            int id = c - INIT;
            if (!curr->next[id]) return false;
            curr = curr->next[id].get();
        }
        return curr->wordCnt > 0;
    }
};
