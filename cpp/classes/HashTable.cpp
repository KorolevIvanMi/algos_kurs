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
    // std::cout<<result;
    return result;
}


void HashTable::showTable(){
    for (int i = 0; i < this->start_element_count; i++) {
        if (hashTable[i] != nullptr) {
            if (hashTable[i]->isDeleted) {
                std::cout << "[DELETED]  " << i << "  -" << std::endl;
            }
            else {
                std::cout << hashTable[i]->number_key << "  " << hashTable[i]->hashed_key <<"  "<<hashTable[i]->sim.get_tariff()<<std::endl;
            }
        }
    }
}

int HashTable::countOccupiedCells(){
    int k = 0;
    for (int i = 0; i < this->start_element_count; i ++){
        if (hashTable[i] != nullptr && hashTable[i]->isDeleted == false){
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
            
            while(attempt < 100 && !inserted){
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
                std::cout<< "невозможно вставить такой элемент в таблицу" << std::endl;
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

void HashTable::deleteElemen(long long sim_card_number){
    HashSegment * segment_to_delete = nullptr;
    int delete_index = -1;

    for(int attempt = 0; attempt < 100; attempt ++ ){
        int hashed_index = this->doubleHash(sim_card_number , attempt, this->start_element_count);

        if (hashed_index >= 0 && hashed_index < this->start_element_count &&
            this->hashTable[hashed_index] != nullptr &&
            !this->hashTable[hashed_index]->isDeleted && // Игнорируем уже удаленные
            this->hashTable[hashed_index]->sim.get_number_int() == sim_card_number) {

            segment_to_delete = this->hashTable[hashed_index];
            delete_index = hashed_index;
            break;
        }
    }

    if (segment_to_delete == nullptr){
        std::cout << "Элемент для удаления не найден" << std::endl;
        return;
    }else{
        segment_to_delete->isDeleted = true;
        std::cout << "Элемент удачно удалён !" << std::endl;
    }
}

void HashTable::addElem(SimCard new_sim_card) {
    // Обновляем размер перед проверкой
    int current_size = this->start_element_count; // или getTableSize()
    int occupied_cells = this->countOccupiedCells();
    
    if (occupied_cells == current_size) {
        this->handleTableOverflow();
        current_size = this->start_element_count; // Обновляем размер
    }

    int attempt = 0;
    HashSegment* new_element = new HashSegment;
    new_element->sim = new_sim_card;
    new_element->collision_count = 0;
    new_element->isDeleted = false;
    new_element->number_key = new_sim_card.get_number();

    while (attempt < 100) {
        int hashed_index = this->doubleHash(new_sim_card.get_number_int(), attempt, current_size);
        
        if (hashed_index < 0 || hashed_index >= current_size) {
            attempt++;
            continue;
        }

        if (this->hashTable[hashed_index] == nullptr || 
            this->hashTable[hashed_index]->isDeleted) {
            
            // Очищаем удалённый элемент
            if (this->hashTable[hashed_index] != nullptr) {
                delete this->hashTable[hashed_index];
                this->hashTable[hashed_index] = nullptr;
            }

            new_element->hashed_key = hashed_index;
            new_element->collision_count = attempt;
            this->hashTable[hashed_index] = new_element;
            
            return; // Успешная вставка
        }
        
        attempt++;
    }
    
    // Если дошли сюда - вставка не удалась
    delete new_element; 
}


HashSegment* HashTable::findSimCardByNumber(long long sim_card_number){
    int hashed_key = 0;
    int size = this->start_element_count;
    for( int i = 0; i < 100; i ++){
        hashed_key = this->doubleHash(sim_card_number, i, start_element_count);
        if(hashed_key >= 0 && hashed_key < size){
            if (this->hashTable[hashed_key] == nullptr) {
                return nullptr;
            }
            if (!this->hashTable[hashed_key]->isDeleted && this->hashTable[hashed_key]->sim.get_number_int() == sim_card_number) {
                    return this->hashTable[hashed_key];
            }
        }
    }
    return nullptr;
}

std::vector<HashSegment*> HashTable::findSimCardByTariff(std::string sim_card_tariff){
    std::vector <HashSegment*> results;
    int size = this->start_element_count;

    for(int i = 0; i < size; i ++){
        if(this->hashTable[i] != nullptr && this->hashTable[i]->isDeleted != true){
            if(this->hashTable[i]->sim.get_tariff() == sim_card_tariff){
            results.push_back(this->hashTable[i]);
            }
        }
    }

    return results;
}