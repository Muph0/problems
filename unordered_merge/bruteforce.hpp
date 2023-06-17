#pragma once

#include "common.hpp"

static string find_split_bruteforce(stringc a, stringc b) {
    if (a.size() == 0 && b.size() == 0) {
        return "";
    }
    if (a.size() == 0) {
        string result;
        result.append(b);
        return result;
    }
    if (b.size() == 0) {
        string result;
        result.append(a);
        return result;
    }

    string left = find_split_bruteforce(a.substr(0, a.size() - 1), b);
    left.push_back(a.back());

    string right = find_split_bruteforce(a, b.substr(0, b.size() - 1));
    right.push_back(b.back());

    if (rev_order_str(left, right) == -1) return move(right);
    else return move(left);
}


