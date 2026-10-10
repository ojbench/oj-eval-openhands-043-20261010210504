#include <bits/stdc++.h>
using namespace std;

namespace LIST {
    struct NODE {
        int data;
        NODE *prev;
        NODE *next;
    };
    NODE *head = nullptr, *tail = nullptr;
    int len = 0;

    void Pre() {
        head = tail = nullptr;
        len = 0;
    }
    // Return pointer to node at index i (0-based). Assumes i is valid (0 <= i < len).
    NODE* move(int i) {
        if (i < 0 || i >= len) return nullptr;
        NODE *cur;
        if (i < len/2) {
            cur = head;
            for (int k = 0; k < i; ++k) cur = cur->next;
        } else {
            cur = tail;
            for (int k = len-1; k > i; --k) cur = cur->prev;
        }
        return cur;
    }
    void insert(int i, int x) {
        // i can be equal to len (insert at end)
        NODE *node = new NODE{ x, nullptr, nullptr };
        if (len == 0) {
            head = tail = node;
        } else if (i == 0) {
            node->next = head;
            head->prev = node;
            head = node;
        } else if (i == len) {
            node->prev = tail;
            tail->next = node;
            tail = node;
        } else {
            NODE *cur = move(i);
            NODE *prevNode = cur->prev;
            node->prev = prevNode;
            node->next = cur;
            prevNode->next = node;
            cur->prev = node;
        }
        ++len;
    }
    void remove(int i) {
        if (len == 0) return; // should not happen per problem guarantees
        NODE *cur = move(i);
        if (!cur) return;
        if (cur == head && cur == tail) {
            head = tail = nullptr;
        } else if (cur == head) {
            head = cur->next;
            head->prev = nullptr;
        } else if (cur == tail) {
            tail = cur->prev;
            tail->next = nullptr;
        } else {
            NODE *p = cur->prev;
            NODE *n = cur->next;
            p->next = n;
            n->prev = p;
        }
        delete cur;
        --len;
    }
    int Get_length() {
        return len;
    }
    int Query(int i) {
        if (i < 0 || i >= len) return -1;
        NODE *cur = move(i);
        return cur ? cur->data : -1;
    }
    void Print() {
        if (len == 0) {
            cout << -1 << '\n';
            return;
        }
        NODE *cur = head;
        while (cur) {
            cout << cur->data;
            if (cur->next) cout << ' ';
            cur = cur->next;
        }
        cout << '\n';
    }
    void Clear() {
        NODE *cur = head;
        while (cur) {
            NODE *nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = tail = nullptr;
        len = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    LIST::Pre();
    for (int _ = 0; _ < n; ++_) {
        int op;
        cin >> op;
        if (op == 0) {
            cout << LIST::Get_length() << '\n';
        } else if (op == 1) {
            int p, x;
            cin >> p >> x;
            LIST::insert(p, x);
        } else if (op == 2) {
            int p;
            cin >> p;
            cout << LIST::Query(p) << '\n';
        } else if (op == 3) {
            int p;
            cin >> p;
            LIST::remove(p);
        } else if (op == 4) {
            LIST::Print();
        }
    }
    LIST::Clear();
    return 0;
}
