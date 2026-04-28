#include <string>
#include <iostream>
#include "ClientAVL.h"
#include <vector>

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

void AVLNode::DeleteTree(AVLNode*& root){
    if (root == nullptr)return;
    DeleteTree(root->Right);
    DeleteTree(root->Left);
    delete root;    
    root = nullptr;
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

void AVLNode::showAllClients(AVLNode* root){
    if (root == nullptr) return;
        
        // Сначала обходим левое поддерево
        showAllClients(root->Left);
        
        // Выводим текущего клиента
        std::cout << "Паспорт: " << root->passport_number << std::endl;
        std::cout << "ФИО: " << root->client.get_fio() << std::endl;
        std::cout << "Адрес: " << root->client.get_adress() << std::endl;
        std::cout << "Дата выдачи паспорта: " << root->client.get_passport_released_data_place() << std::endl;
        std::cout << "Год рождения: " << root->client.get_birth_year() << std::endl;
        std::cout << "------------------------" << std::endl;
        
        // Затем обходим правое поддерево
        showAllClients(root->Right);
}

void AVLNode::deleteClient(AVLNode*& mainTree, long long passport_to_del){

    if (mainTree == nullptr){
        return;
    }

    int k = 0;
    AVLNode* elemToDell = mainTree->findClientByPassport(mainTree, passport_to_del);

    if(elemToDell == nullptr){
        std::cout << "Такого пользователя нет!";
        return;
    }

    AVLNode* parent = elemToDell->Prev;
    if (elemToDell->Left == nullptr && elemToDell->Right == nullptr) {
        if (parent != nullptr) {
            if (parent->Left == elemToDell) {
                parent->Left = nullptr;
            }
            else {
                parent->Right = nullptr;
            }
        }
        else {
            mainTree = nullptr;
        }
        delete elemToDell;
    } 
    else if (elemToDell->Left == nullptr || elemToDell->Right == nullptr) {
        AVLNode* child = (elemToDell->Left != nullptr) ? elemToDell->Left : elemToDell->Right;

        if (parent != nullptr) {
            if (parent->Left == elemToDell) {
                parent->Left = child;
            }
            else {
                parent->Right = child;
            }
        }
        else {
            mainTree = child;
        }

        if (child != nullptr) {
            child->Prev = parent;
        }

        delete elemToDell;
    }
    else {
        AVLNode* successor = elemToDell->Right;
        AVLNode* successorParent = elemToDell;

        while (successor->Left != nullptr) {
            successorParent = successor;
            successor = successor->Left;
        }
        AVLNode* originalParent = elemToDell->Prev;

        if (successorParent != elemToDell) {
            successorParent->Left = successor->Right;
            if (successor->Right != nullptr) {
                successor->Right->Prev = successorParent;
            }

            successor->Right = elemToDell->Right;
            if (elemToDell->Right != nullptr) {
                elemToDell->Right->Prev = successor;
            }
        }

        successor->Left = elemToDell->Left;
        if (elemToDell->Left != nullptr) {
            elemToDell->Left->Prev = successor;
        }

        successor->Prev = originalParent;

        if (originalParent != nullptr) {
            if (originalParent->Left == elemToDell) {
                originalParent->Left = successor;
            }
            else {
                originalParent->Right = successor;
            }
        }
        else {
            mainTree = successor;
        }

        delete elemToDell;
        parent = successor;
    }

    if (parent != nullptr) {
        parent->refreshHeight();
        parent->BalanceTree(mainTree, parent);
    }
    else if (mainTree != nullptr) {
        mainTree->refreshHeight();
        mainTree->BalanceTree(mainTree, mainTree);
    }
}

std::vector<AVLNode*> AVLNode::findClientByFio(AVLNode* root, std::string searchString) {
    std::vector<AVLNode*> results;
    
    if (root == nullptr) return results;
    
    // Левый обход
    std::vector<AVLNode*> leftResults = findClientByFio(root->Left, searchString);
    results.insert(results.end(), leftResults.begin(), leftResults.end());
    
    // Проверка текущего узла прямым поиском
    std::string currentFio = root->client.get_fio();
    
    // Алгоритм прямого поиска подстроки
    bool found = false;
    for (int i = 0; i <= (int)currentFio.length() - (int)searchString.length() && !found; i++) {
        int j = 0;
        while (j < searchString.length() && currentFio[i + j] == searchString[j]) {
            j++;
        }
        if (j == searchString.length()) {
            found = true;
        }
    }
    
    if (found) {
        results.push_back(root);
    }
    
    // Правый обход
    std::vector<AVLNode*> rightResults = findClientByFio(root->Right, searchString);
    results.insert(results.end(), rightResults.begin(), rightResults.end());
    
    return results;
}
std::vector<AVLNode*> AVLNode::findClientByAdress(AVLNode* root, std::string searchString) {
    std::vector<AVLNode*> results;

    if (root == nullptr) return results;

    // Обходим левое поддерево
    std::vector<AVLNode*> leftResults = findClientByAdress(root->Left, searchString);
    results.insert(results.end(), leftResults.begin(), leftResults.end());

    // Прямой поиск в тексте текущего узла
    std::string currentAdress = root->client.get_adress();

    // Алгоритм прямого поиска подстроки
    bool found = false;
    for (int i = 0; i <= (int)currentAdress.length() - (int)searchString.length() && !found; i++) {
        int j = 0;
        while (j < searchString.length() && currentAdress[i + j] == searchString[j]) {
            j++;
        }
        if (j == searchString.length()) {
            found = true;
        }
    }

    if (found) {
        results.push_back(root);
    }

    // Обходим правое поддерево
    std::vector<AVLNode*> rightResults = findClientByAdress(root->Right, searchString);
    results.insert(results.end(), rightResults.begin(), rightResults.end());

    return results;
}


void AVLNode::showAllClients2(AVLNode* root, int level) {
    if (root == nullptr) return;
    
    // Выводим отступы для визуализации уровня
    for (int i = 0; i < level; i++) {
        std::cout << "  ";
    }
    
    // Выводим текущий узел (номер паспорта)
    std::cout << "├─ Паспорт: " << root->passport_number;
    
    // Выводим информацию о детях
    std::cout << " [";
    if (root->Left != nullptr) {
        std::cout << "Левый: " << root->Left->passport_number;
    } else {
        std::cout << "Левый: нет";
    }
    
    std::cout << " | ";
    
    if (root->Right != nullptr) {
        std::cout << "Правый: " << root->Right->passport_number;
    } else {
        std::cout << "Правый: нет";
    }
    std::cout << "]" << std::endl;
    
    // Рекурсивно обходим поддеревья с увеличением уровня
    showAllClients2(root->Left, level + 1);
    showAllClients2(root->Right, level + 1);
}