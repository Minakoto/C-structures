#include <malloc.h>
#include <iostream>
using namespace std;

template <class T>
class Btree {
friend class Iterator;
friend class Rev_Iterator;
private:
    long key;
    T* data;
    Btree<T>* left;
    Btree<T>* right;
public:
    Btree() : left(NULL), right(NULL), data(NULL), key(0) {}
    Btree(Btree<T>& other) {}
    ~Btree() {}
    int get_size() {}
    void clear() {}
    bool is_empty() {}
    bool write(long key) {} // throw exception
    T read(long key) {} // throw exception
    bool add(long key, T data) {}
    bool del(long key) {}
    void list() {}
    void print() {}
    Iterator begin() {}
    Iterator end() {}
    Rev_Iterator rbegin() {}
    Rev_Iterator rend() {}
    class Iterator {
    private:
        Btree* tree;
        long cur_pos = -1;
    public:
        Iterator() : v(NULL), cur_pos(0) {}
        Iterator(Btree* tree) {}
        T& operator *() {}
        Iterator& operator ++() {}
        Iterator& operator --() {}
        bool operator ==(const Iterator& two) {}
        bool operator !=(const Iterator& two) {}
    };
    case Rev_Iterator {
    private:
        Btree* tree;
        long cur_pos = -1;
    public:
        Rev_Iterator() : v(NULL), cur_pos(0) {}
        Rev_Iterator(Btree* tree) {}
        T& operator *() {}
        Rev_Iterator& operator ++() {}
        Rev_Iterator& operator --() {}
        bool operator ==(const Rev_Iterator& two) {}
        bool operator !=(const Rev_Iterator& two) {}
    };

};