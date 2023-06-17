#include <iostream>
#include "bruteforce.hpp"

using namespace std;

static void print_greedy(stringc l, stringc r) {
    auto best = find_split_bruteforce(l, r);
    std::cout << std::format("l:{}", l) << endl;
    std::cout << std::format("r:{}", r) << endl;
    std::cout << "best: " << best << endl << endl;
}

int main() {

    // print_best("654321321", "154321321");
    // print_best("22345", "12345");

    // print_best("12321", "12321");
    // print_best("12321", "42321");

    // print_best("32123", "32123");
    // print_best("32123", "42123");

    // print_best("212121", "212121");
    // print_best("412121", "212121");

    print_greedy("1243", "4321");
}