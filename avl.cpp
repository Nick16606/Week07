#include <iostream>
#include <algorithm>
using namespace std;
struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};

NODE* createNode(int data) {
    NODE* newNode = new NODE;
    newNode->key = data;
    newNode->p_left = newNode->p_right = nullptr;
    newNode->height = 1;
    return newNode;
}
int height(NODE* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}
int getBalance(NODE* node) {
    if (node == nullptr)
        return 0;
    return height(node->p_left) - height(node->p_right);
}
void updateHeight(NODE* node) {
    node->height = 1 + max(height(node->p_left), height(node->p_right));
}
NODE* rotateRight(NODE* y) {
    NODE* x = y->p_left;
    NODE* T2 = x->p_right;
    x->p_right = y;
    y->p_left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}
NODE* rotateLeft(NODE* x) {
    NODE* y = x->p_right;
    NODE* T2 = y->p_left;
    y->p_left = x;
    x->p_right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}
void Insert(NODE*& pRoot, int x) {
    if (!pRoot) {
        pRoot = createNode(x);
        return;
    }
    if (x < pRoot->key)
        Insert(pRoot->p_left, x);
    else if (x > pRoot->key)
        Insert(pRoot->p_right, x);
    else
        return;
    updateHeight(pRoot);
    int balance = getBalance(pRoot);
    if (balance > 1 && x < pRoot->p_left->key)
        pRoot = rotateRight(pRoot);
    else if (balance < -1 && x > pRoot->p_right->key)
        pRoot = rotateLeft(pRoot);
    else if (balance > 1 && x > pRoot->p_left->key) {
        pRoot->p_left = rotateLeft(pRoot->p_left);
        pRoot = rotateRight(pRoot);
    }
    else if (balance < -1 && x < pRoot->p_right->key) {
        pRoot->p_right = rotateRight(pRoot->p_right);
        pRoot = rotateLeft(pRoot);
    }
}
NODE* getMinValueNode(NODE* node) {
    NODE* current = node;
    while (current && current->p_left)
        current = current->p_left;
    return current;
}
void Remove(NODE*& pRoot, int x) {
    if (!pRoot) return;
    if (x < pRoot->key)
        Remove(pRoot->p_left, x);
    else if (x > pRoot->key)
        Remove(pRoot->p_right, x);
    else {
        if (!pRoot->p_left || !pRoot->p_right) {
            NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
            delete pRoot;
            pRoot = temp;
        }
        else {
            NODE* temp = getMinValueNode(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }
    if (!pRoot) return;
    updateHeight(pRoot);
    int balance = getBalance(pRoot);
    if (balance > 1 && getBalance(pRoot->p_left) >= 0)
        pRoot = rotateRight(pRoot);
    else if (balance > 1 && getBalance(pRoot->p_left) < 0) {
        pRoot->p_left = rotateLeft(pRoot->p_left);
        pRoot = rotateRight(pRoot);
    }
    else if (balance < -1 && getBalance(pRoot->p_right) <= 0)
        pRoot = rotateLeft(pRoot);
    else if (balance < -1 && getBalance(pRoot->p_right) > 0) {
        pRoot->p_right = rotateRight(pRoot->p_right);
        pRoot = rotateLeft(pRoot);
    }
}
bool isAVL(NODE* pRoot) {
    if (!pRoot) return true;
    int balance = getBalance(pRoot);
    if (abs(balance) > 1) return false;
    return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}
