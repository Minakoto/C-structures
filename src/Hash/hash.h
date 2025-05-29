#include <iostream>
#include <malloc.h>

template<class T>
class Hash_Table {
    class Node {
        T value; // Данные
        unsigned key; // Ключ
        short state; // Состояние 
    };
    Node* table; // Массив элементов
    unsigned long elem_count = 0; // Кол-во элементов

    int hash(unsigned key) {}
public:
    int get_size(); // Опрос размера таблицы
    unsigned long get_count() {
        return elem_count;
    }
    bool is_empty(); // Проверка на пустоту
    {
        return elem_count == 0;
    }
    void clean(); // Очистка таблицы
    {
        for (long i=0; i<elem_count; i++) {del(i);}
    }
    bool insert(T value, unsigned key); // Вставка по ключу
    bool del(unsigned key); // Удаление по ключу
    T search(unsigned key); // Поиск по ключу
    class Iterator{
        Hash_Table* tbl; // Указатель на таблицу 
        Node* cur_pos; // Позиция итератора
    public:
        Iterator(); // Конструктор по умолчанию
        Iterator(Hash_Table* table, Node* pos); // Конструктор
        T& operator *(); // Оператор разыменования
        Iterator& operator ++(); // Операция инкремента
        Iterator& operator --(); // Операция декремента
        bool operator ==(const Iterator& two); // Операция сравнения
        bool operator !=(const Iterator& two); // Операция неравенства
    }

    Iterator& begin(); // Установка итератора
    Iterator& end(); // Неустановленный итератор
};