#include "myvector.h"



int main() {
    short cmd = 1;
    cout << "Меню:" << endl;
    cout << "1. Создание пустого списка" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите команду: ";
    cin >> cmd;
    switch(cmd) {
        case 1:
            break;
        default:
            cout << "Неизвестная команда" << endl;
    }   
    while(cmd) {
        cout << "Меню:" << endl;
        cout << "1. " << endl;
        cout << "2. " << endl;
        cout << "3. " << endl;
        cout << "4. " << endl;
        cout << "5. " << endl;
        cout << "6. " << endl;
        cout << "7. " << endl;
        cout << "8. " << endl;
        cout << "9. " << endl;
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