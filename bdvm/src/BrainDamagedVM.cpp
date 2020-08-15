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

void BrainDamagedVM::fetch() {
    pc++;
}

void BrainDamagedVM::decode() {
    inst = programCode[pc];
}

void BrainDamagedVM::execute() {
    doPrimitive();
}

void BrainDamagedVM::doPrimitive() {
    i32 i, j;
    f64 k, l;
    VM_Object vo{}, vo1{}, vo2{};
    switch (inst) {
        case HLT: // hlt
            if(debug) {
                std::cout << "HLT" << std::endl;
            }
            running = false;
            break;
        case NOP: // nop
            if(debug) {
                std::cout << "NOP" << std::endl;
            }
            break;
        case ADDI: // add
            if(debug) {
                std::cout << "ADDI" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("ADDI", true)) break;

            // Check and protect against operating with non-ints

            // Inline Addition
            i = 0;
            if(memory[sp -1].is_i16()) {
                i = memory[sp - 1].get_i16();
            } else if(memory[sp -1].is_i32()) {
                i = memory[sp - 1].get_i32();
            }

            j = 0;
            if(memory[sp].is_i16()) {
                j = memory[sp].get_i16();
            } else if(memory[sp].is_i32()) {
                j = memory[sp].get_i32();
            }

            vo = VM_Object{};
            if(memory[sp].is_i32() || memory[sp--].is_i32()) {
                vo.set_i32(i + j);
            } else {
                vo.set_i16(i + j);
            }

            // Drop second number from stack
            pop(1);

            memory[sp] = vo;

            break;
        case SUBI: // sub
            if(debug) {
                std::cout << "SUBI" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("SUBI", true)) break;

            // Check and protect against operating with non-ints
            if(!memory[sp -1].is_i16() || !memory[sp].is_i16()) {
                crash("Cannot SUBI on non int");
                break;
            }

            // Inline Subtraction
            i = memory[sp - 1].get_i16();
            j = memory[sp].get_i16();

            vo = VM_Object{};
            vo.set_i16(i - j);

            memory[sp - 1] = vo;

            // Drop second number from stack
            pop(1);
            break;
        case MULI: // mul
            if(debug) {
                std::cout << "MULI" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("MULI", true)) break;

            // Check and protect against operating with non-ints
            if(!memory[sp -1].is_i16() || !memory[sp].is_i16()) {
                crash("Cannot MULI on non int");
                break;
            }

            // Inline Multiplication
            i = memory[sp - 1].get_i16();
            j = memory[sp].get_i16();

            vo = VM_Object{};
            vo.set_i16(i * j);

            memory[sp - 1] = vo;

            // Drop second number from stack
            pop(1);
            break;
        case DIVI: // div
            if(debug) {
                std::cout << "DIVI" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("DIVI", true)) break;

            // Check and protect against operating with non-ints
            if(!memory[sp -1].is_i16() || !memory[sp].is_i16()) {
                crash("Cannot DIVI on non int");
                break;
            }

            i = memory[sp - 1].get_i16();
            j = memory[sp].get_i16();

            if(i == 0 || j == 0) {
                crash("Cannot divide by zero!");
                break;
            }

            vo = VM_Object{};
            vo.set_i16(i / j);

            memory[sp - 1] = vo;

            pop(1);

            dumpMemory();

            break;
        case DUP: // DUP
            if(debug) {
                std::cout << "DUP" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("DUP", true)) break;

            vo = memory[sp];
            memory[sp+1] = vo;
            sp++;

            break;
        case CMP: // CMP
            if(debug) {
                std::cout << "CMP" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("CMP", true)) break;

            vo = memory[sp-1];
            vo1 = memory[sp];
            pop(1);

            if(vo.is_i8() && vo1.is_i8()) {
                puts("Is i8");
                i = vo.get_i8();
                j = vo1.get_i8();
            } else if(vo.is_i16() && vo1.is_i16()) {
                puts("Is i16");
                i = vo.get_i16();
                j = vo1.get_i16();
            } else if (vo.is_i32() && vo1.is_i32()) {
                puts("Is i32");
                i = vo.get_i32();
                j = vo1.get_i32();
            } else {
                if(vo.is_i16()) {
                    i = vo.get_i16();
                } else if(vo.is_i32()) {
                    i = vo.get_i32();
                } else {
                    i = -1;
                }

                if(vo1.is_i16()) {
                    j = vo1.get_i16();
                } else if(vo1.is_i32()) {
                    j = vo1.get_i32();
                } else {
                    j = -2;
                }
            }

            if(debug) {
                dumpMemory();
                printf("Compare: (%d == %d) => %s\n", i, j, i == j ? "true" : "false");
            }

            vo = VM_Object{};
            vo.set_bool(i == j);

            memory[++sp] = vo;
            break;
        case JE: // JE
            if(debug) {
                std::cout << "JE" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("JE", true)) break;

            // Get condition
            vo1 = memory[sp];
            pop(1);

            // Check if condition is 8 bit
            if(!vo1.is_i8()) {
                crash("Cannot JE condition check with non-bool");
                return;
            }

            // Check if condition is 8 bit
            if(!vo1.is_bool()) {
                crash("Cannot JE condition check with non-bool");
                return;
            }

            // Get address
            i = programCode[++pc];

            if(debug) {
                std::printf("CON: %s; ADDR: %d", vo1.get_bool() ? "true" : "false", i);
            }

            // Check and Jump
            if(vo1.get_bool()) {
                if(i < 0 || i >= programCode.size()) {
                    // TODO: Replace fmt::format with std::format when Clang stdc++ supports it
                    crash(fmt::format("Address out of bounds, cannot jump to: %08x", i));
                    return;
                }
                pc = i;
            }
            break;
        case JNE: // JNE
            if(debug) {
                std::cout << "JNE" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("JNE", true)) break;

            vo1 = memory[sp];
            pop(1);

            if(!vo1.is_bool()) {
                crash("Cannot JNE condition check with non-bool");
                return;
            }

            i = programCode[++pc];

            if(debug) {
                std::printf("CON: %s; ADDR: %d", vo1.get_bool() ? "true" : "false", i);
            }

            if(!vo1.get_bool()) {
                pc = i;
            }
            break;
        case JMP: // JMP
            if(debug) {
                std::cout << "JMP" << std::endl;
            }

            // Get Address
            i = programCode[++pc];

            // Check if we can jump to that address
            if(i < 0 || i > programCode.size()) {
                // TODO: Replace fmt::format with std::format when Clang stdc++ supports it
                crash(fmt::format("Address out of bounds, cannot jump to: {}", i));
                return;
            }

            // Jump
            pc = i;

            break;
        case POP: // POP
            if(debug) {
                std::cout << "POP" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("POP", true)) break;

            pop(1);
            break;
        case SWP: // SWP
            if(debug) {
                std::cout << "SWP" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("SWP", true)) break;

            vo = memory[sp-1];
            vo1 = memory[sp];
            memory[sp-1] = vo1;
            memory[sp] = vo;
            break;
        case INC: // INC
            if(debug) {
                std::cout << "INC" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("INC", true)) break;

            vo = memory[sp];

            if(vo.is_i8())
                vo.set_i8(1);
            if(vo.is_i16())
                vo.set_i16(vo.get_i16()+1);

            memory[sp] = vo;
            break;
        case DEC: // DEC
            if(debug) {
                std::cout << "DEC" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("DEC", true)) break;

            vo = memory[sp];

            if(vo.is_i8())
                vo.set_i8(0);
            if(vo.is_i16())
                vo.set_i16(vo.get_i16()-1);

            memory[sp] = vo;
            break;
        case SPI: // SPI
            if(debug) {
                std::cout << "SPI" << std::endl;
            }
            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("SPI", false)) break;

            sp++;
            break;
        case SPD: // SPD
            if(debug) {
                std::cout << "SPD" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("SPD", true)) break;

            sp--;
            break;
        case SPC: // SPC
            if(debug) {
                std::cout << "SPC" << std::endl;
            }

            // Search for the first non-empty item in the stack space
            for(i = PC_BEGIN-1; i > 0; i--) {
                vo = memory[i];
                if(!vo.is_empty()) {
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

            i = programCode[++pc];

            vo = VM_Object{};
            vo.set_i16(i);

            memory[sp] = vo;

            break;
        case 81: // psi (Print Stack Integer)
            if(debug) {
                std::cout << "PSI" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("PSI", false)) break;

            vo = memory[sp];

            if(vo.is_i8())
                printf("%d", vo.get_i8());
            else if(vo.is_i16())
                printf("%d", vo.get_i16());
            else
                std::cout << 0;

            pop(1);
            break;
        case 82: // psc (Print Stack Character)
            if(debug) {
                std::cout << "PSC" << std::endl;
            }

            // Exit VM when SP gets out of bounds
            if (exitOnInvalidSP("PSC", false)) break;

            vo = memory[sp];

            if(vo.is_i8()) {
                if(vo.get_i8() == 0)
                    std::cout << "0";
                else if(vo.get_i8() == 1)
                    std::cout << "1";
            }
            if(vo.is_i16())
                std::cout << (char) vo.get_i16();

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
                vo = VM_Object{};
                vo.set_i32(i);
                memory[++sp] = vo;
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
                vo = VM_Object{};
                vo.set_i32((int) c);
                memory[++sp] = vo;
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
                vo = VM_Object{};
                char buf[IO_READ_BUFFER_MAX];
                for(char & b : buf) {
                    b = 0;
                }
                fgets(buf, IO_READ_BUFFER_MAX, stdin);

                i32 a,b,c,d;

                vo.set_i8(TXT_BEGIN);
                memory[++sp] = vo;

                for(i = 2; i < IO_READ_BUFFER_MAX; i+=3) {
                    if(i-3 <= IO_READ_BUFFER_MAX) {
                        a = buf[i-3];
                    } else {
                        a = 0x00;
                    }
                    if(i-2 <= IO_READ_BUFFER_MAX) {
                        b = buf[i-2];
                    } else {
                        b = 0x00;
                    }
                    if(i-1 <= IO_READ_BUFFER_MAX) {
                        c = buf[i-1];
                    } else {
                        c = 0x00;
                    }
                    if(i <= IO_READ_BUFFER_MAX) {
                        d = buf[i];
                    } else {
                        d = 0x00;
                    }

                    LibBDVM::Chars::pack(i, a, b, c, d);
                    vo.set_i32(i);
                    memory[++sp] = vo;

                    if(a == TXT_NEW_LINE || b == TXT_NEW_LINE || c == TXT_NEW_LINE) {
                        vo.set_i8(TXT_END);
                        memory[++sp] = vo;
                        break;
                    }
                }
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

            vo = memory[sp];

            if(!vo.is_i8())
                break;

            pop(1);
            if(vo.get_i8() == TXT_END) {
                std::string buf;
                while(memory[sp].get_i8() != TXT_BEGIN) {
                    i32 a,b,c,d;

                    vo = memory[sp];

                    if(!vo.is_i32()) {
                        crash(fmt::format("Cannot unpack a non 32-bit integer into 4 ASCII Characters at %08x", pc));
                        return;
                    }

                    LibBDVM::Chars::unpack(vo.get_i32(), a, b, c, d);
                    pop(1);

                    if(debug) {
                        printf("%04d: %08x, %08x, %08x, %08x\n", sp, a, b, c, d);
                    }

                    buf.push_back((char)d);
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
    if (i >= MEMORY_SIZE) {
        dumpMemory();
        std::printf("BrainDamagedVM:: Cannot remove %d elements from Stack with max size %d\n", i, MEMORY_SIZE);
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

        memory[sp--] = VM_Object{};
        j--;
    }
}

void BrainDamagedVM::dumpMemory() {
    if (debug) {
        puts("---------- VM Memory Dump ----------");
        std::printf("\nSP=%d\nPC=%d\n", sp, pc);
        i32 line;
        line = 0;
        puts("Memory (RAM):");

        auto printMem = [=](const auto& i, VM_Object mem, const std::string& end) {
            if(mem.is_i8())
                std::printf("%04d = (i8) %02x%s", i, mem.get_i8(), end.c_str());
            else if(mem.is_i16())
                std::printf("%04d = (i16) %04x%s", i, mem.get_i16(), end.c_str());
            else if(mem.is_i32())
                std::printf("%04d = (i32) %08x%s", i, mem.get_i32(), end.c_str());
            else if(mem.is_i64())
                std::printf("%04d = (i64) %08lx%s", i, mem.get_i64(), end.c_str());
            else if(mem.is_f64())
                std::printf("%04d = (f64) %f%s", i, mem.get_f64(), end.c_str());
        };

        for (i32 i = 0; i < MEMORY_SIZE; i++) {
            if (!memory[i].is_empty()) {
                if (line < 8) {
                    line++;
                    printMem(i, memory[i], "\t\t");
                }
                else if (line == 8) {
                    printMem(i, memory[i], "\n");
                    line = 0;
                }
            }
        }

        line = 0;
        puts("\nMemory (ROM):");

        for (i32 i = 0; i < programCode.size(); i++) {
            if (line < 8) {
                line++;
                std::printf("%04d: %04x\t\t", i, programCode[i]);
            }
            else if (line == 8) {
                std::printf("%04d: %04x\n", i, programCode[i]);
                line = 0;
            }
        }
        puts("\n---------- VM Memory Dump ----------");
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

    if (sp > MEMORY_SIZE) {
        dumpMemory();
        std::printf("BrainDamagedVM:: Cannot perform %s operation with SP > %d", instName.c_str(), MEMORY_SIZE);
        running = false;
        return true;
    }

    return false;
}

void BrainDamagedVM::crash(const std::basic_string<char>& message) {
    puts("---------- VM PANIC ----------");
    puts("An Error occurred the VM cant recover from!");
    dumpMemory();
    puts("---------- ERROR Message ----------");
    std::printf("BrainDamagedVM:: %s\n", message.c_str());
    puts("---------- ERROR Message ----------");
    puts("---------- VM PANIC ----------");
    running = false;
}

void BrainDamagedVM::run() {
    pc -= 1;
    while (running) {
        fetch();
        decode();
        execute();
    }
}

void BrainDamagedVM::loadProgram(const std::vector<instruction_t>& prog) {
    if(prog.empty()) {
        std::cerr << "BrainDamagedVM:: Bytecode cannot be of length 0 or less!";
    }

    programCode.resize(prog.size());
    programCode.reserve(prog.size());

    // Reset the Program Counter to its start
    pc = PC_BEGIN;

    for (i32 i = 0; i < prog.size(); i++) {
        programCode[pc + i] = prog[i];
    }
}

i32 BrainDamagedVM::packChars(const i32 c1, const i32 c2, const i32 c3, const i32 c4) {
    i32 out;
    LibBDVM::Chars::pack(out, c1, c2, c3, c4);
    return out;
}

void BrainDamagedVM::unpackChars(const i32 i, i32& c1, i32& c2, i32& c3, i32& c4) {
    LibBDVM::Chars::unpack(i, c1, c2, c3, c4);
}