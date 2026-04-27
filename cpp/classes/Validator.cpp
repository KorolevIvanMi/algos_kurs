#include "Validator.h"
#include <cctype>
#include <string>
#include <iostream>
#include <limits>
std::string Validator::validateSimCardNumber() {
    std::string simCardNumber;
    bool isValid;
    
    do {
        isValid = true;
        std::cout << "\nВведите номер сим карты (формат NNN-NNNNNNN): ";
        std::cin >> simCardNumber;
        
        // Проверка длины: 3 цифры + дефис + 7 цифр = 11 символов
        if (simCardNumber.length() != 11) {
            std::cout << "Ошибка! Номер должен содержать 11 символов (NNN-NNNNNNN)\n";
            isValid = false;
            continue;
        }
        
        // Проверка каждого символа
        for (int i = 0; i < simCardNumber.length(); i++) {
            if (i == 3) {
                // На позиции 3 (4-й символ) должен быть дефис
                if (simCardNumber[i] != '-') {
                    std::cout << "Ошибка! На позиции 4 должен быть дефис '-'\n";
                    isValid = false;
                    break;
                }
            } else {
                // На остальных позициях должны быть цифры
                if (!std::isdigit(simCardNumber[i])) {
                    std::cout << "Ошибка! Символ '" << simCardNumber[i] 
                              << "' не является цифрой\n";
                    isValid = false;
                    break;
                }
            }
        }
        
        if (!isValid) {
            std::cout << "Попробуйте снова. Пример правильного формата: 123-4567890\n";
        }
        
    } while (!isValid);
    
    return simCardNumber;
}

std::string Validator::validatePassportNumber(){

    std::string passportNumber;
    bool isValid = false;
    
    do {
        isValid = true;
        std::cout << "\nВведите номер паспорта (формат NNNN-NNNNNN): ";
        std::cin >> passportNumber;
        
        // Проверка длины: 4 цифры + дефис + 6 цифр = 11 символов
        if (passportNumber.length() != 11) {
            std::cout << "Ошибка! Номер паспорта должен содержать 11 символов (NNNN-NNNNNN)\n";
            isValid = false;
            continue;
        }
        
        // Проверка каждого символа
        for (int i = 0; i < passportNumber.length(); i++) {
            if (i == 4) {
                // На позиции 4 (5-й символ) должен быть дефис
                if (passportNumber[i] != '-') {
                    std::cout << "Ошибка! На позиции 5 должен быть дефис '-'\n";
                    isValid = false;
                    break;
                }
            } else {
                // На остальных позициях должны быть цифры
                if (!std::isdigit(passportNumber[i])) {
                    std::cout << "Ошибка! Символ '" << passportNumber[i] 
                              << "' не является цифрой\n";
                    isValid = false;
                    break;
                }
            }
        }
        
        if (!isValid) {
            std::cout << "Попробуйте снова. Пример правильного формата: 1234-567890\n";
        }
        
    } while (!isValid);
    
    return passportNumber;
}

long long Validator::validatePassportNumberInt() {
    long long passportNumber;
    bool isValid;
    
    do {
        isValid = true;
        std::cout << "\nВведите номер паспорта (10 цифр, без дефиса): ";
        std::cin >> passportNumber;
        
        if (std::cin.fail()) {
            std::cin.clear(); // Сбрасываем флаг ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите число.\n";
            isValid = false;
            continue;
        }
        
        if (passportNumber < 0) {
            std::cout << "Ошибка! Номер паспорта не может быть отрицательным.\n";
            isValid = false;
            continue;
        }
        
        if (passportNumber < 1000000000 || passportNumber > 9999999999LL) {
            std::cout << "Ошибка! Номер паспорта должен содержать ровно 10 цифр.\n";
            isValid = false;
        }
    } while (!isValid);
    
    return passportNumber;
}

long long Validator::validateSimCardNumberInt(){
    long long simcardNumber;
    bool isValid;
    
    do {
        isValid = true;
        std::cout << "\nВведите номер сим-карты (10 цифр, без дефиса): ";
        std::cin >> simcardNumber;
        
        if (std::cin.fail()) {
            std::cin.clear(); // Сбрасываем флаг ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите число.\n";
            isValid = false;
            continue;
        }
        
        if (simcardNumber < 0) {
            std::cout << "Ошибка! Номер сим-карты не может быть отрицательным.\n";
            isValid = false;
            continue;
        }
        
        if (simcardNumber < 1000000000 || simcardNumber > 9999999999LL) {
            std::cout << "Ошибка! Номер сим-карты должен содержать ровно 10 цифр.\n";
            std::cout << "Пример: 1234567890\n";
            isValid = false;
            continue;
        }
        
    } while (!isValid);
    
    return simcardNumber;
}
