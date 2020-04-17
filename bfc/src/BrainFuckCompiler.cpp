//
// Created by atjontv on 4/16/20.
//

#include "../include/BrainFuckCompiler.hpp"
#include "../../bdvm/include/Bytecode.hpp"

void BrainFuckCompiler::loadFile(std::string filename) {
    std::ifstream infile(filename);

    for(std::string line; getline(infile, line);) {
        source += line;
    }

    if(filename.ends_with(".bf")) {
        outFilename = filename.replace(filename.find(".bf"), 3, ".bdc");
    } else {
        outFilename = filename + ".bdc";
    }
}

i32 BrainFuckCompiler::compile() {
    for(char i : source) {
        switch (i) {
            case '.':
                instructions.push_back(PSC);
                break;
            case ',':
                instructions.push_back(RSC);
                break;
            case '+':
                instructions.push_back(INC);
                break;
            case '-':
                instructions.push_back(DEC);
                break;
            case '>':
                instructions.push_back(SPI);
                break;
            case '<':
                instructions.push_back(SPD);
                break;
            default:
                instructions.push_back(NOP);
                break;
        }
    }

    return 0;
}

void BrainFuckCompiler::writeFile() {
    std::ofstream outfile(outFilename, std::ios::out | std::ios::binary);
    outfile.write((char*)instructions.data(), instructions.size() * sizeof(i32));
    outfile.close();

    std::cout << "Compiled Assembly to Bytecode. Wrote to file: " << outFilename << std::endl;
}