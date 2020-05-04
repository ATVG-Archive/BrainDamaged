//
// Created by atjontv on 4/16/20.
//

#include "../include/BrainDamagedAssembler.hpp"

void BrainDamagedAssembler::loadFile(std::string filename) {
    std::ifstream infile(filename);

    for(std::string line; getline(infile, line);) {
        source.push_back(line);
    }

    if(filename.ends_with(".bdasm")) {
        outFilename = filename.replace(filename.find(".bdasm"), 6, ".bdc");
    } else {
        outFilename = filename + ".bdc";
    }
}

#define INST(CODE, BCODE) \
    if(ins == CODE) { \
        if(debug) std::printf("%s: 0x%08x\n", CODE, BCODE); \
        instructions.push_back(BCODE); \
        continue; \
    }

#define INSTV(CODE, BCODE, VALUE) \
    if(ins == CODE) { \
        if(debug) std::printf("%s: 0x%08x (0x%08x)\n", CODE, BCODE, VALUE); \
        instructions.push_back(BCODE); \
        instructions.push_back(VALUE); \
        continue; \
    }

i32 BrainDamagedAssembler::compile() {
    for (const std::string& line : source) {
        // Invalid line
        if(line.size() < 3) {
            continue;
        }

        std::string ins = line.substr(0,3);

        // Ignore Comments
        if(ins.starts_with("#")) {
            continue;
        }

        // TODO: Remove this if as we no longer support direct loading of integers
        if(ins.starts_with("0x0") || ins.starts_with("0x1")) {
            // Just skip this as we no longer support direct loading, LDI inst should be used instead
            puts("WARNING: Direct loading of Integer valus is no longer supported! Please use the LDI instruction.");
            continue;
        }

        /// No-Parameter 3 Char Bytecode
        INST("HLT", HLT)
        INST("NOP", NOP)
        INST("ADD", ADD)
        INST("SUB", SUB)
        INST("MUL", MUL)
        INST("DIV", DIV)
        INST("DUP", DUP)
        INST("CMP", CMP)
        INST("POP", POP)
        INST("SWP", SWP)
        INST("INC", INC)
        INST("DEC", DEC)
        INST("SPI", SPI)
        INST("SPD", SPD)
        INST("SPC", SPC)
        INST("PSI", PSI)
        INST("PSC", PSC)
        INST("RSI", RSI)
        INST("RSC", RSC)
        INST("RSW", RSW)
        INST("PSW", PSW)

        /// One-Parameter 3 Char Bytecode
        // Invalid line
        if(line.size() < 4) {
            continue;
        }

        std::string val = line.substr(4);
        i32 value = stoi(val, nullptr, 16);

        INSTV("JNE", JNE, value)
        INSTV("JMP", JMP, value)
        INSTV("LDI", LDI, value)

        /// One-Parameter 2 Char Bytecode
        ins = line.substr(0,2);
        val = line.substr(3);
        value = stoi(val, nullptr, 10);

        INSTV("JE" , JE, value)
    }

    return 0;
}

void BrainDamagedAssembler::writeFile() {
    std::ofstream outfile(outFilename, std::ios::out | std::ios::binary);
    outfile.write((char*)instructions.data(), instructions.size() * sizeof(i32));
    outfile.close();

    std::cout << "Compiled Assembly to Bytecode. Wrote to file: " << outFilename << std::endl;
}
