#include <iostream>
#include "ClientAVL.h"
#include "Client.h"
#include <cstdlib>


int main(int, char**){
    AVLNode* clientBase = nullptr;

    int command = 0;
    bool exit_flag = false;

    do{
        // system("clear");
        std::cout << "\n========== Обслужаивание клиентов оператора сотовой связи ==========" << std::endl;
        std::cout << "1. Регистрация нового клиента" << std::endl;
        std::cout << "2. Снять клиента с обслуживания" << std::endl;
        std::cout << "3. Просмотр всех зарегестрированных клиентов" << std::endl;
        std::cout << "4. Очистка данных о клиентах" << std::endl;
        std::cout << "5. Поиск клиента по номеру паспорта" << std::endl;
        std::cout << "6. Поиск клиента по ФИО" << std::endl;
        std::cout << "7. Поиск клиента по адресу" << std::endl;
        std::cout << "8. Добавление новой сим карты" << std::endl;
        std::cout << "9. Удаление сим карты" << std::endl;
        std::cout << "10. Поиск сим карты по номеру" << std::endl;
        std::cout << "11. Поиск сим карты по тарифу" << std::endl;
        std::cout << "12. Регистрация выдачи сим карты клиенту" << std::endl;
        std::cout << "13. Регистрация возврата сим карты клиенту" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Введите номер команды: ";
        std::cin >> command;

        switch(command){
            case 0:
                exit_flag = true;
                break;
            case 1:
                std::cout << "Привет мир !!" << std::endl<< std::endl<< std::endl;
                break;
            default:
                std::cout << "Такой команды нет"<< std::endl<< std::endl<< std::endl;
                break;
        }

    }while(!exit_flag);

}
