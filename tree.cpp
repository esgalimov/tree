#include <iostream>
#include <functional>
#include "tree.hpp"

using namespace tree;

int main() {
    //using tree_t = typename rb_tree_t<int, std::less<int>>;

    rb_tree_t<int, std::less<int>> *tr = new rb_tree_t<int, std::less<int>>;

    tr->insert(9);
    tr->insert(9);
    tr->insert(11);

    tr->insert(5);
    tr->insert(7);
    tr->insert(3);
    tr->insert(15);
    tr->insert(1);

    tr->insert(1);
    tr->insert(9);
    tr->insert(9);
    tr->insert(13);

    tr->dump();

    rb_tree_t<int, std::less<int>> tr2{std::move(*tr)};

    delete tr;


    tr2.dump();

    auto fst = tr2.lower_bound(2);
    std::cout << fst->key_ << " ";
    auto snd = tr2.upper_bound(10);

    std::cout << snd->key_ << std::endl;

    std::cout << tr2.distance(fst, snd) << std::endl;


    return 0;
}
