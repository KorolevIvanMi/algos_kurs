#include "SimCardHash.h"
#include <string>
#include <SimCard.h>

HashSegment::HashSegment(){
    this->number_key = "111-1111111";
    this->hashed_key = -1;
    this->isDeleted = false;
    SimCard my_sim;
    this->sim = my_sim;
}

HashSegment::HashSegment(std::string number_key, int hashed_key, SimCard sim, bool isDeleted){
    this->number_key = number_key;
    this->hashed_key = hashed_key;
    this->sim = sim;
    this->isDeleted = isDeleted;
}