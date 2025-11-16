#include <iostream>
#include <list>

#include "linked_list.h"

template<class T>

struct treeNode {
    T data;

    treeNode *left;

    treeNode *right;
};

enum childType {
    left,
    right
};

template<class T>
treeNode<int> *createNode(treeNode<T> *fatherNode, T data, childType t) {
    treeNode<T> *newNode = new treeNode<T>;
    newNode->data = data;
    if (t == left) {
        fatherNode->left = newNode;
    } else {
        fatherNode->right = newNode;
    }
    return newNode;
}

template<class T>
void inorder(treeNode<T> *rootNode) {
    if (rootNode == nullptr) {
        return;
    }
    inorder(rootNode->left);
    std::cout << rootNode->data << std::endl;
    inorder(rootNode->right);
}

int main() {
    treeNode<int> *rootNode = new treeNode<int>;
    rootNode->data = 1;
    createNode(createNode(rootNode, 2, left), 3, right);
    createNode(rootNode, 4, right);
    inorder(rootNode);
    return 0;
}
