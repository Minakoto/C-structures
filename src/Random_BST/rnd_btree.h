#include "btree.h"
#include <stack>
using namespace std;

template <class K, class T>
class RND_Btree : public Btree<K, T> {
friend class Iterator;
friend class Rev_Iterator;
friend class Btree<K, T>::Node;
private:
    class R_Node : public Btree<K, T>::Node {
        public:
            long size;
            R_Node() : Btree<K, T>::Node(), size(1) {}
            R_Node(T val, K k) : Btree<K, T>::Node(val, k), size(1) {}
            long get_size() {
            if(this == nullptr) return 0;
                return size;
            }
            void fixsize() {
                this->size = ((R_Node*)this->left)->get_size() + ((R_Node*)this->right)->get_size() + 1;
            } 
    };
    R_Node* root_add(R_Node* sub, K key, T data) {
        auto R = [](R_Node* tree)->R_Node* {
            R_Node* new_root = (R_Node*)tree->left;
            if(!new_root) return tree;
            tree->left = new_root->right;
            new_root->right = tree;
            new_root->size = tree->size;
            tree->fixsize();
            return new_root;
        };
        auto L = [](R_Node* tree)->R_Node* {
            R_Node* new_root = (R_Node*)tree->right;
            if(!new_root) return tree;
            tree->right = new_root->left;
            new_root->left = tree;
            new_root->size = tree->size;
            tree->fixsize();
            return new_root;
        };
        R_Node* new_node = new R_Node(data, key);
        if(sub == nullptr) return new_node;
        stack<R_Node*> path;
        R_Node* cur = sub;
        while(cur != nullptr) {
            path.push(cur);
            if(key == cur->key) return sub;
            if(key < cur->key) cur = (R_Node*) cur->left;
            else cur = (R_Node*) cur->right;
            Btree<K, T>::count++;
        }
        while(!path.empty()) {
            R_Node* parent = path.top();
            path.pop();
            if(key < parent->key) {
                parent->left = new_node;
                new_node = R(parent);
            }
            else {
                parent->right = new_node;
                new_node = L(parent);
            }
        }
        return new_node;
    }
    R_Node* join(R_Node* a, R_Node* b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
    
        R_Node* merged = nullptr;
        R_Node** current = &merged;
    
        while (a != nullptr && b != nullptr) {
            if(rand() % (a->get_size() + b->get_size()) < a->get_size()) {
                *current = a;
                current = (R_Node**) &(a->right);
                a = (R_Node*) a->right;
            } else {
                *current = b;
                current = (R_Node**)&(b->left);
                b = (R_Node*) b->left;
            }
            Btree<K, T>::count++;
        }    
        *current = (a != nullptr) ? a : b;
    
        R_Node* fix_ptr = merged;
        while (fix_ptr != nullptr) {
            fix_ptr->fixsize();
            fix_ptr = ((R_Node*)fix_ptr->right != nullptr) ? (R_Node*)fix_ptr->right : (R_Node*)fix_ptr->left;
        }
        return merged;
    }
public:
    RND_Btree() : Btree<K, T>::Btree() {}
    RND_Btree(RND_Btree<K, T>& other) : Btree<K, T>::Btree(other) {}
    ~RND_Btree() {}
    bool add(K key, T data) override {
        Btree<K, T>::count = 0;
        R_Node** current = (R_Node**)&(Btree<K, T>::root);
        while (*current != nullptr) {
            if(rand() % ((*current)->get_size() + 1) == 0) {
                *current = root_add(*current, key, data);
                return true;
            }
            if (key == (*current)->key) return false;
            
            if (key < (*current)->key) current = (R_Node**) &((*current)->left);
            else current = (R_Node**) &((*current)->right);
            Btree<K, T>::count++;
        }
        *current = new R_Node(data, key);
        (*current)->fixsize();
        return true;
    }
    bool del(K key) override {
        Btree<K, T>::count = 0;
        R_Node** parent_ptr = (R_Node**) &(Btree<K, T>::root);
        R_Node* current = (R_Node*)(Btree<K, T>::root);
    
        while (current != nullptr && current->key != key) {
            if (key < current->key) {
                parent_ptr = (R_Node**) &(current->left);
                current = (R_Node*)current->left;
            } else {
                parent_ptr = (R_Node**) &(current->right);
                current = (R_Node*)current->right;
            }
            Btree<K, T>::count++;
        }
        if (current == nullptr) {
            return false;
        }
        R_Node* joined_subtree = join((R_Node*)current->left, (R_Node*)current->right);
        *parent_ptr = joined_subtree;
        delete current;
        return true;
    }
};