//
// Created by apricityx on 24-12-3.
//
#include <queue>

#include "bst.h"

int main() {
    BinSearchTree<int> *bst = new BinSearchTree<int>();
    bst->insert(10);
    bst->insert(5);
    bst->insert(4);
    bst->insert(3);
    bst->insert(9);
    bst->insert(11);
    bst->printTree();
    std::cout << "The height of the tree is " << bst->height() << std::endl;
    delete bst;

    int heights[100];
    for (int i = 0; i < 100; i++) {
        BinSearchTree<double> *bst2 = new BinSearchTree<double>();
        for (int j = 0; j < i * 1; j++) {
            double randomNum = rand() %100 / (rand() % 100 + 1.0);
            bst2->insert(randomNum);
        }
        heights[i] = bst2->height();
        delete bst2;
    }
    for (const auto item: heights) {
        std::cout << item << ",";
    }

    return 0;
}
