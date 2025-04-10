#include <malloc.h>
#include <iostream>
using namespace std;

template <class T> 
class List {
private:
    T* data;
    long capacity;
    long size;
    long const capacity0 = 16;
    T* renew() {
        this->capacity *= 2;
        T* tmp = new T[this->capacity];
        for(int i = 0; i < size; i++) tmp[i] = data[i];
        delete data;
        return tmp;
    }
public:
    class Iterator {
    private:
        List * v;
        long cur_pos;
    public:
        Iterator()  : v(NULL), cur_pos(0) {}
        Iterator(List* list) {
            v = list;
            cur_pos = 0;
        }
        T& operator *() { return v.data[cur_pos];}
        Iterator& operator ++() {
            this->cur_pos++;
            return this;
        }
        Iterator& operator --() {
            this->cur_pos--;
            return this;
        }
        bool operator ==(const Iterator& two) {
            if(this->v == two->v && this->cur_pos == two->cur_pos) return true;
            return false; 
        }
        bool operator !=(const Iterator& two) {
            return !(this == two);
        }
    };
    class Rev_Iterator {
    private:
        List * v;
        long cur_pos;
    public:
        Rev_Iterator()  : v(NULL), cur_pos(0) {}
        Rev_Iterator(T list) {
            v = list;
            cur_pos = list.size;
        }
        T& operator *() {return v.data[cur_pos];}
        Rev_Iterator& operator ++() {
            this->cur_pos++;
            return this;
        }
        Rev_Iterator& operator --() {
            this->cur_pos--;
            return this;
        }
        bool operator ==(const Rev_Iterator& two) {
            if(this->v == two->v && this->cur_pos == two->cur_pos) return true;
            return false; 
        }
        bool operator !=(const Rev_Iterator& two) {
            return !(this == two);
        }
    };
    List() {
        size = 0;
        capacity = capacity0;
        data = new T[capacity];
    }
    List(long size) : capacity(capacity0) {
        while(size > capacity) capacity *=2;
        data = new T[capacity];
    }
    List(const List<T> &list) {
        this->size = list->size;
        this->capacity = list->capacity;
        for(int i = 0; i < this->size; i++) this->Add(this->data[i]);
    }
    ~List() {Clean();}
    long GetCapacity() {return this->capacity;}
    long GetSize() {return this->size;}
    bool IsEmpty() { return size ? 1 : 0;}
    void Clean()  {
        delete data;
        size = 0;
        capacity = 0;
    }
    long FindByVal(T value) {
        for(int i = 0; i < size; i++) if(data[i] == value) return i;
        return -1;
    }
    T Read(long pos) {
        if(pos > size) throw "Out of range";
        return data[pos];
    }
    void Add(T value) {
        data[size++] = value;
        size > capacity ? data = renew() : 0;
    }
    bool Add(long pos, T value) {
        if(pos > size || pos < 0) return false;
        for(int i = size - 1; i != pos; --i) data[i] = data[i + 1];
        data[pos] = value;
        size++;
        size > capacity ? data = renew() : 0;
        return true;
    }
    bool Del(T value) {
        long pos = -1;
        for(int i = 0; i < size; i++)
            if(data[i] == value){ 
                pos = i;
                break;
            }
        return Del(pos);
    }
    bool Del(long pos) {
        if(pos > size || pos < 0) return false;
        for(int i = pos; i <size - 1; i++) data[i] = data[i+1]; 
        size-=1;
        return true;
    }
    void WriteList() {
        for(int i = 0; i < size; i++) {
            cout << '[' << i << "] " << this->data[i] << "\n";
        }
    }
    friend class Iterator;
    friend class Rev_Iterator;
    Iterator begin() {
        List<T>::Iterator it{this};
        return this->size ? it : this->end();
    }
    Iterator end() {
        List<T>::Iterator it{this};
        it.cur_pos = this->size;
        return it;
    }
    Rev_Iterator rbegin() {
        List<T>::Rev_Iterator it{this};
        it.cur_pos = this->size - 1;
        return this->size ? it : this->rend();
    }
    Rev_Iterator rend() {
        List<T>::Rev_Iterator it{this};
        it.cur_pos = -1;
        return it;
    }
};

