#include <string>
#include <iostream>
#include "ClientAVL.h"

void AVLNode::refreshHeight(){
    AVLNode* current = this;
    while(current != nullptr){
        int leftH = current->Left ? current->Left->height : -1;
        int rightH = current->Right ? current->Right->height : -1;
        current->height = std::max(leftH, rightH) + 1;
        current = current->Prev;
    }
}

int AVLNode::GetHeight(AVLNode* node){
    if (node == nullptr) {
        return -1;
    }
    return node->height;
}

void AVLNode::DeleteTree(AVLNode* root){
    if (root == nullptr)return;
    DeleteTree(root->Right);
    DeleteTree(root->Left);
    delete root;    
}

AVLNode* AVLNode::LeftRotate() {
    AVLNode* oldRoot = this;
    AVLNode* newRoot = this->Right;
    
    if (newRoot == nullptr) return oldRoot;
    
    AVLNode* leftSubtreeOfNewRoot = newRoot->Left;

    newRoot->Left = oldRoot;
    oldRoot->Right = leftSubtreeOfNewRoot;
    
    newRoot->Prev = oldRoot->Prev;
    oldRoot->Prev = newRoot;
    
    if (leftSubtreeOfNewRoot != nullptr) {
        leftSubtreeOfNewRoot->Prev = oldRoot;
    }
    
    if (newRoot->Prev != nullptr) {
        if (newRoot->Prev->Left == oldRoot) {
            newRoot->Prev->Left = newRoot;
        } else {
            newRoot->Prev->Right = newRoot;
        }
    }
    
    oldRoot->refreshHeight();
    newRoot->refreshHeight();
    
    return newRoot;  
}

AVLNode* AVLNode::RightRotate() {
    AVLNode* oldRoot = this;
    AVLNode* newRoot = this->Left;
    if (newRoot == nullptr) return oldRoot;

    AVLNode* rightSubtreeOfNewRoot = newRoot->Right;

    newRoot->Right = oldRoot;
    oldRoot->Left = rightSubtreeOfNewRoot;

    newRoot->Prev = oldRoot->Prev;
    oldRoot->Prev = newRoot;
    if (rightSubtreeOfNewRoot != nullptr) {
        rightSubtreeOfNewRoot->Prev = oldRoot;
    }

    if (newRoot->Prev != nullptr) {
        if (newRoot->Prev->Left == oldRoot) {
            newRoot->Prev->Left = newRoot;
        }
        else {
            newRoot->Prev->Right = newRoot;
        }
    }

    oldRoot->refreshHeight();
    newRoot->refreshHeight();

    return newRoot;
}

AVLNode* AVLNode::BigLeftRotate() {
    if (this == nullptr || this->Right == nullptr) return this;
    this->Right = this->Right->RightRotate();
    AVLNode* newRoot = this->LeftRotate();
    return newRoot;
}

AVLNode* AVLNode::BigRightRotate() {
    if (this == nullptr || this->Left == nullptr) return this;
    this->Left = this->Left->LeftRotate();
    AVLNode* newRoot = this->RightRotate();
    return newRoot;
}

void AVLNode::BalanceTree(AVLNode*& root, AVLNode* newNode) {
    if (newNode == nullptr) return;
    
    AVLNode* current = newNode;
    while (current != nullptr) {
        // Обновляем высоту
        int leftHeight = current->Left ? current->Left->height : -1;
        int rightHeight = current->Right ? current->Right->height : -1;
        current->height = std::max(leftHeight, rightHeight) + 1;
        
        int balance = rightHeight - leftHeight;
        AVLNode* parent = current->Prev;
        
        // Балансировка
        if (balance == 2) {
            if (current->Right != nullptr) {
                int rightBalance = (current->Right->Right ? current->Right->Right->height : -1) - 
                                    (current->Right->Left ? current->Right->Left->height : -1);
                
                AVLNode* newSubtreeRoot;
                if (rightBalance >= 0) {
                    newSubtreeRoot = current->LeftRotate();
                } else {
                    newSubtreeRoot = current->BigLeftRotate();
                }
                
                // Обновляем связь с родителем
                if (parent != nullptr) {
                    if (parent->Left == current) {
                        parent->Left = newSubtreeRoot;
                    } else {
                        parent->Right = newSubtreeRoot;
                    }
                }
                current = newSubtreeRoot;
            }
        } 
        else if (balance == -2) {
            if (current->Left != nullptr) {
                int leftBalance = (current->Left->Right ? current->Left->Right->height : -1) - 
                                    (current->Left->Left ? current->Left->Left->height : -1);
                
                AVLNode* newSubtreeRoot;
                if (leftBalance <= 0) {
                    newSubtreeRoot = current->RightRotate();
                } else {
                    newSubtreeRoot = current->BigRightRotate();
                }
                
                // Обновляем связь с родителем
                if (parent != nullptr) {
                    if (parent->Left == current) {
                        parent->Left = newSubtreeRoot;
                    } else {
                        parent->Right = newSubtreeRoot;
                    }
                }
                current = newSubtreeRoot;
            }
        }
        
        // Обновляем корень
        if (current->Prev == nullptr) {
            root = current;
        }
        
        current = current->Prev;
    }
}

void AVLNode::AddClient(AVLNode*& root, Client client){
    long long client_passport_number = client.get_passport_number_int();
    AVLNode* mainTree = root;
    if(!root){
        root = new AVLNode;
        root->client = client;
        root->passport_number = client_passport_number;
        root->height = 0;
        root->Right = nullptr;
        root->Left = nullptr;
        root->Prev = nullptr;
        mainTree = root;
    }
    else{
        while(true){
            if(client_passport_number < mainTree->passport_number){
                if(mainTree->Left){
                    mainTree = mainTree->Left;
                }
                else{
                    mainTree->Left = new AVLNode;
                    mainTree->Left->client = client;
                    mainTree->Left->passport_number = client_passport_number;
                    mainTree->Left->height = 0;
                    mainTree->Left->Left = nullptr;
                    mainTree->Left->Right = nullptr;
                    mainTree->Left->Prev = mainTree;
                    mainTree->Left->refreshHeight();
                    break;
                }
            }
            else{
                if(mainTree->Right){
                    mainTree = mainTree->Right;
                }
                else{
                    mainTree->Right = new AVLNode;
                    mainTree->Right->client = client;
                    mainTree->Right->height = 0;
                    mainTree->Right->passport_number = client_passport_number;
                    mainTree->Right->Left = nullptr;
                    mainTree->Right->Right = nullptr;
                    mainTree->Right->Prev = mainTree;
                    mainTree->Right->refreshHeight();
                    break;
                }
            }
        }
        root->BalanceTree(root, mainTree);
    }
}


AVLNode* AVLNode::findClientByPassport(AVLNode*& root, long long client_passport){
    AVLNode* current = root;
    while(true){
        if(current->passport_number == client_passport){
            std::cout << "Найдет человек, инфу выведу потом ";
            return current;
        }
        if (current->passport_number > client_passport && current->Left){
            current = current->Left;
        }
        else if (current->passport_number < client_passport && current->Right){
            current = current->Right;
        }
        else{
            return nullptr;
        }
    }
    return nullptr;
}