#include <iostream>
#include "tree_debug.hpp"

using namespace tree;

int main() {
    rb_tree_t<int> tr;

    // tr.insert(1);
    // tr.insert(2);
    // tr.insert(6);
    // tr.insert(4);
    // tr.insert(3);
    // tr.insert(10);
    // tr.insert(9);
    // dump(tr);
    // tr.insert(5);
    // dump(tr);

    tr.insert(10);
    tr.insert(9);
    tr.insert(8);
    tr.insert(7);
    tr.insert(6);
    tr.insert(5);
    tr.insert(4);
    tr.insert(3);
    tr.insert(2);
    tr.insert(1);
    dump(tr);

    return 0;
}
