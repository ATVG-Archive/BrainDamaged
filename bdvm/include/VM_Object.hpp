//
// Created by atjontv on 5/7/20.
//

#ifndef BRAINDAMAGED_VM_OBJECT_HPP
#define BRAINDAMAGED_VM_OBJECT_HPP

#include "VM_Type.hpp"
#include "VM_Data.hpp"

class VM_Object {
    VM_Type type;
    VM_Data data;

public:
    const bool is_bool() { return type == VM_Type::BOOL; }
    const bool is_i8() { return type == VM_Type::INT8; }
    const bool is_i16() { return type == VM_Type::INT16; }
    const bool is_i32() { return type == VM_Type::INT32; }
    const bool is_i64() { return type == VM_Type::INT64; }
    const bool is_u8() { return type == VM_Type::UINT8; }
    const bool is_u16() { return type == VM_Type::UINT16; }
    const bool is_u32() { return type == VM_Type::UINT32; }
    const bool is_u64() { return type == VM_Type::UINT64; }
    const bool is_f64() { return type == VM_Type::FLOAT64; }

    const bool is_empty() { return !is_i8() && !is_i16() && !is_i32() && !is_i64() && !is_f64(); }

    const bool get_bool() { return data.bl; }
    const i8 get_i8() { return data.bo; }
    const i16 get_i16() { return data.hw; }
    const i32 get_i32() { return data.fw; }
    const i64 get_i64() { return data.dw; }
    const u32 get_u32() { return data.cp; }
    const f64 get_f64() { return data.fl; }

    const i16 get_type() { return type; }

    const void set_bool(const bool val) { data.bl = val; type = VM_Type::BOOL; }
    const void set_i8(const i8 val) { data.bo = val; type = VM_Type::INT8; }
    const void set_i16(const i16 val) { data.hw = val; type = VM_Type::INT16; }
    const void set_i32(const i32 val) { data.fw = val; type = VM_Type::INT32; }
    const void set_i64(const i64 val) { data.dw = val; type = VM_Type::INT64; }
    const void set_u32(const u32 val) { data.cp = val; type = VM_Type::UINT32; }
    const void set_f64(const f64 val) { data.fl = val; type = VM_Type::FLOAT64; }

    const void set_type(const VM_Type newType) { type = newType;}
};

#endif //BRAINDAMAGED_VM_OBJECT_HPP
