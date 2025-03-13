#include <malloc.h>
#include <iostream>
using namespace std;

template <class T> 
class Vector {
private:
    T* data;
    long capacity;
    long size;
    friend class Iterator;
    friend class Rev_Iterator;
public:
    class Iterator {
    private:
        Vector * v;
        long cur_pos;
    public:
        Iterator();
        Iterator(long);
        T& operator *();
        Iterator& operator ++();
        Iterator& operator --();
        bool operator ==(const Iterator&);
        bool operator !=(const Iterator&);
    };
    class Rev_Iterator {
        private:
        Vector * v;
        long cur_pos;
    public:
        Rev_Iterator();
        Rev_Iterator(long);
        T& operator *();
        Rev_Iterator& operator ++();
        Rev_Iterator& operator --();
        bool operator ==(const Rev_Iterator&);
        bool operator !=(const Rev_Iterator&);
    };
    Vector();
    Vector(long, T);
    Vector(const Vector<T>&);
    ~Vector();
    long GetCapacity();
    long GetSize();
    bool IsEmpty();
    bool Clean();
    long FindByVal(T);
    T Read(long);
    bool Mod(long, T);
    void Add(T);
    void Add(long, T);
    void Del(T);
    void Del(long);
    void WriteList(Vector);
    Iterator begin();
    Iterator end();
    Rev_Iterator rbegin();
    Rev_Iterator rend();
};