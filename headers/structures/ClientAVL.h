#pragma once

#include <string>
// тут должен быть include Client
struct AVLNode
{
    int passport_number;
    // Client client;


    AVLNode* parent;
    AVLNode* older_child;
    AVLNode* youngest_child;

};
