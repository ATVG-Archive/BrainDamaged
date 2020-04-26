//
// Created by atjontv on 4/15/20.
//

#ifndef BRAINDAMAGED_BRAINDAMAGEDVM_HPP
#define BRAINDAMAGED_BRAINDAMAGEDVM_HPP

#include <iostream>
#include <vector>
#include <stdio.h>

#include "Bytecode.hpp"
#include "Types.hpp"

// Default memory limit (This extends to upper based on program size)
#define MEMORY_SIZE 8192
// This is the maximum count of Stack locations, after this, the Program Code starts
#define STACK_MAX 4095
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
    const i32 getType(const i32 instruction);
    const i32 getData(const i32 instruction);

    void fetch();
    void decode();
    void execute();
    void doPrimitive();

    const i32 packChars(const i32 c1, const i32 c2, const i32 c3);
    void unpackChars(const i32 i, i32& c1, i32& c2, i32& c3);

    void dumpMemory();

    // VM Utils
    void pop(const i32 i);
    bool exitOnInvalidSP(const std::string& instName, const bool strict);

public:
    BrainDamagedVM();
    void run();
    void loadProgram(const std::vector<i32> prog);
    void setDebug(const bool value) {
        debug = value;
    }
};

#endif //BRAINDAMAGED_BRAINDAMAGEDVM_HPP
