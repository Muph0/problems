#pragma once

#include <algorithm>
#include "common.hpp"

static string find_split_greedy(stringc a, stringc b) {
    string result, monot;

    auto ai = a.crbegin(), a_end = a.crend();
    auto bi = b.crbegin(), b_end = b.crend();

    auto monot_flush = [&]() {
        bool falling = monot.size() <= 1 || monot.front() >= monot.back();
        if (falling) {
            result.append(monot);
            result.append(monot);
        } else {
            std::merge(
                monot.cbegin(), monot.cend(), // a
                monot.cbegin(), monot.cend(), // b
                std::back_inserter(result) // output
            );
        }
        monot.clear();
        };

reconsider:
    while (ai != a_end && bi != b_end) {
        bool falling = monot.size() <= 1 || monot.front() >= monot.back();

        if (*ai == *bi) {
            bool monot_broken = monot.size() > 0
                && monot.front() != monot.back() && (falling
                    ? *ai > monot.back()
                    : *ai < monot.back());

            if (monot_broken) {
                char last = monot.back();
                monot.pop_back();
                monot_flush();
                monot.push_back(last);
            }

            monot.push_back(*ai);
            ai++;
            bi++;
        } else {
            char smaller = std::min(*ai, *bi);

            if (monot.size() > 0 && smaller < monot.front()) {
                result.append(monot);
            } else {
                monot_flush();
            }

            result.push_back(smaller);
            if (smaller == *ai) {
                ai++;
                bi -= monot.size();
            } else {
                bi++;
                ai -= monot.size();
            }
            monot.clear();
        }
    }

    // remainder
    auto ri = ai;
    auto r_end = a_end;
    if (ai == a_end) {
        ri = bi;
        r_end = b_end;
    }

    if (ri != r_end) {
        if (monot.size() == 0) {
            result.append(ri, r_end);
            if (ri == ai) ai = a_end; else bi = b_end;
        } else {
            if (*ri < monot.front()) {
                result.append(monot);
                result.push_back(*ri);
                if (ri == ai) {
                    ai++;
                    bi -= monot.size();
                } else {
                    bi++;
                    ai -= monot.size();
                }
                monot.clear();
            } else {
                monot_flush();
            }
            goto reconsider;
        }
    } else {
        monot_flush();
    }

    assert(monot.size() == 0);
    assert(ai == a_end);
    assert(bi == b_end);

    std::reverse(result.begin(), result.end());
    return result;
}