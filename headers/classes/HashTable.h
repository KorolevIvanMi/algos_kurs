#pragma once

#include <string>
#include <SimCard.h>
#include <SimCardHash.h>
#include <vector>


class HashTable{
    private:
        HashSegment** hashTable = new HashSegment* [5];
        int start_element_count = 5;
    public:
        HashTable();

        int doubleHash(long long , int, int); // +
        void showTable(); // +
        void handleTableOverflow(); //+
        int countOccupiedCells(); //+
        void deleteElemen(long long sim_card_number); //+
        void addElem(SimCard new_sim_card); // +
        HashSegment* findSimCardByNumber(long long sim_card_number); //+
        std::vector<HashSegment*> findSimCardByTariff(std::string sim_card_tariff);
};
