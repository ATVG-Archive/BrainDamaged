//
// Created by atjontv on 4/15/20.
//

#include "../include/BrainDamagedVM.hpp"

BrainDamagedVM::BrainDamagedVM() {
    memory.reserve(1000000);
}

i32 BrainDamagedVM::getType(i32 instruction) {
    i32 type = 0xc0000000;
    type = (type & instruction) >> 30;
    return type;
}

i32 BrainDamagedVM::getData(i32 instruction) {
    i32 data = 0x3fffffff;
    data = data & instruction;
    return data;
}

void BrainDamagedVM::fetch() {
    pc++;
}

void BrainDamagedVM::decode() {
    typ = getType(memory[pc]);
    dat = getData(memory[pc]);
}

void BrainDamagedVM::execute() {
    if (typ == 0 || typ == 2) {
        sp++;
        memory[sp] = dat;
    } else {
        doPrimitive();
    }
}

void BrainDamagedVM::doPrimitive() {
    if(debug || dat == 2) {
        std::printf("\n%04d: %04x\n", pc-100, dat);
    }
    switch (dat) {
        case 0: // hlt
            if(debug) {
                std::cout << "HLT" << std::endl;
            }
            running = 0;
            break;
        case 1: // nop
            if(debug) {
                std::cout << "NOP" << std::endl;
            }
            break;
        case 2: // dbg
            if(debug) {
                std::cout << "DBG" << std::endl;
            }
            debug = !debug;
            break;
        case 3: // nop
            break;
        case 4: // nop
            break;
        case 5: // add
            if(debug) {
                std::cout << "ADD" << std::endl;
            }
            memory[sp - 1] = memory[sp - 1] + memory[sp];
            sp--;
            break;
        case 6: // sub
            if(debug) {
                std::cout << "SUB" << std::endl;
            }
            memory[sp - 1] = memory[sp - 1] - memory[sp];
            sp--;
            break;
        case 7: // mul
            if(debug) {
                std::cout << "MUL" << std::endl;
            }
            memory[sp - 1] = memory[sp - 1] * memory[sp];
            sp--;
            break;
        case 8: // div
            if(debug) {
                std::cout << "DIV" << std::endl;
            }
            memory[sp - 1] = memory[sp - 1] / memory[sp];
            sp--;
            break;
        case 9: // DUP
            if(debug) {
                std::cout << "DUP" << std::endl;
            }
            i32 i;
            i = memory[sp];
            sp++;
            memory[sp] = i;
            break;
        case 10: // JE
            if(debug) {
                std::cout << "JE" << std::endl;
            }
            i = memory[sp];
            i32 j;
            j = memory[sp+1];
            sp-=2;
            if(i == 1) {
                pc += j;
            }
            break;
        case 11: // JNE
            if(debug) {
                std::cout << "JNE" << std::endl;
            }
            i = memory[sp];
            sp--;
            j = memory[sp];
            sp--;
            if(debug) {
                std::printf("CON: %d; SKIP: %d", j, i);
            }
            if(j == 0) {
                pc += i;
            }
            break;
        case 12: // CMP
            if(debug) {
                std::cout << "CMP" << std::endl;
            }
            i32 a, b;
            a = memory[sp-1];
            b = memory[sp];
            sp--;
            memory[sp] = (int)(a == b);
            break;
        case 13: // POP
            if(debug) {
                std::cout << "POP" << std::endl;
            }
            sp--;
            break;
        case 14: // SWP
            a = memory[sp-1];
            b = memory[sp];
            memory[sp-1] = b;
            memory[sp] = a;
            break;
        case 81: // psi (Print Stack Integer)
            if(debug) {
                std::cout << "PSI" << std::endl;
            }
            std::cout << memory[sp];
            sp--;
            break;
        case 82: // psc (Print Stack Character)
            if(debug) {
                std::cout << "PSC" << std::endl;
            }
            i = memory[sp];
            sp--;
            std::cout << (char)i;
            break;
        case 83: // rsi (Read Stack Integer)
            if(debug) {
                std::cout << "RSI" << std::endl;
            }
            try {
                scanf(" %d", &i);
                sp++;
                memory[sp] = i;
            } catch (const std::exception &e) {
                if(debug) {
                    std::cout << e.what() << std::endl;
                }
            }
            break;
        case 84: // rsc (Read Stack Char)
            if(debug) {
                std::cout << "RSC" << std::endl;
            }
            try {
                char c;
                scanf(" %c", &c);
                sp++;
                memory[sp] = (int) c;
            } catch (const std::exception &e) {
                if(debug) {
                    std::cout << e.what() << std::endl;
                }
            }
            break;
    }
}

void BrainDamagedVM::run() {
    pc -= 1;
    while (running == 1) {
        fetch();
        decode();
        execute();
    }
}

void BrainDamagedVM::loadProgram(std::vector<i32> prog) {
    if(prog.size() <= 0) {
        std::cerr << "BrainDamagedVM:: Bytecode cannot be of length 0 or less!" << std::endl;
    }
    for (i32 i = 0; i < prog.size(); i++) {
        memory[pc + i] = prog[i];
    }
}