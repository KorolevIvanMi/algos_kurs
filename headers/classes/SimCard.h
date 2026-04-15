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
        long long get_number_int();
        std::string get_tariff();
        int get_birth_age();
        bool get_isvailable();

        SimCard& operator=(const SimCard& other);
};