#pragma once

#include <string>
#include <format>
#include <stdexcept>

#define DEBUG

#define _QUOTE(x) #x
#define QUOTE(x) _QUOTE(x)

#ifdef DEBUG
#define assert(expr, ...) if (!(expr)) throw std::logic_error(string(__PRETTY_FUNCTION__) + ":" QUOTE(__LINE__) ": " #expr " " __VA_ARGS__)
#else
#define assert(expr, msg)
#endif

using string = std::string;
using stringc = const std::string_view&;

static constexpr size_t mask(int bits) { return (1 << bits) - 1; }

/**
 *  0 => a = b
 *  1 => a < b
 * -1 => a > b
 */
static int rev_order_str(stringc a, stringc b) {
    auto ai = a.crbegin();
    auto bi = b.crbegin();

    while (ai != a.crend() && bi != b.crend()) {
        char ch_a = *(ai++);
        char ch_b = *(bi++);

        auto diff = ch_b - ch_a;
        if (diff != 0) return diff > 0 ? 1 : -1;
    }

    if (bi != b.crend()) return 1;
    if (ai != a.crend()) return -1;

    return 0;
}