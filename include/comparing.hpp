#pragma once

#include <iostream>
#include <set>
#include <chrono>
#include "tree.hpp"

template<typename KeyT = int, typename Comp = std::less<int>>
int get_my_tree_distance(tree::rb_tree_t<KeyT, Comp> &tr, int lower, int upper) {
    auto fst_tr = tr.lower_bound(lower),
         snd_tr = tr.upper_bound(upper);

    // #ifdef COMPARING
    // auto start = std::chrono::high_resolution_clock::now();
    // #endif

    int tr_dist = tr.distance(tr.lower_bound(lower), tr.upper_bound(upper));

    // #ifdef COMPARING
    // double tm = std::chrono::duration_cast<std::chrono::nanoseconds>(
    //         std::chrono::high_resolution_clock::now() - start).count();
    // std::cout << tr_dist << "\n" << "rb_tree_t distance time = " << tm << " nanoseconds" << std::endl;
    // #endif

    return tr_dist;
}

template<typename KeyT = int>
int get_set_distance(std::set<KeyT> &st, int lower, int upper) {
    auto fst_st = st.lower_bound(lower),
         snd_st = st.upper_bound(upper);

    //auto start = std::chrono::high_resolution_clock::now();

    int st_dist = std::distance(fst_st, snd_st);

    // double tm = std::chrono::duration_cast<std::chrono::nanoseconds>(
    //         std::chrono::high_resolution_clock::now() - start).count();
    // std::cout << st_dist << "\n" << "std::set distance time = " << tm << " nanoseconds" << std::endl;

    return st_dist;
}
