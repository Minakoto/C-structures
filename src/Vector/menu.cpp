#include "clvector.h"


void menu() {
    short cmd = 1; 
    int choice;
    int element;
    // List<int> list;
    List<int>::Iterator g;
    List<int>::Rev_Iterator rev_g;
    cout << "Начальная емкость: " << endl;
    
    while(cmd) {
        cout << "________________________________________________________" << endl;
        cout << "Меню:" << endl;
        cout << "1. Добавление элемента" << endl;
        cout << "2. Удаление элемента" << endl;
        cout << "3. Первоначальная установка итератора" << endl;
        cout << "4. Первоначальная установка обратного итератора" << endl;
        cout << "5. Сдвиг итератора вперед" << endl;
        cout << "6. Сдвиг итератора назад" << endl;
        cout << "7. Сдвиг обратного итератора вперед" << endl;
        cout << "8. Сдвиг обратного итератора назад" << endl;
        cout << "9. Получить значение на позиции итератора" << endl;
        cout << "10. Получить значение на позиции обратного итератора" << endl;
        cout << "11. Изменить значение на позиции итератора" << endl;
        cout << "12. Изменить значение на позиции обратного итератора" << endl;
        cout << "13. Количество элементов в списке" << endl;
        cout << "14. Емкость списка" << endl;
        cout << "15. Проверка на пустоту" << endl;
        cout << "16. Вывести список" << endl;
        cout << "17. Поиск" << endl;
        cout << "18. Изменение значения" << endl;
        cout << "19. Очистить список" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите команду: ";
    
        cin >> cmd;
        cout << "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾" << endl;
        switch(cmd) {
            case 1:
                cout << "Введите элемент:" << endl;
                cin >> element;
                cout << "В какую часть списка добавить элемент? [1: в конец / 2: по позиции]" << endl;
                cin >> choice;
                if (choice == 1) list.Add(element);
                else {
                        cout << "Введите позицию:" << endl;
                        cin >> choice;
                        list.Add(choice, element);
                    }
                break;
            case 2:
            cout << "По какому полю удалить элемент? [1: по значению / 2: по позиции]" << endl;
            cin >> choice;
            if (choice == 1) {
                cout << "Введите значение:" << endl;
                cin >> choice;
                list.Del((int)choice);
            }
            else {
                    cout << "Введите позицию:" << endl;
                    cin >> choice;
                    list.Del((long)choice);
                }
                break;
            case 3:
                g = list.begin();
                break;
            case 4:
                rev_g = list.rbegin();
                break;
            case 5:
                ++g;
                break;
            case 6:
                --g;
                break;
            case 7:
                ++rev_g;
                break;
            case 8:
                --rev_g;
                break;
            case 9:
                cout << "Значение на позиции итератора: " << *g << endl;
                break;
            case 10:
                cout << "Значение на позиции обратного итератора: " << *rev_g << endl;
                break;
            case 11:
                cout << "Введите значение:" << endl;
                cin >> choice;
                *g = choice;
                break;
            case 12:
                cout << "Введите значение:" << endl;
                cin >> choice;
                *rev_g = choice;
                break;
            case 13:
                cout << "Кол-во элементов в списке: " << list.GetSize() << endl;
                break;
            case 14:
                cout << "Кол-во элементов в списке: " << list.GetCapacity() << endl;
                break;
            case 15:
                cout << list.IsEmpty() << endl;
                break;
            case 16:
                list.WriteList();
                break;
            case 17:
            cout << "По какому полю будет происходить поиск? [1: по значению / 2: по позиции]" << endl;
            cin >> choice;
            if (choice == 1) {
                cout << "Введите значение:" << endl;
                cin >> choice;
                cout << "Позиция: " << list.FindByVal(choice) << endl;
            }
            else {
                    cout << "Введите позицию:" << endl;
                    cin >> choice;
                    cout << "Значение: "  << list.Read(choice) << endl;
                }
                break;
            case 18:
                cout << "Введите позицию: ";
                cin >> choice;
                cout << "Введите значение: ";
                cin >> element;
                list.Mod(element, choice);
                break;
            case 19:
                list.Clean();
                break;
            case 0:
                break;
            default:
                cout << "Неизвестная команда" << endl;
        }
    }
}

int main() {
    
    menu();
    return 0;
}


