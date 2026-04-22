#pragma once

#include <string>
#include <SimCard.h>


struct  HashSegment{
    std::string number_key;
    int hashed_key;
    SimCard sim;
    bool isDeleted;
    int collision_count;
    
    HashSegment();
    HashSegment(std::string, int, SimCard, bool);

};
