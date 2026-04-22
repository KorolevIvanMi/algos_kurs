#pragma once

#include <string>

#include "SimCard.h"
#include "Client.h"

struct List{
    long long passport_number;
    long long simcard_number;
    std::string data_of_outcome;
    std::string data_of_end;


    List* prev;
    List* next;

    void AddSimCard();
    void DeleteCard();
    void SortCards();
    
};
