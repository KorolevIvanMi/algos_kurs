#include "List.h"
#include <iostream>
#include <algorithm>


void List::AddSimCard(List*& head, List* new_operation){
    if (head == nullptr){
	head = new_operation;
	head->prev = head;
	head->next = head;
	return;
    }
    List* tail = head->prev;
    new_operation->next = head;
    new_operation->prev = tail;
    tail->next = new_operation;
    head->prev = new_operation;
    head = new_operation; 
    
}

long long List::DeleteCard(List*& head, long long passport_number, std::string data){
    long long passport_number_head = head->passport_number;
    
    List* current = head;
    do{
        if (current->passport_number == passport_number){
			current->data_of_end = data;
			return current->simcard_number;
		}
		current = current->next;
    } while (current->passport_number != passport_number_head);
    return 0;
}


void List::showList(List* head){
    if (head == nullptr){
        return;
    }
    
    List* current = head;
    List* start = head;  // Запоминаем начальный элемент
    
    do {
        std::cout <<"Владелец: "<< current->passport_number << "  " 
                  <<"Номер карты: " <<current->simcard_number << "  "  
                  <<"Дата выпуски карты: "<<current->data_of_outcome << "  "  
                  <<"Дата возврата карты:"<< current->data_of_end << std::endl;
        current = current->next;
    } while (current != start);  // Сравниваем указатели, а не номера
}

void List::SortCards(List*& head) {
    if (head == nullptr || head->next == head) {
        return;
    }

    std::vector<List*> nodes;
    List* current = head;
    List* start = head;

    do {
        nodes.push_back(current);
        current = current->next;
    } while (current != start);

    // Изменено: сортировка по simcard_number
    std::sort(nodes.begin(), nodes.end(),
        [](const List* a, const List* b) {
            return a->simcard_number < b->simcard_number;  // ← теперь по номеру карты
        });

    for (size_t i = 0; i < nodes.size(); i++) {
        nodes[i]->next = nodes[(i + 1) % nodes.size()];
        nodes[i]->prev = nodes[(i + nodes.size() - 1) % nodes.size()];
    }

    head = nodes[0];
}


std::vector<long long> List::findCardsByPassportNumber(List* head, long long passport_number){
    std::vector<long long> result;
    if(head == nullptr){
        return result;
    }

    List* current = head;
    List* start = head;  // Запоминаем начальный элемент

    do{
        if(current->passport_number == passport_number){
            result.push_back(current->simcard_number);
        }
        current = current->next;
    } while(current != start);  // Сравниваем указатели, а не номера паспортов

    return result;
}
