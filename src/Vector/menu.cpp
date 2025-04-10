#include "clvector.h"

int main() {
    short cmd = 1; 
    while(cmd) {
        cout << "Меню:" << endl;
        cout << "1. Создание списка" << endl;
        cout << "2. Добавление элемента" << endl;
        cout << "3. Удаление элемента" << endl;
        cout << "4. Первоначальная установка итератора" << endl;
        cout << "5. Первоначальная установка обратного итератора" << endl;
        cout << "6. Сдвиг итератора вперед" << endl;
        cout << "7. Сдвиг итератора назад" << endl;
        cout << "8. Сдвиг обратного итератора вперед" << endl;
        cout << "9. Сдвиг обратного итератора назад" << endl;
        cout << "10. Получить значение на позиции итератора" << endl;
        cout << "11. Получить значение на позиции обратного итератора" << endl;
        cout << "12. Изменить значение на позиции итератора" << endl;
        cout << "13. Изменить значение на позиции обратного итератора" << endl;
        cout << "14. Количество элементов в списке" << endl;
        cout << "15. Емкость списка" << endl;
        cout << "16. Проверка на пустоту" << endl;
        cout << "17. Тестирование" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите команду: ";
        cin >> cmd;
        switch(cmd) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 0:
                break;
            default:
                cout << "Неизвестная команда" << endl;
        }
    }
    
}