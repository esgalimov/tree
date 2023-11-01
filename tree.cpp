#include <iostream>
#include <functional>
#include "tree.hpp"

using namespace tree;

int main() {
    rb_tree_t<int, std::less<int>> tr;

    tr.insert(5);
    tr.insert(7);
    tr.insert(3);
    tr.insert(15);
    tr.insert(1);
    tr.insert(9);
    tr.insert(9);
    tr.insert(11);

    tr.insert(1);
    tr.insert(9);
    tr.insert(9);
    tr.insert(13);

    tr.dump();

    auto fst = tr.lower_bound(2);
    std::cout << fst->key_ << " ";
    auto snd = tr.upper_bound(10);

    std::cout << snd->key_ << std::endl;

    std::cout << tr.distance(fst, snd) << std::endl;


    return 0;
}
