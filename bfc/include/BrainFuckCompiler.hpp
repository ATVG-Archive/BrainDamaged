//void
// Created by atjontv on 4/15/20.
//

#ifndef BRAINDAMAGED_BRAINFUCKCOMPILER_HPP
#define BRAINDAMAGED_BRAINFUCKCOMPILER_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include <Types.hpp>
#include <Bytecode.hpp>

class BrainFuckCompiler {
    std::string source;
    std::vector<instruction_t> instructions;
    std::string outFilename;
    bool bdExtensions = false;

public:
    void loadFile(std::string filename);
    status_t compile();
    void writeFile(const std::string& filename);
    void setBDExtensions(const bool value) {
        bdExtensions = value;
    }
};

#endif //BRAINDAMAGED_BRAINFUCKCOMPILER_HPP
