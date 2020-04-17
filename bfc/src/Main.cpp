//
// Created by atjontv on 4/16/20.
//

#include "../include/BrainFuckCompiler.hpp"

int main(int argc, char* argv[]) {
    std::printf("BrainFuckCompiler (v0.1.0)\n");
    if(argc < 2 || argc > 3) {
    #ifdef linux
        std::printf("Usage: %s [-x] <filename>", basename(argv[0]));
    #endif
    #ifdef _WIN32
        std::printf("Usage: BrainFuckCompiler.exe [-x] <filename>");
    #endif
        exit(1);
    }

    BrainFuckCompiler compiler;
    if(argc == 3 && std::string(argv[1]) == "-x") {
        compiler.setBDExtensions(true);
        compiler.loadFile(argv[2]);
    }

    if(argc == 2 && std::string(argv[1]) != "-x") {
        compiler.setBDExtensions(false);
        compiler.loadFile(argv[1]);
    }
    i32 s = compiler.compile();
    compiler.writeFile();

    return s;
}