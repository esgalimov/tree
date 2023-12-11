#pragma once

#include <iostream>
#include <vector>

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
