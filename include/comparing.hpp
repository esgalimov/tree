#pragma once

#include <iostream>
#include <set>
#include <chrono>
#include "tree.hpp"


template <typename T>
void compare_answers(std::ostream& os, const std::vector<T>& tr_ans, const std::vector<T>& st_ans) {
    if (tr_ans.size() != st_ans.size())
        os << "\033[1;31mERROR\033[0m" << std::endl;
    else {
        bool same = true;
        for (int i = 0, iend = st_ans.size(); i < iend; ++i) {
            if (tr_ans[i] != st_ans[i]) same = false;
        }
        if (same) os << "\033[32mCORRECT \033[0m" << std::endl;
        else      os << "\033[1;31mERROR\033[0m" << std::endl;
    }
}

template <typename T>
std::vector<T> get_tree_ans(std::ostream& os, const std::vector<T>& data, const std::vector<T>& query) {
    tree::rb_tree_t<T> tr;
    std::vector<T> tr_ans;
    typename std::vector<T>::const_iterator next_q = query.begin();

    #ifdef COMPARING
    auto start = std::chrono::high_resolution_clock::now();
    #endif
    for (int i = 0, iend = data.size(); i < iend; ++i) {
        if (i != *next_q) tr.insert(data[i]);
        else {
            if (data[i] >= data[i + 1]) tr_ans.push_back(0);
            else
                tr_ans.push_back(tr.distance(tr.lower_bound(data[i]), tr.upper_bound(data[i + 1])));
            next_q++;
            i++;
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
std::vector<T> get_set_ans(std::ostream& os, const std::vector<T>& data, const std::vector<T>& query) {
    std::set<T> st;
    std::vector<T> st_ans;
    typename std::vector<T>::const_iterator next_q = query.begin();

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0, iend = data.size(); i < iend; ++i) {
        if (i != *next_q) st.insert(data[i]);
        else {
            if (data[i] >= data[i + 1]) st_ans.push_back(0);
            else
                st_ans.push_back(std::distance(st.lower_bound(data[i]), st.upper_bound(data[i + 1])));
            next_q++;
            i++;
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
