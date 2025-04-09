#include "clvector.h"
template <class T>
List<T>::List() : size(0), capacity(capacity0) {
    data = new T[capacity];
}
template <class T>
List<T>::List(long size) : capacity(capacity0) {
    while(size > capacity) capacity *=2;
    data = new T[capacity];
}
template <class T>
List<T>::List(const List<T> &list) {
    this->size = list->size;
    this->capacity = list->capacity;
    for(int i = 0; i < this->size; i++) this->Add(this->data[i]);
}
template <class T>
List<T>::~List() {
    Clean();
}
template <class T>
long List<T>::GetCapacity() {
    return this->capacity;
}
template <class T>
long List<T>::GetSize() {
    return this->size;
}
template <class T>
bool List<T>::IsEmpty() {
    return size ? 1 : 0;
}
template <class T>
void List<T>::Clean() {
    delete data;
    size = 0;
    capacity = 0;
}
template <class T>
long List<T>::FindByVal(T value) {
    for(int i = 0; i < size; i++) if(data[i] == value) return i;
    return -1;
}
template <class T>
T List<T>::Read(long pos) { //Exception
    if(pos > size) throw("out of range");//?????
    return data[pos];
}
// template <class T>
// bool List<T>::Mod(long, T) {

// }
template <class T>
void List<T>::Add(T value) { //Add exception??
    data[size++] = value;
    size > capacity ? data = renew(&capacity) : 0;
}
template <class T>
bool List<T>::Add(long pos, T value) {
    if(pos > size || pos < 0) return false;
    for(int i = size - 1; i != pos; --i) data[i] = data[i + 1];
    data[pos] = value;
    size++;
    size > capacity ? data = renew(&capacity) : 0;
    return true;
}
template <class T>
bool List<T>::Del(T value) {
    long pos = -1;
    for(int i = 0; i < size; i++)
        if(data[i] == value){ 
            pos = i;
            break;
        }
    return Del(pos);
}
template <class T>
bool List<T>::Del(long pos) {
    if(pos > size || pos < 0) return false;
    for(int i = pos + 1; i <size; i++) data[pos] = data[pos] - 1;
    size-=1;
    return true;
}


template <class T>
void List<T>::WriteList()  {
    for(int i = 0; i < size; i++) {
        cout << '[' << i << '] ' << this->data[i] << "\n";
    }
}