#include <iostream>
#include "ClientAVL.h"
#include "Client.h"
#include "HashTable.h"
#include "List.h"
#include <cstdlib>
#include <limits>
#include <cmath>
#include <vector>
#include "Validator.h"


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

void initializeTestSimCards(HashTable*& simCardBase) {
    SimCard simcard1("111-1111111", "Эконом", 2020, true);
    SimCard simcard2("222-2222222", "Стандарт", 2021, true);
    SimCard simcard3("333-3333333", "Премиум", 2022, true);
    SimCard simcard4("444-4444444", "Безлимит", 2023, true);
    SimCard simcard5("555-5555555", "Студенческий", 2024, true);
    
    simCardBase->addElem(simcard1);
    simCardBase->addElem(simcard2);
    simCardBase->addElem(simcard3);
    simCardBase->addElem(simcard4);
    simCardBase->addElem(simcard5);

}

int main(int, char**){
    AVLNode* clientBase = nullptr;
    HashTable* simCardBase = new HashTable();
    List* in_out_base = nullptr;
    SimCard* simCard = nullptr;
    Validator validator;

    initializeTestData(clientBase);
    initializeTestSimCards(simCardBase); 
    int command = 0;
    bool exit_flag = false;
    std::string data_of_out = "";
    std::string data_of_end = "";
    std::string available_tariff[] = {"Эконом", "Стандарт","Премиум","Безлимит","Студенческий"}; 

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
        std::cout << "14. Просмотр всех сим карт" << std::endl;
        std::cout << "15. Просмотр всеx занятых симкарт и клиентов" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Введите номер команды: ";
        std::cin >> command;


        std::string passport_number ;
        std::string passport_released_data_place;
        std::string fio;
        int birth_year;
        std::string adress;
        long long passport_number_int;

        std::string simcard_number;
        std::string tariff;
        int birth_age;

        long long simcard_number_int;


        switch(command){
            case 0:
                clientBase->DeleteTree(clientBase);
                simCardBase->DeleteHashTable();
                delete in_out_base;
                exit_flag = true;
                break;
            case 1:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                passport_number = validator.validatePassportNumber();
                
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
                    passport_number_int = new_client.get_passport_number_int();
                    AVLNode* finded_node = clientBase->findClientByPassport(clientBase, passport_number_int);
                    if(finded_node == nullptr){

                        clientBase->AddClient(clientBase, new_client);

                    }else{
                        std::cout << "Такой человек уже существует"<< std::endl;
                    }
                }
            break;
            case 2:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                passport_number_int = validator.validatePassportNumberInt();
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
                passport_number_int = validator.validatePassportNumberInt();;
                {
                    AVLNode* client_node = clientBase->findClientByPassport(clientBase, passport_number_int);
                    Client finded_client = client_node->client;

                    std::cout << "Паспорт: " << passport_number_int << std::endl;
                    std::cout << "ФИО: " << finded_client.get_fio() << std::endl;
                    std::cout << "Адрес: " << finded_client.get_adress() << std::endl;
                    std::cout << "Дата выдачи паспорта: " << finded_client.get_passport_released_data_place() << std::endl;
                    std::cout << "Год рождения: " << finded_client.get_birth_year() << std::endl;
                    std::cout << "Сим карты клиента:"<< std::endl;
                    std::vector<long long> simcards_numbers = in_out_base->findCardsByPassportNumber(in_out_base,passport_number_int);
                    for(long long n: simcards_numbers){
                        std::cout << std::endl << "Номер:" << n;
                    }
                }
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
            case 8:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    
                simcard_number = validator.validateSimCardNumber();

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

                {
                bool flag1 = false;
                do{
                    std::cout << "Введите тариф: ";
                    std::getline(std::cin, tariff);

                    for(int i = 0; i < 4; i ++){
                        if(tariff == available_tariff[i]){
                            flag1 = true;
                        }
                    }
                
                }while(!flag1);
                std::cout << "Введите год выпуска: ";
                std::cin >> birth_age;
                
                std::cin.ignore();
                { 
                     
                    SimCard new_simcard(simcard_number, tariff, birth_age, true);
                    simcard_number_int = new_simcard.get_number_int();
                    HashSegment* if_finded = simCardBase->findSimCardByNumber(simcard_number_int);

                    if(if_finded == nullptr){
                        simCardBase->addElem(new_simcard);
                    }
                    else{
                        std::cout << "Карта с таким номером уже существует !!"<<std::endl;
                    }
                
                }}
                break;
            case 9:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    
                simcard_number_int = validator.validateSimCardNumberInt();
                simCardBase->deleteElemen(simcard_number_int);
            break;
            case 10:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Введите номер карты: ";
                simcard_number_int = validator.validateSimCardNumberInt();
                {
                    HashSegment* finded_sim_card = simCardBase->findSimCardByNumber(simcard_number_int);
                    std::cout << "Номер сим карты: " << finded_sim_card->sim.get_number() << std::endl;
                    std::cout << "Тариф карты: " << finded_sim_card->sim.get_tariff() << std::endl;
                    std::cout << "Год выпуска: " << finded_sim_card->sim.get_birth_age() << std::endl;
                    std::cout << "Доступность: " << finded_sim_card->sim.get_isvailable() << std::endl;
                }
            break;
            case 11:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Введите тариф: ";
                getline(std::cin, tariff);
                {
                    std::vector <HashSegment*> sim_cards = simCardBase->findSimCardByTariff(tariff);
                    for(int i = 0; i < sim_cards.size(); i++){
                        HashSegment* sim_card = sim_cards[i];
                        std::cout << "Номер сим карты: " << sim_card->sim.get_number() << std::endl;
                        std::cout << "Тариф карты: " << sim_card->sim.get_tariff() << std::endl;
                        std::cout << "Год выпуска: " << sim_card->sim.get_birth_age() << std::endl;
                        std::cout << "Доступность: " << sim_card->sim.get_isvailable() << std::endl;
                    }
                }
            break;
            case 12:
	           
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    	        passport_number_int = validator.validatePassportNumberInt();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                simcard_number_int = validator.validateSimCardNumberInt();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Введите дату выдачи: ";
                std::getline(std::cin,data_of_out);

                {
                    AVLNode* client_node = clientBase->findClientByPassport(clientBase, passport_number_int);
                    if(client_node == nullptr){
                        std::cout << "Такого человека не существует!" << std::endl;
                    }
                    else{
                        Client client = client_node->client;
                        HashSegment* finded_sim_card = simCardBase->findSimCardByNumber(simcard_number_int);
                        if(finded_sim_card == nullptr){
                            std::cout<<"Такой сим карты нет!"<<std::endl;
                        }
                        else{
                            if(finded_sim_card->sim.get_isvailable() == false){
                                std::cout << "Эта сим карта уже назначена другому человеку!" << std::endl;
                            }
                            else{

                                List* new_operation = new List;
                                new_operation->passport_number = client.get_passport_number_int();
                                new_operation->simcard_number = finded_sim_card->sim.get_number_int();
                                new_operation->data_of_outcome = data_of_out;
                                new_operation->data_of_end = "";
                                finded_sim_card->sim.set_isavailable(false); 
                                in_out_base->AddSimCard(in_out_base, new_operation);
                                in_out_base->SortCards(in_out_base);
                            }
                        }
                    }
                }
            break;
            case 13:
                
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                passport_number_int = validator.validatePassportNumberInt();
               
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                simcard_number_int = validator.validateSimCardNumberInt();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout <<"Введите дату снятия с обслуживания" ;
                std::getline(std::cin, data_of_end);
                {
                    simcard_number_int = in_out_base->DeleteCard(in_out_base, passport_number_int, data_of_end);
                    HashSegment* finded_sim_card = simCardBase->findSimCardByNumber(simcard_number_int);
                    finded_sim_card->sim.set_isavailable(true);
                }
            break;
            case 14:
                simCardBase->showTable();
            break;
            case 15:
                in_out_base->showList(in_out_base);
            break;
            default:
                std::cout << "Такой команды нет"<< std::endl<< std::endl<< std::endl;
                break;
        }

    }while(!exit_flag);

}
