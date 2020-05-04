//
// Created by atjontv on 4/15/20.
//

#include "../include/BrainDamagedVM.hpp"

BrainDamagedVM::BrainDamagedVM() {
    // Resize memory to allocate space
    memory.resize(MEMORY_SIZE);
    // Make sure the space is reserved
    memory.reserve(MEMORY_SIZE);

    // Clear possible random data from memory to prevent UB (Undefined Behavior)
    memory.clear();
}

const i32 BrainDamagedVM::getType(const i32 instruction) {
    i32 type = 0xc0000000;
    type = (type & instruction) >> 30;
    return type;
}

const i32 BrainDamagedVM::getData(const i32 instruction) {
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
    // TODO: Remove this if as we no longer support direct loading of integers
    if (typ == 0 || typ == 2) {
        // We will leave this for now so that the executor does not face normal integers
        return;
    } else {
        doPrimitive();
    }
}

void BrainDamagedVM::doPrimitive() {
    if(debug || dat == 2) {
        std::printf("\n%04d: %04x\n", pc-PC_BEGIN, dat);
    }
    i32 i, j;
    switch (dat) {
        case 0: // hlt
            if(debug) {
                std::cout << "HLT" << std::endl;
            }
            running = false;
            break;
        case 1: // nop
            if(debug) {
                std::cout << "NOP" << std::endl;
            }
            break;
        case 2: // nop
            break;
        case 3: // nop
            break;
        case 4: // nop
            break;
        case 5: // add
            if(debug) {
                std::cout << "ADD" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("ADD", true)) break;

            // Inline Addition
            memory[sp - 1] = memory[sp - 1] + memory[sp];

            // Drop second number from stack
            pop(1);
            break;
        case 6: // sub
            if(debug) {
                std::cout << "SUB" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("SUB", true)) break;

            // Inline Subtraction
            memory[sp - 1] = memory[sp - 1] - memory[sp];

            // Drop second number from stack
            pop(1);
            break;
        case 7: // mul
            if(debug) {
                std::cout << "MUL" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("MUL", true)) break;

            // Inline Multiplication
            memory[sp - 1] = memory[sp - 1] * memory[sp];

            // Drop second number from stack
            pop(1);
            break;
        case 8: // div
            if(debug) {
                std::cout << "DIV" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("DIV", true)) break;

            // Inline Division
            memory[sp - 1] = memory[sp - 1] / memory[sp];

            // Drop second number from stack
            pop(1);
            break;
        case 9: // DUP
            if(debug) {
                std::cout << "DUP" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("DUP", true)) break;

            i = memory[sp++];
            memory[sp] = i;

            break;
        case 10: // JE
            if(debug) {
                std::cout << "JE" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("JE", true)) break;

            j = memory[sp];
            pop(1);

            i = memory[++pc];
            i32 type;
            type = getType(i);

            // Check if next item on the program stack is a jumpable location
            if(type != 0 && type != 2) {
                dumpMemory();
                std::cerr << "BrainDamagedVM:: Cannot jump to non-integer relative location" << std::endl;
                running = false;
                break;
            }

            if(debug) {
                std::printf("CON: %d; SKIP: %d", j, i);
            }

            if(j == 1) {
                pc += i;
            }
            break;
        case 11: // JNE
            if(debug) {
                std::cout << "JNE" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("JNE", true)) break;

            j = memory[sp];
            pop(1);

            i = memory[++pc];
            type = getType(i);

            // Check if next item on the program stack is a jumpable location
            if(type != 0 && type != 2) {
                dumpMemory();
                std::cerr << "BrainDamagedVM:: Cannot jump to non-integer relative location" << std::endl;
                running = 0;
                break;
            }

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

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("CMP", true)) break;

            i = memory[sp-1];
            j = memory[sp];
            pop(1);

            memory[++sp] = (int)(i == j);
            break;
        case 13: // POP
            if(debug) {
                std::cout << "POP" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("POP", true)) break;

            pop(1);
            break;
        case 14: // SWP
            if(debug) {
                std::cout << "SWP" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("SWP", true)) break;

            i = memory[sp-1];
            j = memory[sp];
            memory[sp-1] = j;
            memory[sp] = i;
            break;
        case 15: // INC
            if(debug) {
                std::cout << "INC" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("INC", true)) break;

            memory[sp]++;
            break;
        case 16: // DEC
            if(debug) {
                std::cout << "DEC" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("DEC", true)) break;

            memory[sp]--;
            break;
        case 17: // JMP
            if(debug) {
                std::cout << "JMP" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("JMP", true)) break;

            i = memory[++pc];
            type = getType(i);

            // Check if next item on the program stack is a jumpable location
            if(type != 0 && type != 2) {
                dumpMemory();
                std::cerr << "BrainDamagedVM:: Cannot jump to non-integer relative location" << std::endl;
                running = false;
                break;
            }

            // Jump
            pc += i;

            break;
        case 18: // SPI
            if(debug) {
                std::cout << "SPI" << std::endl;
            }
            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("SPI", false)) break;

            sp++;
            break;
        case 19: // SPD
            if(debug) {
                std::cout << "SPD" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("SPD", true)) break;

            sp--;
            break;
        case 20: // SPC
            if(debug) {
                std::cout << "SPC" << std::endl;
            }

            // Search for the first non-empty item in the stack space
            for(i = PC_BEGIN-1; i > 0; i--) {
                if(memory[i] != 0x00000000) {
                    sp = i;
                    break;
                }
            }
            break;
        case 21: // LDI
            if(debug) {
                std::cout << "LDI" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if(exitOnInvalidSP("LDI", false)) break;

            i = memory[++pc];
            type = getType(i);

            // Check if next item on the program stack is a jumpable location
            if(type != 0 && type != 2) {
                dumpMemory();
                std::cerr << "BrainDamagedVM:: Cannot load non-integer into stack" << std::endl;
                running = false;
                break;
            }

            memory[sp] = i;

            break;
        case 81: // psi (Print Stack Integer)
            if(debug) {
                std::cout << "PSI" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("PSI", false)) break;

            std::cout << memory[sp];
            pop(1);
            break;
        case 82: // psc (Print Stack Character)
            if(debug) {
                std::cout << "PSC" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("PSC", false)) break;

            std::cout << (char) memory[sp];
            pop(1);
            break;
        case 83: // rsi (Read Stack Integer)
            if(debug) {
                std::cout << "RSI" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("RSI", false)) break;

            try {
                scanf(" %d", &i);
                memory[++sp] = i;
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

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("RSC", false)) break;

            try {
                char c;
                scanf(" %c", &c);
                memory[++sp] = (int) c;
            } catch (const std::exception &e) {
                if(debug) {
                    std::cout << e.what() << std::endl;
                }
            }
            break;
        case 85: // RSW (Read Stack Wide)
            if(debug) {
                std::cout << "RSW" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("RSW", false)) break;

            try {
                char buf[IN_BYTE_MAX];
                for(char & b : buf) {
                    b = 0;
                }
                fgets(buf, IN_BYTE_MAX, stdin);

                i32 a,b,c;

                memory[++sp] = TXT_BEGIN;

                for(i = 2; i < IN_BYTE_MAX; i+=3) {
                    if(i-2 <= IN_BYTE_MAX) {
                        a = buf[i-2];
                    } else {
                        a = 0x00;
                    }
                    if(i-1 <= IN_BYTE_MAX) {
                        b = buf[i-1];
                    } else {
                        b = 0x00;
                    }
                    if(i <= IN_BYTE_MAX) {
                        c = buf[i];
                    } else {
                        c = 0x00;
                    }

                    memory[++sp] = packChars(a, b, c);

                    if(a == NEW_LINE || b == NEW_LINE || c == NEW_LINE) {
                        memory[++sp] = TXT_END;

                        free(buf);
                        break;
                    }
                }
                free(buf);
            } catch (std::exception &e) {
                if(debug) {
                    std::cout << e.what() << std::endl;
                }
            }
            break;
        case 86: // PSW
            if(debug) {
                std::cout << "PSW" << std::endl;
            }
            
            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("PSW", true)) break;

            i = memory[sp];
            pop(1);
            if(i == TXT_END) {
                std::string buf;
                while(memory[sp] != TXT_BEGIN) {
                    i32 a,b,c;

                    unpackChars(memory[sp], a, b, c);
                    pop(1);

                    if(debug) {
                        printf("%04d: %08x, %08x, %08x\n", sp, a, b, c);
                    }

                    buf.push_back((char)c);
                    buf.push_back((char)b);
                    buf.push_back((char)a);
                }

                std::string out;

                for(i = buf.size(); i > 0; i--) {
                    out.push_back(buf[i]);
                }

                std::cout << out;
            }
            break;
    }
}

void BrainDamagedVM::pop(const i32 i) {
    if (sp <= 0) {
        dumpMemory();
        std::cout << "BrainDamagedVM:: Cannot remove from Stack with SP <= 0" << std::endl;
        running = false;
        return;
    }
    if (i >= STACK_MAX) {
        dumpMemory();
        std::printf("BrainDamagedVM:: Cannot remove %d elements from Stack with max size %d\n", i, STACK_MAX);
        running = false;
        return;
    }

    for(i32 j = i; j > 0; j--) {
        if (sp <= 0) {
            dumpMemory();
            std::cout << "BrainDamagedVM:: Cannot remove from Stack with SP <= 0" << std::endl;
            running = false;
            return;
        }

        memory[sp--] = 0;
        j--;
    }
}

void BrainDamagedVM::dumpMemory() {
    if (debug) {
        std::printf("Printing Memory Dump.\nSP=%d\nPC=%d\nStack:\n", sp, pc);
        i32 line;
        line = 0;
        for (i32 i = 0; i < PC_BEGIN; i++) {
            if (memory[i] != 0x00000000) {
                if (line < 8) {
                    line++;
                    std::printf("%04d = %08x\t", i, memory[i]);
                }
                else if (line == 8) {
                    std::printf("%04d = %08x\n", i, memory[i]);
                    line = 0;
                }
            }
        }
        std::cout << std::endl;
    }
}

/***
 * Check the Stack Pointer if it is in a invalid range, this can be strict with <= 0 and > STACK_MAX or
 * non-strict with < 0 and > STACK_MAX
 * @param instName Instruction Name to print in the case a error occurred
 * @param strict This refers to the SP on the lower end. This causes the VM to crash when SP is lower then or equal to 0
 * @return
 */
bool BrainDamagedVM::exitOnInvalidSP(const std::string& instName, const bool strict = true) {
    if (sp <= 0 && strict) {
        dumpMemory();
        std::printf("BrainDamagedVM:: Cannot perform %s operation with SP <= 0", instName.c_str());
        running = false;
        return true;
    } else if (sp < 0 && !strict) {
        dumpMemory();
        std::printf("BrainDamagedVM:: Cannot perform %s operation with SP < 0", instName.c_str());
        running = false;
        return true;
    }

    if (sp > STACK_MAX) {
        dumpMemory();
        std::printf("BrainDamagedVM:: Cannot perform %s operation with SP > %d", instName.c_str(), STACK_MAX);
        running = false;
        return true;
    }

    return false;
}

void BrainDamagedVM::run() {
    pc -= 1;
    while (running) {
        fetch();
        decode();
        execute();
    }
}

void BrainDamagedVM::loadProgram(const std::vector<i32>& prog) {
    if(prog.empty()) {
        std::cerr << "BrainDamagedVM:: Bytecode cannot be of length 0 or less!" << std::endl;
    }

    // Check if the program to load exceeds the current memory size.
    // For the check to only account for Program Size, we have to subtract the STACK_MAX from the memory size
    // As from 0 to STACK_MAX the stack is located in unified memory
    if(prog.size() > (memory.size() - STACK_MAX)) {
        // Clear the memory before resize
        memory.clear();

        // Resize to new memory space
        memory.resize(STACK_MAX + prog.size());

        // Reserve the new memory space
        memory.reserve(STACK_MAX + prog.size());

        // Make sure there is no random data
        memory.clear();
    }

    // Reset the Program Counter to its start
    pc = PC_BEGIN;

    for (i32 i = 0; i < prog.size(); i++) {
        memory[pc + i] = prog[i];
    }
}

i32 BrainDamagedVM::packChars(const i32 c1, const i32 c2, const i32 c3) {
    i32 i = (c1 << 16);
    i = i | (c2 << 8);
    i = i | c3;
    return i;
}

void BrainDamagedVM::unpackChars(const i32 i, i32& c1, i32& c2, i32& c3) {
    c1 = (i >> 16) & 0xFF;
    c2 = (i >> 8) & 0xFF;
    c3 = i & 0xFF;
}