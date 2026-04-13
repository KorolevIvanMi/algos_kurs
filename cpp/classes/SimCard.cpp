#include <string>
#include <cmath>
#include "SimCard.h"

SimCard::SimCard(){
    this->number = "111-1111111";
    this->tariff = "Свобода";
    this->birth_age = 2000;
    this->isavailable = true;
}

SimCard::SimCard(std::string number, std::string tariff, int birth_age, bool isavailable){
    this->number = number;
    this->tariff = tariff;
    this->birth_age = birth_age;
    this->isavailable = isavailable;
}

std::string SimCard::get_number(){
    return this->number;
}

std::string SimCard::get_tariff(){
    return this->tariff;
}

int SimCard::get_birth_age(){
    return this->birth_age;
}

bool SimCard::get_isvailable(){
    return this->isavailable;
}

long long SimCard::get_number_int(){
    int sim_length = 9;
    long long sim_number_int = 0;
    for(int i = 0; i < number.length(); i ++){
        if(number[i] == '-'){
            continue;
        }
        else{
            int digit = number[i] - '0';
            sim_number_int += digit * pow(10, sim_length--);
        }
    }

    return sim_number_int;
}