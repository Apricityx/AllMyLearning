#include "company.h"
#include "doubly_linked_list.h"

int main() {
    Company cmp;
    cmp.inputEmployee();
    cmp.findBestPaid();
    cmp.findBestPaidReverse();
    cmp.printBestPaid();
    return 0;
}
