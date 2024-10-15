#include <iostream>
#include "linked_list.h"

int main() {
    Linked<int> link_obj;
    for (int i = 0; i < 100; i++) {
        link_obj.push_front(i + 1);
    }
    for (Linked<int>::Iterator it = link_obj.begin(); it != link_obj.end(); ++it) {
        std::cout << *it << " ";
    }

    return 0;
}
