#include <malloc.h>
#include <iostream>
using namespace std;

template <class T> 
class Vector {
private:
    T* data;
    long capacity;
    long size;
    class Iterator {

    };
    class Rev_Iterator {

    };

public:
    Vector() : capacity(0), size(0) {}
    Vector(long size, T val) {

    }
    // Vector(const Vector<T> right) {
    //     this->capacity = right->capacity;
    //     this->size = right->size;
    // }
    ~Vector() {

    }
    long GetCapacity() {
        return capacity;
    }
    long GetSize() {
        return size;
    }
    bool IsEmpty() {
        return size; //?
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
    int Mod(long pos, T val) {
        int res = 0;
        if(pos < size) {
            data[pos] = val;
            res = 1;
        }
        return res;

    }
    void Add() { //TODO DEFO
        capacity *= 2;


    }
    void Add(long pos) {

    }
    void Del(T val) {

    }
    void Del(long pos) {

    }
};