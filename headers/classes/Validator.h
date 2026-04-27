#pragma once

#include <string>



class Validator{
public:
    long long validatePassportNumberInt();
    long long validateSimCardNumberInt();
    std::string  validateSimCardNumber();
    std::string validatePassportNumber();

};
