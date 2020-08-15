#ifndef BRAINDAMAGED_CHARS_HPP
#define BRAINDAMAGED_CHARS_HPP

#include "config.hpp"
#include "Types.hpp"

LIBBDVM_NAMESPACE_BEGIN

class Chars {
public:
    static void pack(i32 &out, const i32 &a, const i32 &b, const i32 &c, const i32 &d) {
        out = 0;
        out = a       << 24;
        out = out | b << 16;
        out = out | c << 8;
        out = out | d;
    }
    static void unpack(const i32 &in, i32 &a, i32 &b, i32 &c, i32 &d) {
        a = in >> 24 & 0xFF;
        b = in >> 16 & 0xFF;
        c = in >> 8  & 0xFF;
        d = in       & 0xFF;
    }
};

LIBBDVM_NAMESPACE_END
#endif //BRAINDAMAGED_CHARS_HPP
