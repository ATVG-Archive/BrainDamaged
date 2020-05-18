//
// Created by atjontv on 5/7/20.
//

#ifndef BRAINDAMAGED_VM_OBJECT_HPP
#define BRAINDAMAGED_VM_OBJECT_HPP

#include <Types.hpp>

enum VM_Type {
    NONE,
    INT8,
    INT16,
    INT32,
    INT64,
    FLOAT64
};

union VM_Data {
    i8 bo;
    i16 hw; // Half Word
    i32 fw; // Full Word
    i64 dw; // Double Word
    f64 fl; // Float
};

class VM_Object {
    VM_Type type;
    VM_Data data;

public:
    const bool is_i8() { return type == VM_Type::INT8; }
    const bool is_i16() { return type == VM_Type::INT16; }
    const bool is_i32() { return type == VM_Type::INT32; }
    const bool is_i64() { return type == VM_Type::INT64; }
    const bool is_f64() { return type == VM_Type::FLOAT64; }

    const bool is_empty() { return !is_i8() && !is_i16() && !is_i32() && !is_i64() && !is_f64(); }

    const i8 get_i8() { return data.bo; }
    const i16 get_i16() { return data.hw; }
    const i32 get_i32() { return data.fw; }
    const i64 get_i64() { return data.dw; }
    const f64 get_f64() { return data.fl; }

    const void set_i8(const i8 val) { data.bo = val; type = VM_Type::INT8; }
    const void set_i16(const i16 val) { data.hw = val; type = VM_Type::INT16; }
    const void set_i32(const i32 val) { data.fw = val; type = VM_Type::INT32; }
    const void set_i64(const i64 val) { data.dw = val; type = VM_Type::INT64; }
    const void set_f64(const f64 val) { data.fl = val; type = VM_Type::FLOAT64; }

    const void set_type(const VM_Type newType) { type = newType;}
};

#endif //BRAINDAMAGED_VM_OBJECT_HPP
