#include <malloc.h>
#include <iostream>
#include <stack>
using namespace std;

template <class K, class T>
class Btree {
friend class Iterator;
friend class Rev_Iterator;
friend class Node;
private:
    class Node {
        public:
            K key;
            T data;
            Node* left;
            Node* right;
            long size;
            Node() : data(nullptr), key(0), left(nullptr), right(nullptr), size(1) {}
            Node(T val, K k) : data(val), key(k), left(nullptr), right(nullptr), size(1) {}
            void set_size(long in) {size = in;}
            long get_size() {
                if(this == nullptr) return 0;
                else return size;
            }
            void fixsize() {
                this->size = this->left->get_size() + this->right->get_size() + 1;
            } 
    };
    Node* root;
    long count = 0;

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
    void clear(Node* node) {
        if(node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete(node);
        }
    }
    Node* root_add(Node* sub, K key, T data) {
        auto R = [](Node* tree)->Node* {
            Node* new_root = tree->left;
            if(!new_root) return tree;
            tree->left = new_root->right;
            new_root->right = tree;
            new_root->size = tree->size;
            tree->fixsize();
            return new_root;
        };
        auto L = [](Node* tree)->Node* {
            Node* new_root = tree->right;
            if(!new_root) return tree;
            tree->right = new_root->left;
            new_root->left = tree;
            new_root->size = tree->size;
            tree->fixsize();
            return new_root;
        };
        
        Node* new_node = new Node(data, key);
        if(sub == nullptr) return new_node;
        stack<Node*> path;
        Node* cur = sub;
        while(cur != nullptr) {
            path.push(cur);
            if(key == cur->key) return sub;
            if(key < cur->key) cur = cur->left;
            else cur = cur->right;
            count++;
        }
        while(!path.empty()) {
            Node* parent = path.top();
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
    Node* join(Node* a, Node* b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
    
        Node* merged = nullptr;
        Node** current = &merged;
    
        while (a != nullptr && b != nullptr) {
            if(rand() % (a->get_size() + b->get_size()) < a->get_size()) {
                *current = a;
                current = &(a->right);
                a = a->right;
            } else {
                *current = b;
                current = &(b->left);
                b = b->left;
            }
            count++;
        }    
        *current = (a != nullptr) ? a : b;
    
        Node* fix_ptr = merged;
        while (fix_ptr != nullptr) {
            fix_ptr->fixsize();
            fix_ptr = (fix_ptr->right != nullptr) ? fix_ptr->right : fix_ptr->left;
        }
    
        return merged;
    }
public:
    Btree() {
        root = NULL;
    }
    Btree(Btree<K, T>& other) : root(nullptr) {
        root = cpy(other.root);
    }
    ~Btree() {
        clear(root);
    }
    void clean() {
        clear(root);
        root = nullptr;
    }
    int get_size() {
        return cnt(root);
    }
    Node** get_root() {
        return &root;
    }
    bool is_empty() {
        return root == nullptr;
    }
    // throws exception
    void write(K key, T val) {
        Node* tmp = root;
        while(tmp != nullptr && key != tmp->key) {
            if(key < tmp->key) tmp = tmp->left;
            else tmp = tmp->right;
        }
        if(tmp == nullptr) throw "Not found exception";
        tmp->data = val;
    }
    // throws exception
    T read(K key) {
        count = 0;
        Node* tmp = root;
        while(tmp != nullptr && key != tmp->key) {
            if(key < tmp->key) tmp = tmp->left;
            else tmp = tmp->right;
            count++;
        }
        if(tmp == nullptr) throw "Not found exception";
        return tmp->data;
    }
    bool add(int key, int data) {
        count = 0;
        Node** current = &root;
        while (*current != nullptr) {
            if(rand() % ((*current)->get_size() + 1) == 0) {
                *current = root_add(*current, key, data);
                return true;
            }
            if (key == (*current)->key) return false;
            
            if (key < (*current)->key) current = &((*current)->left);
            else current = &((*current)->right);
            count++;
        }
        *current = new Node(data, key);
        (*current)->fixsize();
        return true;
    }
    bool del(K key) {
        count = 0;
        Node** parent_ptr = &root;
        Node* current = root;
    
        while (current != nullptr && current->key != key) {
            if (key < current->key) {
                parent_ptr = &(current->left);
                current = current->left;
            } else {
                parent_ptr = &(current->right);
                current = current->right;
            }
            count++;
        }
    
        if (current == nullptr) {
            return false;
        }
        
        Node* joined_subtree = join(current->left, current->right);
        *parent_ptr = joined_subtree;
        delete current;
    
        return true;
    }
    void list() {
        if(root == nullptr) {
            cout << "Дерево пусто" << endl;
            return;
        }
        list_sub(root);
        cout << endl;
    }
    void print() {
        if(root == nullptr) {
            cout << "Дерево пусто" << endl;
            return;
        }
        if(get_size() > 8) {
            cout << "Превышено ограничение размера" << endl;
            return;
        }
        cout << endl << endl;
        auto prit = [](Node* node, const string& pref, auto&& prit)->void {
            if(node == nullptr) return;
            prit(node->right, pref + "    ", prit);

            cout << pref << node->key << endl;

            prit(node->left, pref + "    ", prit);
        };
        prit(root, "", prit);
    }
    Node* min(Node* node) {
        Node* min = node;        
        while(min != nullptr && min->left != nullptr) min = min->left;
        return min;
    }
    Node* max(Node* node) {
        Node* max = node;        
        while(max != nullptr && max->right != nullptr) max = max->right;
        return max;
    }
    long count_nodes() {
        long cnt = this->count;
        this->count = 0;
        return cnt;
    }
    class Iterator {
    private:
        Btree* tree = nullptr;
        Node* cur_pos = nullptr;
        Node* get_bigger(Node* cur) {
            if(cur_pos == nullptr) return nullptr;
            if(cur_pos->right) return tree->min(cur_pos->right);
            Node* prev = nullptr;
            Node* next = tree->root;
            while(next != cur_pos) {
                if(cur_pos->key < next->key) {
                    prev = next;
                    next = next->left;
                }
                else next = next->right;
            }
            return prev;
        }
        Node* get_lower(K key) {
            Node* prev = nullptr;
            Node* cur = tree->root;
            while(cur!= nullptr) {
                if(key > cur->key) {
                    prev = cur;
                    cur = cur->right;
                }
                else if(key < cur->key) cur = cur->left;
                else {
                    if(cur->left) return tree->max(cur->left);
                    break;
                }
            }
            return prev;
        }
    public:
        Iterator() : tree(nullptr), cur_pos(nullptr) {}
        Iterator(Btree& tr, Node* min_l) : tree(&tr), cur_pos(min_l) {}
        T& operator *() {
            if(cur_pos == nullptr || tree->root == nullptr) throw "Empty exception";
            return cur_pos->data;
        }
        Iterator& operator ++() {
            if(cur_pos == nullptr) return *this;
            cur_pos = get_bigger(cur_pos);
            return *this;
        }
        Iterator& operator --() {
            if(cur_pos == nullptr) return *this;
            cur_pos = get_lower(cur_pos->key);
            return *this;
        }
        bool operator ==(const Iterator& two) {
            return this->cur_pos == two.cur_pos;
        }
        bool operator !=(const Iterator& two) {
            return this->cur_pos != two.cur_pos;
        }
    };
    class Rev_Iterator {
    private:
        Btree* tree = nullptr;
        Node* cur_pos = nullptr;
        Node* get_bigger(Node* cur) {
            if(cur_pos == nullptr) return nullptr;
            if(cur_pos->right) return tree->min(cur_pos->right);
            Node* prev = nullptr;
            Node* next = tree->root;
            while(next != cur_pos) {
                if(cur_pos->key < next->key) {
                    prev = next;
                    next = next->left;
                }
                else next = next->right;
            }
            return prev;
        }
        Node* get_lower(K key) {
            Node* prev = nullptr;
            Node* cur = tree->root;
            while(cur!= nullptr) {
                if(key > cur->key) {
                    prev = cur;
                    cur = cur->right;
                }
                else if(key < cur->key) cur = cur->left;
                else {
                    if(cur->left) return tree->max(cur->left);
                    break;
                }
            }
            return prev;
        }
    public:
        Rev_Iterator() : tree(nullptr), cur_pos(nullptr) {}
        Rev_Iterator(Btree& tr, Node* node) : tree(&tr), cur_pos(node) {}
        T& operator *() {
            if(cur_pos == nullptr || tree->root == nullptr) throw "Empty exception";
            return cur_pos->data;
        }
        Rev_Iterator& operator ++() {
            if(cur_pos == nullptr) return *this;
            cur_pos = get_lower(cur_pos->key);
            return *this;
        }
        Rev_Iterator& operator --() {
            if(cur_pos == nullptr) return *this;
            cur_pos = get_bigger(cur_pos);
            return *this;
        }
        bool operator ==(const Rev_Iterator& two) {
            return this->cur_pos == two.cur_pos;
        }
        bool operator !=(const Rev_Iterator& two) {
            return this->cur_pos != two.cur_pos;
        }
    };
    Iterator& begin() {
        Iterator* it = new Iterator(*this, this->min(this->root));
        return *it;
    }
    Iterator& end() {
        Iterator* it = new Iterator(*this, nullptr);
        return *it;
    }
    Rev_Iterator& rbegin() {
        Rev_Iterator* it = new Rev_Iterator(*this, this->max(this->root));
        return *it;
    }
    Rev_Iterator& rend() {
        Rev_Iterator* it = new Rev_Iterator(*this, nullptr);
        return *it;
    }
};