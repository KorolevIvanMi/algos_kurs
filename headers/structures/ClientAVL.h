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
    int GetHeight();
    void DeleteTree();
    void LeftRotate();
    void RightRotate();
    void BigLeftRotate();
    void BigRightRotate();
    void BalanceTree(AVLNode*&);


    void AddClient(Client);
    void deleteClient(long long);
    void showAllClients();
    void deleteAllClients();
    void findClientByPassport(long long);
    void findClientByFio(std::string);
    void findClientByAdress(std::string);
};
