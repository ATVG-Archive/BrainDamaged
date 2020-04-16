//
// Created by atjontv on 4/15/20.
//

#include "../include/BrainDamagedVM.hpp"

BrainDamagedVM::BrainDamagedVM() {
    memory.reserve(1000000);
    for(i32 i = 0; i < PC_BEGIN; i++) {
        memory[i] = 0;
    }
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
        std::printf("\n%04d: %04x\n", pc-PC_BEGIN, dat);
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
        case 3: // ddm
            if(debug) {
                std::printf("Dumping Memory:\n");
                i32 line;
                line = 0;
                for(i32 i = 0; i < PC_BEGIN; i++) {
                    if(line < 8) {
                        line++;
                        std::printf("%04d = %08x\t", i, memory[i]);
                    } else if(line == 8) {
                        std::printf("%04d = %08x\n", i, memory[i]);
                        line = 0;
                    }
                }
            }
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
        case 15: // INC
            memory[sp]++;
            break;
        case 16: // DEC
            memory[sp]--;
            break;
        case 17: // JMP
            i = memory[sp];
            sp--;
            pc+=i;
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
        case 85: // RSW
            try {
                char buf[IN_BYTE_MAX];
                for(char & b : buf) {
                    b = 0;
                }
                fgets(buf, IN_BYTE_MAX, stdin);

                i32 c;

                sp++;
                memory[sp] = TXT_BEGIN;

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

                    sp++;
                    memory[sp] = packChars(a, b, c);

                    if(a == NEW_LINE || b == NEW_LINE || c == NEW_LINE) {
                        sp++;
                        memory[sp] = TXT_END;
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
            i = memory[sp];
            sp--;
            if(i == TXT_END) {
                std::string buf;
                while(memory[sp] != TXT_BEGIN) {
                    a = 0; b = 0; i32 c = 0;

                    unpackChars(memory[sp], a, b, c);
                    sp--;

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