#include <iostream>

#include "doubly_linked_list.h"
int main() {
    DoublyLinkedList<int> list;
    list.pushFromBegin(4);
    list.pushFromBegin(3);
    list.pushFromBegin(2);
    list.pushFromBegin(1);
    list.pushFromEnd(1);
    list.pushFromEnd(2);git rev-list --objects --all | grep "$(git verify-pack -v .git/objects/pack/pack-*.idx | sort -k 3 -n | tail -n 10 | awk '{print$1}')"

    list.pushFromEnd(3);
    list.pushFromEnd(4);
    // list.pushFromEnd(2);
    list.show();
    list.show_reverse();
    std::cout << *list.end() << std::endl;
    std::cout << *list.begin() << std::endl;
    for (DoublyLinkedList<int>::Iterator it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    for (DoublyLinkedList<int>::Iterator it = list.end(); it != list.begin(); --it) {
        std::cout << *it << " ";
    }
    return 0;
}
