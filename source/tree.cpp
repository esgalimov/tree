#include <iostream>
#include <string>
#include <vector>
#include "comparing.hpp"

int main() try {
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
    query.push_back(-1);

    std::vector<int> tr_ans = get_tree_ans(std::cout, data, query);
    #ifdef COMPARING
    std::vector<int> st_ans = get_set_ans(std::cout, data, query);
    compare_answers(std::cout, tr_ans, st_ans);
    #endif

    return 0;
}
catch (const std::exception& exc) {
    std::cerr << "Something wrong: " << exc.what() << std::endl;
}


