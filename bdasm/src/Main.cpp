//
// Created by atjontv on 4/16/20.
//

#include <iostream>

#include "../include/BrainDamagedAssembler.hpp"

int main(int argc, char* argv[]) {
    std::printf("BrainDamagedAssembler (v0.3.0)\n");
    if(argc < 2 || argc > 3) {
    #ifdef linux
        std::printf("Usage: %s [-v] <filename>", basename(argv[0]));
    #endif
    #ifdef _WIN32
        std::printf("Usage: BrainDamagedAssembler.exe [-v] <filename>");
    #endif
        exit(1);
    }

    BrainDamagedAssembler assembler;

    if(argc == 3 && std::string(argv[1]) == "-v") {
        assembler.setDebug(true);
        assembler.loadFile(argv[2]);
    }

    if(argc == 2 && std::string(argv[1]) != "-v") {
        assembler.setDebug(false);
        assembler.loadFile(argv[1]);
    }

    i32 s = assembler.compile();
    assembler.writeFile();

    return s;
}