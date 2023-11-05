#include <iostream>
#include <string>
#include "comparing.hpp"

int main() {
    std::string query;
    int key   = 0,
        lower = 0,
        upper = 0;

    tree::rb_tree_t<> tr;
    #ifdef COMPARING
    std::set<int> st;
    #endif

    while (std::cin >> query) {
        if (!query.compare("k")) {
            if (!(std::cin >> key)) {
                std::cerr << "Bad key" << std::endl;
                break;
            }
            tr.insert(key);
            #ifdef COMPARING
            st.insert(key);
            #endif
        }
        else if (!query.compare("q")) {
            if (!(std::cin >> lower >> upper)) {
                std::cerr << "Bad range" << std::endl;
                break;
            }
            if (lower >= upper) {
                std::cout << 0 << " ";
            }
            else {
                int tr_dist = get_my_tree_distance(tr, lower, upper);

                #ifndef COMPARING
                std::cout << tr_dist << " ";
                #endif


                #ifdef COMPARING
                int st_dist = get_set_distance(st, lower, upper);

                if (tr_dist == st_dist) std::cout << "\033[32mCORRECT \033[0m" << std::endl;
                else std::cout << "\033[1;31mERROR\033[0m" << std::endl;
                #endif
            }
        }
        else {
            std::cerr << "Bad query" << std::endl;
            break;
        }
    }
    #ifdef DUMP
    tr.dump();
    #endif
    return 0;
}


