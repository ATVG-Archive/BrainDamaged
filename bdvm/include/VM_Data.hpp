//
// Created by atjontv on 5/18/20.
//

#ifndef BRAINDAMAGED_VM_DATA_HPP
#define BRAINDAMAGED_VM_DATA_HPP

#include <Types.hpp>

union VM_Data {
    bool bl;
    i8 bo;
    i16 hw; // Half Word
    i32 fw; // Full Word
    i64 dw; // Double Word
    f64 fl; // Float
    u32 cp; // Char Package
};

#endif //BRAINDAMAGED_VM_DATA_HPP
