#pragma once

#include <string>

struct Sim_cards_list
{
    std::string passport_number;
    std::string sim_card_number;
    std::string release_date;
    std::string end_date;

    Sim_cards_list* prev;
    Sim_cards_list* next;


    
};
