//
// Created by atjontv on 4/15/20.
//

#ifndef BRAINDAMAGED_BRAINDAMAGEDVM_HPP
#define BRAINDAMAGED_BRAINDAMAGEDVM_HPP

#include <iostream>
#include <vector>
#include <stdio.h>

// TODO: Replace <fmt/format.h> with <format> when Clang stdc++ supports it
#include <fmt/format.h>

#include <Chars.hpp>
#include <Types.hpp>
#include <Bytecode.hpp>

#include "VM_Object.hpp"

#define MEMORY_SIZE 8192
#define PC_BEGIN 1

#define VM_TRUE 1
#define VM_FALSE 2

// IO
#define IO_READ_BUFFER_MAX 1024

// Text
#define TXT_BEGIN 0x02
#define TXT_END 0x03
#define TXT_NEW_LINE 0x0a

class BrainDamagedVM {
    // Program Counter
    i32 pc = PC_BEGIN;
    // Stack Pointer
    i32 sp = 0;

    // Memory (RAM)
    std::vector<VM_Object> memory;

    // Program (ROM)
    std::vector<instruction_t> programCode;

    // Current Instruction
    instruction_t inst{};

    // VM Running State
    bool running = 1;
    // VM Debug state
    bool debug = 0;

    void fetch();
    void decode();
    void execute();
    void doPrimitive();

    [[deprecated("Replaced with LibBDVM::Chars::pack")]]
    static i32 packChars(const i32 c1, const i32 c2, const i32 c3, const i32 c4);
    [[deprecated("Replaced with LibBDVM::Chars::unpack")]]
    static void unpackChars(const i32 i, i32& c1, i32& c2, i32& c3, i32& c4);

    // VM Utils
    void pop(const i32 i);
    bool exitOnInvalidSP(const std::string& instName, const bool strict);
    void crash(const std::basic_string<char>& message);

public:
    BrainDamagedVM();
    void run();
    void loadProgram(const std::vector<instruction_t>& prog);
    void setDebug(const bool value) {
        debug = value;
    }

    void dumpMemory();
};

#endif //BRAINDAMAGED_BRAINDAMAGEDVM_HPP
