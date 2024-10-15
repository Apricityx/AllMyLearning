//
// Created by apricityx on 24-9-19.
//

#include <iostream>
#include <cstring>

#ifndef DATASTRUCTERLEARNING_LINKED_LIST_H
#define DATASTRUCTERLEARNING_LINKED_LIST_H
#endif //DATASTRUCTERLEARNING_LINKED_LIST_H


class Linked {
protected:
    struct Node {
        void *data;
        size_t dataSize;
        Node *next;

        // 修改Node类使得可以存储任意类型的数据
        // 初始化节点示例：Node *node = new Node("Hello World", 12);
        Node(void *data, size_t size) {
            this->data = malloc(size); // 为节点中的数据分配内存
            memcpy(this->data, data, size);  // 将传入的数据输出到节点中
            this->dataSize = size;
            this->next = nullptr;
        }

        ~Node() {
            free(data);  // 释放节点中的数据
        }
    };

public:
    Linked() : head(nullptr) {}

    template<typename T>
    void newFromBegin(const T &data) {
        Node *newNode = new Node((void *) &data, sizeof(data));
        newNode->next = head;
        head = newNode;
    }

    // 未更改
    void showAllData() const {
        Node *pointer = head->next;
        while (pointer != nullptr) {
            // Todo: 如何解引用
            std::cout << pointer->data << std::endl;
            pointer = pointer->next;
        }
    }

    // 获取节点的值，并做简单地类型推理
    template<class T>
    T getValue(Node *node) {
        //Todo: 类型推理
        return *(T *) node->data;
    }

    template<typename T>
    class iterator {
    public:
        iterator() = default;

        // 定义：迭代器实现以下几个功能：
        // 1. 当前指向的元素，用运算符*获取
        // 2. 移动至下一个元素，用运算符++
        // 3. 判断是否到达末尾，用运算符!=

        T &operator*() {
            return current->data;
        }

        iterator &operator++() {
            current = current->next;
            return *this;
        };

        bool operator!=(const iterator &other) const {
            return current != other.current;
        }

    private:
        Node *current;
    };

private:
    Node *head;
};