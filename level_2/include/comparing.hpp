#pragma once

#include <iostream>
#include <set>
#include <chrono>
#include <algorithm>
#include "tree.hpp"


template <typename T>
std::vector<T> get_tree_ans(std::ostream& os, const std::vector<T>& data,
                            const std::vector<T>& get_k_vec, const std::vector<T>& lower_cnt_vec) {
    tree::rb_tree_t<T> tr;
    std::vector<T> tr_ans;
    typename std::vector<T>::const_iterator next_m = get_k_vec.begin();
    typename std::vector<T>::const_iterator next_n = lower_cnt_vec.begin();

    #ifdef COMPARING
    auto start = std::chrono::high_resolution_clock::now();
    #endif

    for (int i = 0, iend = data.size(); i < iend; ++i) {
        if (i != *next_m && i != *next_n) {
            tr.insert(data[i]);
        }
        else if (i == *next_m) {
            tr_ans.push_back(*tr.get_k_smallest_elem(data[i]));
            next_m++;
        }
        else {
           tr_ans.push_back(tr.get_lower_cnt(data[i]));
           next_n++;
        }
    }
    #ifdef COMPARING
    double tm = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - start).count();
    #endif

    for (int i = 0, iend = tr_ans.size(); i < iend; ++i) {
        os << tr_ans[i] << " ";
    }
    #ifdef COMPARING
    os << std::endl << "total rb_tree_t time = " << tm << " microseconds" << std::endl;
    #endif

    #ifdef DUMP
    tr.dump();
    #endif

    return tr_ans;
}

template <typename T>
std::vector<T> get_set_ans(std::ostream& os, const std::vector<T>& data,
                           const std::vector<T>& get_k_vec, const std::vector<T>& lower_cnt_vec) {
    std::set<T> st;
    std::vector<T> st_ans;
    typename std::vector<T>::const_iterator next_m = get_k_vec.begin();
    typename std::vector<T>::const_iterator next_n = lower_cnt_vec.begin();

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0, iend = data.size(); i < iend; ++i) {
        if (i != *next_m && i != *next_n) st.insert(data[i]);
        else if (i == *next_m) {
            if (data[i] >= st.size()) {
                if (st.size() != 0) st_ans.push_back(*std::prev(st.end(), 1));

                else throw std::runtime_error("Set is empty");
            }
            else st_ans.push_back(*std::next(st.begin(), data[i] - 1));
            next_m++;
        }
        else {
            st_ans.push_back(std::distance(st.begin(), st.lower_bound(data[i])));
            next_n++;
        }
    }
    double tm = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - start).count();
    for (int i = 0, iend = st_ans.size(); i < iend; ++i) {
        os << st_ans[i] << " ";
    }
    os << std::endl << "total std::set time = " << tm << " microseconds" << std::endl;

    return st_ans;
}
