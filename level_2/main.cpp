#include <iostream>
#include <string>
#include <vector>
#include "comparing.hpp"
#include "cmp_answers.hpp"

int main() try {
    std::string str;
    int key = 0, num = 0, cnt = 0;

    std::vector<int> data, get_k_vec, lower_cnt_vec;

    while (std::cin >> str) {
        if (!str.compare("k")) {
            if (!(std::cin >> key)) {
                std::cerr << "Bad key" << std::endl;
                break;
            }
            data.push_back(key);
        }
        else if (!str.compare("m")) {
            if (!(std::cin >> num)) {
                std::cerr << "Bad range" << std::endl;
                break;
            }
            get_k_vec.push_back(cnt);
            data.push_back(num);
        }
        else if (!str.compare("n")) {
            if (!(std::cin >> num)) {
                std::cerr << "Bad range" << std::endl;
                break;
            }
            lower_cnt_vec.push_back(cnt);
            data.push_back(num);
        }
        else {
            std::cerr << "Bad query" << std::endl;
            break;
        }
        cnt++;
    }
    get_k_vec.push_back(-1);
    lower_cnt_vec.push_back(-1);

    std::vector<int> tr_ans = get_tree_ans(std::cout, data, get_k_vec, lower_cnt_vec);
    #ifdef COMPARING
    std::vector<int> st_ans = get_set_ans(std::cout, data, get_k_vec, lower_cnt_vec);
    compare_answers(std::cout, tr_ans, st_ans);
    #endif

    //for (auto ans : tr_ans) std::cout << ans << " ";

    return 0;
}
catch (const std::exception& exc) {
    std::cerr << "Something wrong: " << exc.what() << std::endl;
    return 1;
}
