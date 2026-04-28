#pragma once

#include <string>
#include <vector>

#include "SimCard.h"
#include "Client.h"

struct List{
    long long passport_number;
    long long simcard_number;
    std::string data_of_outcome;
    std::string data_of_end;



    List* prev;
    List* next;

    void AddSimCard(List*& head, List* new_operation);
    long long DeleteCard(List*& head, long long passport_number,long long sim_card_number, std::string data);
    void SortCards(List*&);
    void showList(List* head);
    std::vector <long long> findCardsByPassportNumber(List* head, long long passport_number); 

};
