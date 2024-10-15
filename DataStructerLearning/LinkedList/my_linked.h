//
// Created by apricityx on 24-9-19.
//

#include <iostream>

#ifndef DATASTRUCTERLEARNING_LINKED_LIST_H
#define DATASTRUCTERLEARNING_LINKED_LIST_H
#endif //DATASTRUCTERLEARNING_LINKED_LIST_H

class Linked {
protected:
    template<typename T>
    struct Node {
        T data;
        Node *next;
    };

public:
    Linked() {
        head.next = nullptr;
    }

    template<typename T>
    Node<T> *newFromBegin(T data) {
        Node<T> *newNode = new Node<T>;
        newNode->next = head.next;
        this->head.next = newNode;
        newNode->data = data;
        return newNode;
    }

    template<class T>
    Node<T> newFromEnd(T data) {

    }

    void showAllData() const {
        Node<int> *pointer = head.next;
        while (pointer != nullptr) {
            std::cout << pointer->data << std::endl;
            pointer = pointer->next;
        }
    }

    class iterator {

    public:

    private:

    };

private:
    Node<int> head;
};