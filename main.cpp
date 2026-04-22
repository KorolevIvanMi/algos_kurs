#include <iostream>
#include "ClientAVL.h"
#include "Client.h"
#include "HashTable.h"
#include <cstdlib>
#include <limits>
#include <cmath>
#include <vector>

void initializeTestData(AVLNode*& root) {
    Client client1("12 34 567890", "ОВД Ленинского района г. Москвы", "Иванов Иван Иванович", 1985, "г. Москва, ул. Ленина, д. 1, кв. 10");
    Client client2("23 45 678901", "УФМС Центрального района", "Петров Петр Петрович", 1990, "г. Санкт-Петербург, Невский пр., д. 20, кв. 5");
    Client client3("34 56 789012", "Отдел УФМС по Кировской области", "Сидорова Анна Сергеевна", 1988, "г. Киров, ул. Свободы, д. 15, кв. 42");
    Client client4("45 67 890123", "МВД по Республике Татарстан", "Кузнецов Алексей Николаевич", 1975, "г. Казань, ул. Баумана, д. 7, кв. 12");
    Client client5("56 78 901234", "УФМС по Свердловской области", "Смирнова Елена Викторовна", 1995, "г. Екатеринбург, ул. Мира, д. 33, кв. 78");
    
    root->AddClient(root, client1);
    root->AddClient(root, client2);
    root->AddClient(root, client3);
    root->AddClient(root, client4);
    root->AddClient(root, client5);
}



int main(int, char**){
    AVLNode* clientBase = nullptr;

    initializeTestData(clientBase);
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


        std::string passport_number ;
        std::string passport_released_data_place;
        std::string fio;
        int birth_year;
        std::string adress;
        long long passport_number_int;

        switch(command){
            case 0:
                exit_flag = true;
                break;
            case 1:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Введите номер паспорта: ";
                std::getline(std::cin, passport_number);

                std::cout << "Введите дату и место выдачи паспорта: ";
                std::getline(std::cin, passport_released_data_place);

                std::cout << "Введите ФИО клиента: ";
                std::getline(std::cin, fio);

                std::cout << "Введите дату рождения клиента: ";
                std::cin >> birth_year;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Введите адрес проживания клиента: ";
                std::getline(std::cin, adress);
                {
                    Client new_client(passport_number, passport_released_data_place, fio, birth_year, adress);
                    clientBase->AddClient(clientBase, new_client);
                }
            break;
            case 2:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Введите номер паспорта: ";
                std::cin>> passport_number_int;
                clientBase->deleteClient(clientBase, passport_number_int);

            break;

            case 3:
                clientBase->showAllClients(clientBase);
            break;

            case 4:
                clientBase->DeleteTree(clientBase);
                
            break;
            case 5:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Введите номер паспорта: ";
                std::cin>> passport_number_int;
                {
                    AVLNode* client_node = clientBase->findClientByPassport(clientBase, passport_number_int);
                    Client finded_client = client_node->client;

                    std::cout << "Паспорт: " << passport_number_int << std::endl;
                    std::cout << "ФИО: " << finded_client.get_fio() << std::endl;
                    std::cout << "Адрес: " << finded_client.get_adress() << std::endl;
                    std::cout << "Дата выдачи паспорта: " << finded_client.get_passport_released_data_place() << std::endl;
                    std::cout << "Год рождения: " << finded_client.get_birth_year() << std::endl;
                    std::cout << "Добавить вывод по сим картам"<< std::endl;
                    std::cout << "------------------------" << std::endl;
                }
                clientBase->findClientByPassport(clientBase, passport_number_int);
            break;
            case 6:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Введите ФИО клиента: ";
                std::getline(std::cin, fio);
                {
                    std::vector <AVLNode*> vec = clientBase->findClientByFio(clientBase, fio);
                    for (int i = 0; i < vec.size(); i ++){
                        AVLNode* client_node = vec[i];
                        Client finded_client = vec[i]->client;

                        std::cout << "Паспорт: " << finded_client.get_passport_number_int() << std::endl;
                        std::cout << "ФИО: " << finded_client.get_fio() << std::endl;
                        std::cout << "Адрес: " << finded_client.get_adress() << std::endl;
                        std::cout << "Дата выдачи паспорта: " << finded_client.get_passport_released_data_place() << std::endl;
                        std::cout << "Год рождения: " << finded_client.get_birth_year() << std::endl;
                        std::cout << "Добавить вывод по сим картам"<< std::endl;
                        std::cout << "------------------------" << std::endl;
                    }
                }
                
            break;
            case 7:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Введите адрес проживания клиента: ";
                std::getline(std::cin, adress);
                {
                    std::vector <AVLNode*> vec = clientBase->findClientByAdress(clientBase, adress);
                    for (int i = 0; i < vec.size(); i ++){
                        AVLNode* client_node = vec[i];
                        Client finded_client = vec[i]->client;

                        std::cout << "Паспорт: " << finded_client.get_passport_number_int() << std::endl;
                        std::cout << "ФИО: " << finded_client.get_fio() << std::endl;
                        std::cout << "Адрес: " << finded_client.get_adress() << std::endl;
                        std::cout << "Дата выдачи паспорта: " << finded_client.get_passport_released_data_place() << std::endl;
                        std::cout << "Год рождения: " << finded_client.get_birth_year() << std::endl;
                        std::cout << "Добавить вывод по сим картам"<< std::endl;
                        std::cout << "------------------------" << std::endl;
                    }
                }
            break;
            default:
                std::cout << "Такой команды нет"<< std::endl<< std::endl<< std::endl;
                break;
        }

    }while(!exit_flag);

}
