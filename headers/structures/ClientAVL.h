#pragma once

#include <string>
#include "Client.h"
#include <vector>


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
    void DeleteTree(AVLNode*&); 
    AVLNode* LeftRotate();
    AVLNode* RightRotate();
    AVLNode* BigLeftRotate();
    AVLNode* BigRightRotate();
    void BalanceTree(AVLNode*&,AVLNode*);


    void AddClient(AVLNode*&, Client); //+
    void deleteClient(AVLNode*&, long long);
    void showAllClients(AVLNode*); //+
    AVLNode* findClientByPassport(AVLNode*&, long long); //+
    std::vector<AVLNode*> findClientByFio(AVLNode*, std::string);
    std::vector<AVLNode*> findClientByAdress(AVLNode*,std::string);
};
