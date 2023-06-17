
#include <iostream>
#include <cstdint>
#include <cstring>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

using namespace std;

#include "bruteforce.hpp"
#include "greedy.hpp"


static void run_tests();

constexpr bool LEFT = true;
constexpr bool RIGHT = false;

int main(void) {
#ifdef DEBUG
    run_tests();
#endif

    size_t stacks_len = 4;
    size_t base_log = 2;
    size_t total_configurations = 1 << (base_log * stacks_len * 2);

    for (size_t i = 0; i < total_configurations; ++i) {
        size_t i_copy = i;

        string left_stack;
        for (int pos = 0; pos < stacks_len; ++pos) {
            left_stack.push_back((i_copy & mask(base_log)) + '0');
            i_copy >>= base_log;
        }
        string right_stack;
        for (int pos = 0; pos < stacks_len; ++pos) {
            right_stack.push_back((i_copy & mask(base_log)) + '0');
            i_copy >>= base_log;
        }

        auto best_brute = find_split_bruteforce(left_stack, right_stack);
        auto best_greedy = find_split_greedy(left_stack, right_stack);

        if (best_brute != best_greedy) {
            std::cout << "l: " << left_stack << " <top" << endl;
            std::cout << "r: " << right_stack << " <top" << endl;
            std::cout << "best:   " << best_brute << endl;
            std::cout << "greedy: " << best_greedy << endl << endl;
        }
    }
}


static void run_tests() {
    assert(rev_order_str("aa", "aaa") == 1);
    assert(rev_order_str("aaa", "aa") == -1);
    assert(rev_order_str("ba", "aa") == -1);
    assert(rev_order_str("aa", "ba") == 1);
    assert(rev_order_str("ba", "ab") == 1);
    assert(rev_order_str("ab", "ba") == -1);
    assert(rev_order_str("xxxba", "yyyab") == 1);
    assert(rev_order_str("zzzab", "wwwba") == -1);
    assert(rev_order_str("aaaaaaa", "aaaaaaa") == 0);
    assert(rev_order_str("", "") == 0);
}

/*

k=1
01,
10 # = 2

k=2
0011,
0101,0110,
1001,1010,1100 # = 6

k=3
000111,
001011,001101,001110,
010011,010101,010110,011001,011010,011100,
100011,100101,100110,101001,101010,101100,110001,110010,110100,111000; # = 20

k=4   # =      70
k=5   # =     252
k=6   # =     924
k=7   # =   3,432
k=8   # =  12,870
k=9   # =  48,620
k=10  # = 184,756

(2k)! / (k!) / (k!)

*/