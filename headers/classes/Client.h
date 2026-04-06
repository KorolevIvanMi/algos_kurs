#pragma once

#include <string>

class Client{
    private:
        std::string passport_number;
        std::string passport_released_data_place;
        std::string fio;
        int birth_year;
        std::string adress;
    public:
        Client();
        Client(std::string, std::string, std::string, int, std::string);
        std::string get_passport_number();
        long long get_passport_number_int();
        std::string get_fio();
        std::string get_adress();
        std::string get_passport_released_data_place();
        int get_birth_year();
};