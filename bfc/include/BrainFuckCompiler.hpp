//void
// Created by atjontv on 4/15/20.
//

#ifndef BRAINDAMAGED_BRAINFUCKCOMPILER_HPP
#define BRAINDAMAGED_BRAINFUCKCOMPILER_HPP

#include <vector>
#include <string>
#include "../../bdvm/include/Types.hpp"

class BrainFuckCompiler {
    std::vector<i32> instructions;

    BrainFuckCompiler();

public:
    std::vector<i32> compile(const std::string code);
};

#endif //BRAINDAMAGED_BRAINFUCKCOMPILER_HPP
