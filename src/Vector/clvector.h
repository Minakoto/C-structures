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
public:
    class Iterator {
    private:
        List * v;
        long cur_pos;
    public:
        Iterator();
        Iterator(List*);
        T& operator *();
        Iterator& operator ++();
        Iterator& operator --();
        bool operator ==(const Iterator&);
        bool operator !=(const Iterator&);
    };
    class Rev_Iterator {
    private:
        List * v;
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
    List();
    List(long);
    List(long, long, T);
    List(const List<T>&);
    ~List();
    long GetCapacity();
    long GetSize();
    bool IsEmpty();
    void Clean();
    long FindByVal(T);
    T Read(long);
    // bool Mod(long, T);
    void Add(T);
    bool Add(long, T);
    bool Del(T);
    bool Del(long);
    void WriteList();
    friend class Iterator;
    friend class Rev_Iterator;
    Iterator begin();
    Iterator end();
    Rev_Iterator rbegin();
    Rev_Iterator rend();
};

