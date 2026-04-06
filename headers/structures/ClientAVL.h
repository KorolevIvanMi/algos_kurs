#pragma once

#include <string>
#include "Client.h"



struct AVLNode
{
    long long passport_number;
    Client client;
    int height;

    AVLNode* Prev;
    AVLNode* Left;
    AVLNode* Right;


    void refreshHeight(); 
    int GetHeight(AVLNode*); 
    void DeleteTree(AVLNode*); 
    AVLNode* LeftRotate();
    AVLNode* RightRotate();
    AVLNode* BigLeftRotate();
    AVLNode* BigRightRotate();
    void BalanceTree(AVLNode*&,AVLNode*);


    void AddClient(AVLNode*&, Client); //+
    void deleteClient(AVLNode*&, long long);
    void showAllClients(AVLNode*);
    // void deleteAllClients(AVLNode*&); по сути равно удалению дерева
    AVLNode* findClientByPassport(AVLNode*&, long long); //+
    void findClientByFio(AVLNode*&, std::string);
    void findClientByAdress(AVLNode*&,std::string);
};
