#ifndef BST_H
#define BST_H

#include <iostream>
#ifndef NULL
#define NULL 0
#endif
template<typename T>
class BinSearchTree {
    // class Iterator; //very important!!!

private:
    struct Node {
        T item;
        Node *parent;
        Node *left;
        Node *right;
    }; // Node重声明时有不同的可访问性

    Node *root;

    int count;

public:
    class Iterator {
        friend class BinSearchTree<T>;

    private:
        Node *curr;

        Iterator(Node *currNode);

    public:
        Iterator();

        Iterator &operator++();

        Iterator &operator--();

        T &operator*() const;

        bool operator==(const Iterator &otherIterator) const;
    }; // Iterator
    // Postcondition: this BinSearchTree is empty.
    BinSearchTree(); //  default constructor

    // Postcondition: the number of items in this BinSearchTree
    //                has been returned.
    int size() const;

    // Postcondition: the height of this BinSearchTree
    //                has been returned.
    int height() const;

    // Postcondition: item has been inserted into this BinSearchTree. An iterator
    //                positioned at the inserted item has been returned. The
    //                averageTime(n) is O(log n) and worstTime(n) is O(n).
    Iterator insert(const T &item);

    // Postcondition: if there is an item in this BinSearchTree that equals item,
    //                the value returned is an iterator pointing to that item.
    //                Otherwise, the value returned is an iterator with the same
    //                value as the iterator returned by the end( ) method.  The
    //                averageTime(n) is O(log n) and worstTime(n) is O(n).
    Iterator find(const T &item) const;

    // Precondition: itr is positioned at an item in this BinSearchTree.
    // Postcondition: the item that itr is positioned at has been deleted from
    //                this BinSearchTree.  The averageTime(n) is O(log n)
    //                and worstTime(n) is O(n).
    void erase(Iterator itr);

    // Postcondition: The space allocated for this BinSearchTree has been
    //                deallocated.  The worstTime(n) is O(n).
    ~BinSearchTree();

    // Postcondition: The tree-shape of this BinSearchTree has been printed
    void printTree();

    // Postcondition: if this BinSearchTree is non-empty, an iterator positioned
    //                at the smallest item in the tree has been returned.
    //                Otherwise, the iterator returned has the same value as the
    //                iterator returned by the end( ) method.
    Iterator begin();


    // Postcondition: the value returned is an iterator that can be used in a
    //                comparison for ending the traversal of this BinSearchTree.
    //                If this BinSearchTree is non-empty, the largest item is in the
    //                position just before the position of the iterator returned.
    Iterator end();
}; // BinSearchTree


//************************the following is the implementation of the bst class interfaces***********************************
template<typename T>
int BinSearchTree<T>::size() const {
    // 定义递归 lambda时必须传递一个自身的引用
    auto searchNext = [](Node *node, auto &&self) -> int {
        if (node == nullptr) {
            return 0; // 空节点计为 0
        }
        // 当前节点 + 左子树大小 + 右子树大小
        return 1 + self(node->left, self) + self(node->right, self);
    };

    // 从根节点开始计算大小
    return searchNext(root, searchNext);
}


template<typename T>
int BinSearchTree<T>::height() const {
    //Please implement this!
    int maxHeight = 0;
    auto searchNext = [&maxHeight,this,searchNext](const int height, Node x) {
        maxHeight = height > maxHeight ? height : maxHeight;
        if (x.left != NULL) {
            searchNext(height + 1, x.left);
        } else if (x.right != NULL) {
            searchNext(height + 1, x.right);
        }
    };
    return maxHeight;
}

template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::insert(const T &item) {
    //Please implement this!
    if (root == nullptr) {
        root = new Node;
        root->item = item;
        return Iterator(root);
    }
    if (root->item == item) {
        return Iterator(root);
    }

    Iterator searchNext = [this, item, searchNext](Node x) {
        if (x.item == item) {
            return Iterator(x);
        }
        if (x.item > item) {
            if (x.left == NULL) {
                x.left = new Node;
                x.left->item = item;
                return Iterator(x.left);
            }
            searchNext(x.left);
        } else {
            if (x.right == NULL) {
                x.right = new Node;
                x.right->item = item;
                return Iterator(x.right);
            }
            searchNext(x.right);
        }
    };
    return searchNext(*root);
}

template<typename T>
void BinSearchTree<T>::printTree() {
    //Please think about how to implement this.
    // 左在上，右在下

}

template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::find(const T &item) const {
    //not finished
    return Iterator();
}


template<typename T>
void BinSearchTree<T>::erase(Iterator itr) {
    //not finished
}

template<typename T>
BinSearchTree<T>::~BinSearchTree() {
    //Please implement this!
}

template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::begin() {
    //not finished
    return Iterator(root);
}

template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::end() {
    //not finished
    return Iterator();
}

//
// Created by apricityx on 24-12-3.
//
#include "bst.h"

template<typename T>
BinSearchTree<T>::BinSearchTree(): count(0) {
    root = NULL;
    //Please implement this!
}



//************************the following is the implementation of the iterator inner class***********************************
template<typename T>
BinSearchTree<T>::Iterator::Iterator(Node *currNode) {
    curr = currNode;
}

template<typename T>
BinSearchTree<T>::Iterator::Iterator(): curr(nullptr) {
}

template<typename T>
typename BinSearchTree<T>::Iterator &BinSearchTree<T>::Iterator::operator++() {
    if (!curr) {
        throw std::logic_error("Iterator is not pointing to a valid node");
    }

    auto findMin = [](Node *node) -> Node * {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    };

    if (curr->right) {
        curr = findMin(curr->right);
    } else {
        Node *parent = curr->parent;
        while (parent && curr == parent->right) {
            curr = parent;
            parent = parent->parent;
        }
        curr = parent;  // 如果为空，说明已经到达树的末尾
    }

    return *this;
}


template<typename T>
typename BinSearchTree<T>::Iterator &BinSearchTree<T>::Iterator::operator--() {
    //not finished
    return Iterator();
}

template<typename T>
T &BinSearchTree<T>::Iterator::operator*() const {
    return curr->item;
}

template<typename T>
bool BinSearchTree<T>::Iterator::operator==(const Iterator &otherIterator) const {
    //not finished
    return false;
}

#endif
