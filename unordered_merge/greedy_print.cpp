#include <iostream>
#include "greedy.hpp"

using namespace std;

static void print_greedy(stringc l, stringc r) {
    auto result = find_split_greedy(l, r);
    std::cout << std::format("l:{}", l) << endl;
    std::cout << std::format("r:{}", r) << endl;
    std::cout << "best: " << result << endl << endl;
}

int main() {
    print_greedy("0010", "1000");
}