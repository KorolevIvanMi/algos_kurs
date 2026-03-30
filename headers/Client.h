#pragma once

#include <string>

class Client{
    private:
        std::string passport_number;
        std::string passport_released_data_place;
        std::string fio;
        int birth_age;
        std::string adress;
    public:
        Client();
        Client(std::string, std::string, std::string, int, std::string);
        std::string get_passpport_number();
        
};