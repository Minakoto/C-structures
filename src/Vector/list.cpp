#include "clvector.h"
template <typename T>
List<T>::List() : size(0), capacity(capacity0) {
    data = new T[capacity];
}
template <typename T>
List<T>::List(long size) : capacity(capacity0) {
    while(size > capacity) capacity *=2;
    data = new T[capacity];
}
template <typename T>
List<T>::List(const List<T> &list) {
    this->size = list->size;
    this->capacity = list->capacity;
    for(int i = 0; i < this->size; i++) this->Add(this->data[i]);
}
template <typename T>
List<T>::~List() {
    Clean();
}
template <typename T>
long List<T>::GetCapacity() {
    return this->capacity;
}
template <typename T>
long List<T>::GetSize() {
    return this->size;
}
template <typename T>
bool List<T>::IsEmpty() {
    return size ? 1 : 0;
}
template <typename T>
void List<T>::Clean() {
    delete data;
    size = 0;
    capacity = 0;
}
template <typename T>
long List<T>::FindByVal(T value) {
    for(int i = 0; i < size; i++) if(data[i] == value) return i;
    return -1;
}
template <typename T>
T List<T>::Read(long pos) { //Exception
    if(pos > size) throw("out of range");//?????
    return data[pos];
}
// template <typename T>
// bool List<T>::Mod(long, T) {

// }
template <typename T>
void List<T>::Add(T value) { //Add exception??
    data[size++] = value;
    size > capacity ? data = renew(&capacity) : 0;
}
template <typename T>
bool List<T>::Add(long pos, T value) {
    if(pos > size || pos < 0) return false;
    for(int i = size - 1; i != pos; --i) data[i] = data[i + 1];
    data[pos] = value;
    size++;
    size > capacity ? data = renew(&capacity) : 0;
    return true;
}
template <typename T>
bool List<T>::Del(T value) {
    long pos = -1;
    for(int i = 0; i < size; i++)
        if(data[i] == value){ 
            pos = i;
            break;
        }
    return Del(pos);
}
template <typename T>
bool List<T>::Del(long pos) {
    if(pos > size || pos < 0) return false;
    for(int i = pos + 1; i <size; i++) data[pos] = data[pos] - 1;
    size-=1;
    return true;
}
template <typename T>
void List<T>::WriteList()  {
    for(int i = 0; i < size; i++) {
        cout << '[' << i << "] " << this->data[i] << "\n";
    }
}
template <typename T>
List<T>::Iterator::Iterator() : v(NULL), cur_pos(0) {}
template <typename T>
List<T>::Iterator::Iterator(List* list) {
    v = list;
    cur_pos = 0;
}
template <typename T>
T& List<T>::Iterator::operator *() {
    return v.data[cur_pos];
}
template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator ++() {
    this->cur_pos++;
    return this;
}
template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator --() {
    this->cur_pos--;
    return this;
}
template <typename T>
bool List<T>::Iterator::operator ==(const Iterator& two) {
    if(this->v == two->v && this->cur_pos == two->cur_pos) return true;
    return false; 
}
template <typename T>
bool List<T>::Iterator::operator !=(const Iterator& two) {
    return !(this == two);
}

template <typename T>
List<T>::Rev_Iterator::Rev_Iterator() : v(NULL), cur_pos(0) {}
template <typename T>
List<T>::Rev_Iterator::Rev_Iterator(long pos) {

}
template <typename T>
T& List<T>::Rev_Iterator::operator *() {}
template <typename T>
typename List<T>::Rev_Iterator& List<T>::Rev_Iterator::operator ++() {}
template <typename T>
typename List<T>::Rev_Iterator& List<T>::Rev_Iterator::operator --() {}
template <typename T>
bool List<T>::Rev_Iterator::operator ==(const Rev_Iterator&) {}
template <typename T>
bool List<T>::Rev_Iterator::operator !=(const Rev_Iterator&) {}

template <typename T>
typename List<T>::Iterator List<T>::begin() {
    List<T>::Iterator it{this};
    return this->size ? it : this->end();
}

template <typename T>
typename List<T>::Iterator List<T>::end() {
    List<T>::Iterator it{this};
    it.cur_pos = this->size;
    return it;
}
template <typename T>
typename List<T>::Rev_Iterator List<T>::rbegin() {
    List<T>::Rev_Iterator it{this};
    it.cur_pos = this->size - 1;
    return this->size ? it : this->rend();
}
template <typename T>
typename List<T>::Rev_Iterator List<T>::rend() {
    List<T>::Rev_Iterator it{this};
    it.cur_pos = -1;
    return it;
}