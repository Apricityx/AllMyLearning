#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include <vector>
#ifndef NULL
#define NULL 0
#endif
template<typename T>
class BinSearchTree {
public:
    class Iterator; //very important!!!

private:
    struct Node {
        T item;
        Node *parent;
        Node *left;
        Node *right;
    }; // Node

    Node *root;

    int count;

public:
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


//************************the following is the implmentation of the bst class interfaces***********************************
template<typename T>
BinSearchTree<T>::BinSearchTree(): root(nullptr), count(0) {
    //Please implement this!
}

template<typename T>
int BinSearchTree<T>::size() const {
    // 定义递归 lambda
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
    // 定义一个递归的辅助函数来计算树的高度
    auto calculateHeight = [](Node *node, auto &&self) -> int {
        if (node == nullptr) {
            return 0; // 空节点的高度是 0
        }

        // 递归计算左子树和右子树的高度，取最大值加 1
        int leftHeight = self(node->left, self);
        int rightHeight = self(node->right, self);

        return std::max(leftHeight, rightHeight) + 1;
    };

    // 调用辅助函数从根节点开始计算树的高度
    return calculateHeight(root, calculateHeight);
}


template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::insert(const T &item) {
    if (root == nullptr) {
        root = new Node;
        root->item = item;
        return Iterator(root);
    }

    Node *current = root;
    while (true) {
        if (current->item == item) {
            return Iterator(current); // 找到了现有节点
        } else if (item < current->item) {
            if (current->left == nullptr) {
                current->left = new Node;
                current->left->item = item;
                return Iterator(current->left);
            } else {
                current = current->left;
            }
        } else {
            if (current->right == nullptr) {
                current->right = new Node;
                current->right->item = item;
                return Iterator(current->right);
            } else {
                current = current->right;
            }
        }
    }
}

template<typename T>
void BinSearchTree<T>::printTree() {
    std::vector<std::vector<T> > result;

    auto printNextDepth = [this, &result](Node *curr, auto &&self, int depth = 0) {
        if (curr == nullptr) {
            return;
        }
        // 如果当前深度没有对应的 vector，进行添加
        if (result.size() <= depth) {
            result.push_back(std::vector<T>());
        }
        result[depth].push_back(curr->item);
        // 递归遍历左子树和右子树
        self(curr->left, self, depth + 1);
        self(curr->right, self, depth + 1); // todo
    };
    printNextDepth(root, printNextDepth);
    std::cout << "The tree is:" << std::endl;
    std::cout << "Result size: " << result.size() << std::endl;     // todo
    for (size_t depth = 0; depth < result.size(); ++depth) {
        std::cout << "Depth " << depth << ": ";
        for (const T &item: result[depth]) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
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
    // 定义一个递归的辅助函数来删除树中的每个节点
    // auto deleteTree = [](Node *node, auto &&self) {
    //     if (node == NULL) {
    //         return;
    //     }
    //     std::cout << "Deleting node with value: " << node->item << std::endl;
    //
    //     // 递归删除左子树和右子树
    //     self(node->left, self);
    //     self(node->right, self);
    //
    //     // 删除当前节点
    //     delete node;
    // };
    //
    // // 从根节点开始删除树中的所有节点
    // deleteTree(root, deleteTree);
}


template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::begin() {
    //not finished
    return Iterator();
}

template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::end() {
    //not finished
    return Iterator();
}

//************************the following is the implmentation of the iterator inner class***********************************
template<typename T>
BinSearchTree<T>::Iterator::Iterator(Node *currNode) {
    curr = currNode;
}

template<typename T>
BinSearchTree<T>::Iterator::Iterator() {
    curr = nullptr;
}

template<typename T>
typename BinSearchTree<T>::Iterator &BinSearchTree<T>::Iterator::operator++() {
    //not finished
    return Iterator();
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
