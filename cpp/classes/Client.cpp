#include <string>
#include <cmath>
#include "Client.h"

Client::Client(){
    this->passport_number = "1111-111111";
    this->passport_released_data_place = "06.06.2026 ул.Калатушкина д.12 к.1";
    this->fio = "Иванов Иван Иванович";
    this->birth_year = 1990;
    this->adress = "ул.Калатушкина д.12 к.1";
}

Client::Client(std::string passport_number, std::string passport_released_data_place, std::string fio , int birth_year, std::string adress){
    this->passport_number = passport_number;
    this->passport_released_data_place = passport_released_data_place;
    this->fio = fio;
    this->birth_year = birth_year;
    this->adress = adress;
}

std::string Client::get_passport_number(){
    return passport_number;
}

long long Client::get_passport_number_int(){
    int passport_length = 9;
    long long passport_number_int = 0;
    for(int i = 0; i < passport_number.length(); i ++){
        if(passport_number[i] == '-'){
            continue;
        }
        else{
            int digit = passport_number[i] - '0';
            passport_number_int += digit * pow(10, passport_length--);
        }
    }

    return passport_number_int;
}

std::string Client::get_fio(){
    return fio;
}

std::string Client::get_adress(){
    return adress;
}

std::string Client::get_passport_released_data_place(){
    return passport_released_data_place;
}

int Client::get_birth_year(){
    return birth_year;
}

