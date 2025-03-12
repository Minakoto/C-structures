

template <class T> 
class Vector {
private:
    T* data;
    long capacity;
    long size;
    class Iterator {

    };
    class Rev_Iterator {

    }
    
public:
    Vector() : capacity(0), size(0) {}
    Vector(long size, T val) {

    }
    Vector(Vector right) {
        this->capacity = right->capacity;
        this->size = right->size;
    }
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

    }
    long Read(long pos) {

    }
    long Mod(long pos) {

    }
    void Add() {

    }
    void Add(long pos) {

    }
    void Del(T val) {

    }
    void Del(long pos) {

    }


};