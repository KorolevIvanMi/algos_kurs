#pragma once

#include <string>
#include <SimCard.h>
#include <SimCardHash.h>

class HashTable{
    private:
        HashSegment** hashTable = new HashSegment* [100];
        int start_element_count = 100;
    public:
        HashTable();

        int doubleHash(long long , int, int); // +
        void showTable(); // +
        void handleTableOverflow();
        int countOccupiedCells(); //+
        void deleteElemen(long long sim_card_number);
        void addElem(HashSegment new_sim_card);
        HashSegment* findSimCardByNumber(long long sim_card_number);
        HashSegment* findSimCardByTariff(std::string sim_card_tariff);
};