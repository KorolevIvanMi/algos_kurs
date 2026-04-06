#pragma once

#include <string>
// тут должен быть include Client
struct AVLNode
{
    int passport_number;
    // Client client;
    int height;

    AVLNode* Prev;
    AVLNode* Left;
    AVLNode* Right;

};
