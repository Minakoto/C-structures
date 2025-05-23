#include "btree.h"

#define l1 "1. "
void list(bool);


int main() {
    Btree<int, int> root;
    Btree<int, int>::Iterator iterator;
    Btree<int, int>::Rev_Iterator r_iterator;
    bool exit = false, mode = true;
    int cmd = 0;
    int value1 = 0, value2 = 0, result = 0;

    while(!exit) {
        value1 = 0, value2 = 0, result = 0;;
        list(mode);
        cin >> cmd;
        cout << endl;
        switch(cmd) {
            case 1:
                if(mode) {
                    cout << "Введте значения ключа и данных: ";
                    cin >> value1;
                    cin >> value2;
                    cout << root.add(value1, value2);
                }
                else iterator = root.begin();
                break;
            case 2:

                if(mode) {
                    cout << "Введте значение ключа: ";
                    cin >> value1;
                    cout << root.del(value1);
                } 
                else r_iterator = root.rbegin();
                break;
            case 3:
                if(mode) {
                    try {
                        cout << "Введте значение ключа: ";
                        cin >> value1;
                        result = root.read(value1); 
                    } catch(...) {
                        cout << "Исключение" << endl;
                        break;
                    }
                    cout << result << endl;
                }
                else {
                    try {
                        result = *iterator; 
                    } catch(...) {
                        cout << "Исключение" << endl;
                        break;
                    }
                    cout << result << endl;
                }
                break;
            case 4:
                if(mode) {
                    try {
                        cout << "Введте значения ключа и данных: ";
                        cin >> value1;
                        cin >> value2;
                        root.write(value1, value2);
                    } catch(...) {
                        cout << "Исключение" << endl;
                        break;
                    }
                }
                else {
                    try {
                        result = *r_iterator;
                    } catch(...) {
                        cout << "Исключение" << endl;
                        break;
                    }
                    cout << result << endl;
                }                break;
            case 5:
                if(mode) cout << root.get_size() << endl;
                else {
                    cout << "Введте значение: ";
                    cin >> value1;
                    try {
                        *iterator = value1;
                    } catch(...) {
                        cout << "Исключение" << endl;
                        break;
                    }
                }
                break;
            case 6:
                if(mode) cout << root.is_empty() << endl;
                else {
                    cout << "Введте значение: ";
                    cin >> value1;
                    try {
                        *r_iterator = value1;
                    } catch(...) {
                        cout << "Исключение" << endl;
                        break;
                    }
                }
                break;
            case 7:
                if(mode) root.list();
                else ++iterator;
                break;
                
            case 8:
                if(mode) root.print_horizontal();
                else --iterator;
                break;
            case 9:
                if(mode) root.print();
                ++r_iterator;
                break;
            case 10:
                if(mode) {
                    mode = false;
                    break;
                }
                else --r_iterator;
                break;
            case 11:
                if(mode) root.clean();
                else cout << (iterator == root.end());
                break;
            case 12:
                if(mode) break;
                cout << (r_iterator == root.rend());
                break;
            case 0:
                if(mode) exit = true;
                else mode = true;
                break;
            default:
                cout << "Неверная команда" << endl;
        }
    }
}

void list(bool mode) {
    cout << endl <<"___________________________________" << endl;
    if(mode) {
        cout << "Меню: " << endl;
        cout << "1. Добавление элемента" << endl;
        cout << "2. Удаление элемента" << endl;
        cout << "3. Чтение элемента на по ключу" << endl;
        cout << "4. Запись значения в элемент по ключу" << endl;
        cout << "5. Опрос размера дерева" << endl; 
        cout << "6. Проверка на пустоту" << endl;
        cout << "7. Вывод дерева (Формат Lr-r-Rr)" << endl; 
        cout << "8. Горизонтальное представление" << endl;
        cout << "9. Вертикальное представление" << endl;
        cout << "10. Операции над итераторами" << endl;
        cout << "11. Очистка дерева" << endl;
        cout << "0. Выход" << endl;
    }
    else {
        cout << "Операции над итераторами" << endl;
        cout << "1. begin" << endl;
        cout << "2. rbegin" << endl;
        cout << "3. * Iterator" << endl;
        cout << "4. * Rev_Iterator" << endl;
        cout << "5. * Iterator = Значение"<< endl;
        cout << "6. * Rev_Iterator = Значение"<< endl;
        cout << "7. ++ Iterator" << endl;
        cout << "8. -- Iterator" << endl;
        cout << "9. ++ Rev_Iterator" << endl;
        cout << "10. -- Rev_Iterator" << endl;
        cout << "11. Iterator == end()" << endl;
        cout << "12. Rev_Iterator == rend()" << endl;
        cout << "0. Назад" << endl;
    }
    cout << "Выберите действие: ";
}
