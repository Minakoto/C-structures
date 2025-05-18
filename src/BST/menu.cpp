#include "btree.h"

int main() {
    Btree<int> root;
    // root.add(10, 0);
    // root.add(6, 2);
    // root.add(23, 1);
    // root.add(15, 50);
    // root.add(4, 4);
    // root.add(9, 8);
    // root.add(7, 13);
    // root.add(13, 14);
    // root.add(14, 23);
    // root.del(23);
    // root.del(9);
    // root.del(10);

    root.add(5, 1);
    root.add(1, 10);
    root.add(10, 0);

    root.print();
    // root.add(5, 3);
    // root.add(1, 1);
    // root.add(10, 2);
    // root.list();
    // root.del(5);
    // root.list();
}