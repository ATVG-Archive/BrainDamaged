//
// Created by atjontv on 4/15/20.
//

#ifndef BRAINDAMAGED_BRAINDAMAGEDVM_HPP
#define BRAINDAMAGED_BRAINDAMAGEDVM_HPP

#include <iostream>
#include <vector>

#include "Bytecode.hpp"
#include "Types.hpp"

class BrainDamagedVM {
    i32 pc = 100;
    i32 sp = 0;
    std::vector<i32> memory;
    i32 typ = 0;
    i32 dat = 0;
    i32 running = 1;
    bool debug = 0;

    // Instruction = 0xFFcccccc where FF = Instruction and cccccc = Data
    i32 getType(i32 instruction);
    i32 getData(i32 instruction);

    void fetch();
    void decode();
    void execute();
    void doPrimitive();

public:
    BrainDamagedVM();
    void run();
    void loadProgram(std::vector<i32> prog);
};

#endif //BRAINDAMAGED_BRAINDAMAGEDVM_HPP
