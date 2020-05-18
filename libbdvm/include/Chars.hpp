#ifndef BRAINDAMAGED_CHARS_HPP
#define BRAINDAMAGED_CHARS_HPP

#include "config.hpp"
#include <cstdint>

LIBBDVM_NAMESPACE_BEGIN

class Chars {
public:
    static void pack(int32_t &out, const int32_t &a, const int32_t &b, const int32_t &c, const int32_t &d) {
        out = 0;
        out = a       << 24;
        out = out | b << 16;
        out = out | c << 8;
        out = out | d;
    }
    static void unpack(const int32_t &in, int32_t &a, int32_t &b, int32_t &c, int32_t &d) {
        a = in >> 24 & 0xFF;
        b = in >> 16 & 0xFF;
        c = in >> 8  & 0xFF;
        d = in       & 0xFF;
    }
};

LIBBDVM_NAMESPACE_END
#endif //BRAINDAMAGED_CHARS_HPP
