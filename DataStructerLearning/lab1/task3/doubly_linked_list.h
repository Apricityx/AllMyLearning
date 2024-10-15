#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>

// 双向链表
template<typename T>
class DoublyLinkedList {
protected:
    struct Node {
        Node *next;
        Node *prev;
        T item;
    };

    Node *head;
    long length;
    Node *tail;

public:
    DoublyLinkedList();

    [[nodiscard]] long getLength() const;

    void pushFromBegin(const T &item);

    void pushFromEnd(const T &item);

    void popFromBegin();

    void show();

    void show_reverse();

    // 迭代器
    class Iterator {
        friend class DoublyLinkedList;

        explicit Iterator(Node *Ptr);

    protected:
        Node *nodePtr;

    public:
        Iterator operator++();

        Iterator operator--();

        bool operator==(const Iterator &obj) const;

        bool operator!=(const Iterator &obj) const;

        T &operator*() const;
    };

    Iterator begin() const;

    Iterator end() const;

private:
    void init(T item);
};

/* ===========================实现=========================== */

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    length = 0;
    tail = head;
}

template<typename T>
void DoublyLinkedList<T>::init(T item) {
    std::cout << "初始化" << std::endl;
    Node *newNode = new Node{nullptr, nullptr, item};
    head = newNode;
    tail = newNode;
    length++;
}

template<typename T>
void DoublyLinkedList<T>::show() {
    std::cout << "Showing: ";
    for (Node *it = head; it != nullptr; it = it->next) {
        std::cout << it->item << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void DoublyLinkedList<T>::show_reverse() {
    std::cout << "Showing reverse: ";
    for (Node *it = tail; it != nullptr; it = it->prev) {
        std::cout << it->item << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void DoublyLinkedList<T>::pushFromBegin(const T &item) {
    if (head == nullptr) {
        this->init(item);
        return;
    }
    Node *newHead = new Node{head, nullptr, item};
    head->prev = newHead;
    head = newHead;
    length++;
}

template<typename T>
void DoublyLinkedList<T>::pushFromEnd(const T &item) {
    // 将前一个的next设为newNode
    // 将newNode的prev设置为前一个
    // 将newNode的next设置为空
    if (head == nullptr) {
        this->init(item);
        return;
    }
    Node *newNode = new Node{nullptr, tail, item};
    tail->next = newNode;
    tail = newNode;
    // std::cout << "检查prev.next和this是否一致" << std::endl;
    // std::cout << this << "|" << this->tail->prev->next << std::endl;
}

template<typename T>
long DoublyLinkedList<T>::getLength() const {
    return length;
}

// 迭代器
template<typename T>
DoublyLinkedList<T>::Iterator::Iterator(Node *Ptr) {
    nodePtr = Ptr;
}

template<typename T>
T &DoublyLinkedList<T>::Iterator::operator*() const {
    return this->nodePtr->item;
}

template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator++() {
    Iterator temp = *this;
    (*this).nodePtr = (*nodePtr).next;
    return temp;
}

template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator--() {
    Iterator temp = *this;
    (*this).nodePtr = (*nodePtr).prev;
    return temp;
}

template<typename T>
bool DoublyLinkedList<T>::Iterator::operator==(const Iterator &obj) const {
    return nodePtr == obj;
}

template<typename T>
bool DoublyLinkedList<T>::Iterator::operator!=(const Iterator &obj) const {
    return !(nodePtr == obj.nodePtr);
}

// 特殊迭代器
template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() const {
    // std::cout << "begin初始化，通过head：" << head->item << std::endl;
    return Iterator(head);
}

template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() const {
    // std::cout << "end初始化：" << tail->item << std::endl;
    // Node *last = new Node{nullptr, tail, tail->item};
    // std::cout << "end_tail()" << tail->prev << std::endl;
    // std::cout << "end_last()" << last->prev << std::endl;
    return Iterator(tail);
}
#endif // DOUBLY_LINKED_LIST_H
