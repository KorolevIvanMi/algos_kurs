#pragma once

#include <string>

class SimCard{
    private:
        std::string number;
        std::string tariff;
        int birth_age;
        bool isavailable;
    public:
        SimCard();
        SimCard(std::string, std::string, int, bool );
        std::string get_number();
        
};