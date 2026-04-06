#include <string>
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