#include <string>
#include <iostream>

#include "HashTable.h"
#include "SimCardHash.h"
#include "SimCard.h"

HashTable::HashTable(){
    for(int i = 0; i < this->start_element_count; i++){
        hashTable[i] = nullptr;
    }
}

int HashTable::doubleHash(long long key, int attempt, int size){
    int hash1 = 0;
    std::string key_string = std::to_string(key);
    for(int i = 0; i < key_string.length() ; i ++){
        hash1 += key_string[i];
    }
    hash1 = (hash1 - 490) * 9;
    int hash2 = 0;
    for(int i = 0; i < key_string.length(); i ++){
        hash2 = 31*hash2 + key_string[i];
    }
    hash2 = abs(hash2);
    int result = (hash1 + hash2 * attempt) % size;
    std::cout<<result;
    return result;
}


void HashTable::showTable(){
    for (int i = 0; i < this->start_element_count; i++) {
        if (hashTable[i] != nullptr) {
            if (hashTable[i]->isDeleted) {
                std::cout << "[DELETED]  " << i << "  -" << std::endl;
            }
            else {
                std::cout << hashTable[i]->number_key << "  " << hashTable[i]->hashed_key << std::endl;
            }
        }
    }
}

int HashTable::countOccupiedCells(){
    int k = 0;
    for (int i = 0; i < this->start_element_count; i ++){
        if (hashTable[i] != nullptr or hashTable[i]->isDeleted == false){
            k ++;
        }
    }
    return k;
}


void HashTable::handleTableOverflow(){
    std::cout << "Таблица переполнена, выполняю увелечение..." << std::endl;

    int new_size = this->start_element_count * 2;
    HashSegment** newTable = new HashSegment * [new_size];
    for (int i = 0; i < new_size; i ++){
        newTable[i] = nullptr;
    }

    for(int i = 0; i < this->start_element_count; i ++){
        if (this->hashTable[i] != nullptr && this->hashTable[i]->isDeleted != true){
            HashSegment* old_segment = this->hashTable[i];
            bool inserted = false;
            int attempt = 0;
            
            while(attempt < 10 && !inserted){
                long long int_number_key = old_segment->sim.get_number_int();
                int new_index = this->doubleHash(int_number_key, attempt, new_size);

                if (new_index >= 0 && new_index < new_size &&
                    (newTable[new_index] == nullptr || newTable[new_index]->isDeleted)) {
                    // Вставляем элемент в новую таблицу
                    HashSegment* new_segment = new HashSegment;
                    new_segment->collision_count = old_segment->collision_count;
                    new_segment->hashed_key = new_index;
                    new_segment->isDeleted = false;
                    new_segment->number_key = old_segment->number_key;
                    new_segment->sim = old_segment->sim;

                    newTable[new_index] = new_segment;
                    inserted = true;
                }
                else {
                    attempt++;
                }
            }

            if (!inserted){
                for(int j = 0; j < new_size && !inserted; j++){
                    if (newTable[j] == nullptr || newTable[j]->isDeleted) {
                        HashSegment* new_segment = new HashSegment;
                        new_segment->collision_count = old_segment->collision_count;
                        new_segment->hashed_key = j;
                        new_segment->isDeleted = false;
                        new_segment->number_key = old_segment->number_key;
                        new_segment->sim = old_segment->sim;

                        newTable[j] = new_segment;
                        inserted = true;
                    }
                }
            }
        }


        if (this->hashTable[i] != nullptr) {
            delete this->hashTable[i];
            this->hashTable[i] = nullptr;
        }
    }

    delete[] this->hashTable;
    this->start_element_count = new_size;

    this->hashTable = newTable;

}