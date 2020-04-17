//
// Created by atjontv on 4/15/20.
//

#ifndef BRAINDAMAGED_BRAINDAMAGEDVM_HPP
#define BRAINDAMAGED_BRAINDAMAGEDVM_HPP

#include <iostream>
#include <vector>
#include <stdio.h>

#ifdef linux
#include <libgen.h>
#endif

#include "Bytecode.hpp"
#include "Types.hpp"

#define MEMROY_SIZE 1000000
#define PC_BEGIN 4096
#define IN_BYTE_MAX 1024

#define TXT_BEGIN 0x00000002
#define TXT_END 0x00000003
#define NEW_LINE 0x0000000a

class BrainDamagedVM {
    i32 pc = PC_BEGIN;
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

    i32 packChars(const i32 c1, const i32 c2, const i32 c3);
    void unpackChars(const i32 i, i32& c1, i32& c2, i32& c3);

    // VM Utils
    void pop(i32 i);
    bool exitOnInvalidSP(std::string instName);

public:
    BrainDamagedVM();
    void run();
    void loadProgram(std::vector<i32> prog);
};

#endif //BRAINDAMAGED_BRAINDAMAGEDVM_HPP
