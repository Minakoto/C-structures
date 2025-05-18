#include <malloc.h>
#include <iostream>
using namespace std;

template <class T>
class Btree {
friend class Iterator;
friend class Rev_Iterator;
friend class Node;
private:
    class Node {
        public:
            long key;
            T data;
            Node* left;
            Node* right;
            Node() : data(nullptr), key(0), left(nullptr), right(nullptr) {}
            Node(T val, long k) : data(val), key(k), left(nullptr), right(nullptr) {}
            long get_key() {return this->key;}
    };
    Node* root;

    Node* cpy(Node* other) {
        if(other == nullptr) 
            return nullptr;
        Node* new_n = new Node(other->data, other->key);
        new_n->left = cpy(other->left);
        new_n->right = cpy(other->right);

        return new_n;
    }
    void list_sub(Node* node) {
        if(!node) return;
        list_sub(node->left);
        cout << "[" << node->key << "] " << " ";
        list_sub(node->right);
    }
    int cnt(Node* node) {
        if(node == nullptr) return 0;
        return 1 + cnt(node->left) + cnt(node->right);
    }
public:
    Btree() {
        root = NULL;
    }
    Btree(Btree<T>& other) : root(nullptr) {
        root = cpy(other.root);
    }
    ~Btree() {
        clear(root);
    }
    void clear(Node* node) {
        if(node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete(node);
        }
    }
    int get_size() {
        return cnt(root);
    }
    bool is_empty() {
        return root == NULL;
    }
    // throws exception
    void write(long key, T val) {
        Node* tmp = root;
        while(tmp != nullptr && key != tmp->key) {
            if(key < tmp->key) tmp = tmp->left;
            else tmp = tmp->right;
        }
        if(tmp == nullptr) throw "Not found exception";
        tmp->data = val;
    }
    // throws exception
    T read(long key) {
        Node* tmp = root;
        while(!tmp && key != tmp->key) {
            if(key < tmp->key) tmp = tmp->left;
            else tmp = tmp->right;
        }
        if(tmp == nullptr) throw "Not found exception";
        return tmp->data;
    }
    bool add(long key, T data) {
        if(root == nullptr) {
            root = new Node(data, key);
            return true;
        }
        Node* tmp = root;
        Node* prev = tmp;
        while(tmp != nullptr) {
            prev = tmp;
            if(key == tmp->key) return false;
            if(key < tmp->key) tmp = tmp->left;
            else tmp = tmp->right;
        }
        if(key < prev->key) prev->left = new Node(data, key);
        else prev->right = new Node(data, key);
        return true;
    }
    bool del(long key) {
        Node* cur = root;
        Node* par = nullptr;
        while(cur != nullptr && cur->key != key) {
            par = cur;
            if(key < cur->key) cur = cur->left;
            else cur = cur->right;
        }
        if(cur == nullptr) return false;
        if(cur->left == nullptr && cur->right == nullptr) {
            if(par == nullptr) root = nullptr;
            else if(par->left == cur) par->left = nullptr;
            else par->right = nullptr;
            delete cur;
        }
        else if (cur->left == nullptr || cur->right == nullptr) {
            Node* child = (cur->left != nullptr) ? cur->left : cur->right;
            if(par == nullptr) root = child;
            else if(par->left == cur) par->left = child;
            else par->right = child;
            delete cur;
        }
        else {
            Node* next = cur->right;
            if(next->left == nullptr) {
                cur->key = next->key;
                cur->data = next->data;
                cur->right = next->right;
            }
            else{
                while(next->left != nullptr) {
                    par = next;
                    next = next->left;
                }
                cur->key = next->key;
                cur->data = next->data;
                par->left = next->right;
            }
            delete next;
        }
        return true;
    }
    void list() {
        list_sub(root);
        cout << endl;
    }
    void print() {
        if(root == nullptr) {
            cout << "Tree empty" << endl;
            return;
        }
        if(get_size() > 8) {
            cout << "Tree too big" << endl;
            return;
        }
        auto prit = [](Node* node, const string& pref, auto&& prit)->void {
            if(node == nullptr) return;
            prit(node->right, pref + "    ", prit);

            cout << pref << node->key << endl;

            prit(node->left, pref + "    ", prit);
        };

        prit(root, "", prit);
    }
    class Iterator {
    private:
        Btree* tree;
        long cur_pos = -1;
    public:
        Iterator() : tree(NULL), cur_pos(0) {}
        Iterator(Btree* tree) {}
        // T& operator *() {}
        // Iterator& operator ++() {}
        // Iterator& operator --() {}
        // bool operator ==(const Iterator& two) {}
        // bool operator !=(const Iterator& two) {}
    };
    class Rev_Iterator {
    private:
        Btree* tree;
        long cur_pos = -1;
    public:
        Rev_Iterator() : tree(NULL), cur_pos(0) {}
        Rev_Iterator(Btree* tree) {}
        // T& operator *() {}
        // Rev_Iterator& operator ++() {}
        // Rev_Iterator& operator --() {}
        // bool operator ==(const Rev_Iterator& two) {}
        // bool operator !=(const Rev_Iterator& two) {}
    };
    // Iterator begin() {}
    // Iterator end() {}
    // Rev_Iterator rbegin() {}
    // Rev_Iterator rend() {}
};