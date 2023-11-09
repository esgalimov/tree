#include <iostream>
#include <string>
#include <vector>
#include "comparing.hpp"

int main() {
    std::string str;
    int key = 0, lower = 0, upper = 0, cnt = 0;

    std::vector<int> data, query;

    while (std::cin >> str) {
        if (!str.compare("k")) {
            if (!(std::cin >> key)) {
                std::cerr << "Bad key" << std::endl;
                break;
            }
            data.push_back(key);
        }
        else if (!str.compare("q")) {
            if (!(std::cin >> lower >> upper)) {
                std::cerr << "Bad range" << std::endl;
                break;
            }
            query.push_back(cnt++);
            data.push_back(lower);
            data.push_back(upper);
        }
        else {
            std::cerr << "Bad query" << std::endl;
            break;
        }

        cnt++;
    }

    tree::rb_tree_t tr;
    std::vector<int>::iterator next_q = query.begin();

    #ifdef COMPARING
    auto start = std::chrono::high_resolution_clock::now();
    #endif
    for (int i = 0, iend = data.size(); i < iend; ++i) {
        if (i != *next_q) tr.insert(data[i]);
        else {
            if (data[i] >= data[i + 1]) std::cout << 0 << " ";
            else
                std::cout << tr.distance(tr.lower_bound(data[i]), tr.upper_bound(data[i + 1])) << " ";
            next_q++;
            i++;
        }
    }
    #ifdef COMPARING
    double tm = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - start).count();
    std::cout << std::endl << "total rb_tree_t time = " << tm << " microseconds" << std::endl;

    std::set<int> st;
    next_q = query.begin();

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0, iend = data.size(); i < iend; ++i) {
        if (i != *next_q) st.insert(data[i]);
        else {
            if (data[i] >= data[i + 1]) std::cout << 0 << " ";
            else
                std::cout << std::distance(st.lower_bound(data[i]), st.upper_bound(data[i + 1])) << " ";
            next_q++;
            i++;
        }
    }
    tm = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - start).count();
    std::cout << std::endl << "total std::set time = " << tm << " microseconds" << std::endl;
    #endif

    #ifdef DUMP
    tr.dump();
    #endif
    return 0;
}


