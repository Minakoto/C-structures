#include <malloc.h>
#include <iostream>
using namespace std;

template <class T> 
class Vector {
private:
    T* data;
    long capacity;
    long size;
    T* Renew() {
        capacity *= 2;
        T* tmp = malloc(sizeof(T)*capacity);
        for(int i = 0; i < size; i++) {
            tmp[i] = data[i];
        }
        free(data);
        return tmp;
    }
public:
    class Iterator {
    private:
        Vector * v;
        long cur_pos;
    public:
        Iterator() : cur_pos(0), v(NULL){};
        Iterator(int pos) : cur_pos(pos) {};
    };
    friend class Iterator;
    class Rev_Iterator {};
    friend class Rev_Iterator;
    Vector() : capacity(0), size(0) {}
    Vector(long size, T val) {
        this->size = size;
        while(this->size > capacity) {
            data = Renew();
        }
        for(int i = 0; i < this->size; i++) {
            data[i] = val;
        }
    }
    Vector(const Vector<T>& right) {
        this->capacity = right->capacity;
        this->size = right->size;
    }
    ~Vector() {
        free(data);
    }
    long GetCapacity() {
        return capacity;
    }
    long GetSize() {
        return size;
    }
    bool IsEmpty() {
        return (bool)size;
    }
    long FindByVal(T val) {
        for(int i = 0; i < size; i++)
            if (*(data + i) == val) return i;
        return -1;

    }
    T Read(long pos) {
        if(pos < size) return data[pos];
        else return 0;

    }
    bool Mod(long pos, T val) {
        bool res = false;
        if(pos < size) {
            data[pos] = val;
            res = true;
        }
        return res;

    }
    void Add(T val) { //Throw exception somehow
        size += 1;
        if(size > capacity) 
            data = Renew();
        data[size - 1] = val;
    }
    void Add(long pos, T val) {

    } //Throw exception somehow
    void Del(T val) {}
    void Del(long pos) {}
};