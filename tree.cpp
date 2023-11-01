#include <iostream>
#include "tree_debug.hpp"

using namespace tree;

int main() {
    rb_tree_t<int> tr;

    tr.insert(5);
    tr.insert(7);
    tr.insert(9);
    tr.insert(11);
    tr.insert(3);
    tr.insert(15);
    tr.insert(1);
    tr.insert(9);
    tr.insert(1);
    tr.insert(9);
    tr.insert(9);
    tr.insert(13);

    dump(tr);

    auto fst = tr.lower_bound(2);
    auto snd = tr.upper_bound(10);

    std::cout << fst->key_ << " " << snd->key_ << std::endl;

    std::cout << tr.distance(fst, snd) << std::endl;


    return 0;
}
