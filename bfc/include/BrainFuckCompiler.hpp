//void
// Created by atjontv on 4/15/20.
//

#ifndef BRAINDAMAGED_BRAINFUCKCOMPILER_HPP
#define BRAINDAMAGED_BRAINFUCKCOMPILER_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <libgen.h>

#include "../../bdvm/include/Types.hpp"

class BrainFuckCompiler {
    std::string source;
    std::vector<i32> instructions;
    std::string outFilename;
    bool bdExtensions = false;

public:
    void loadFile(std::string filename);
    i32 compile();
    void writeFile();
    void setBDExtensions(const bool value) {
        bdExtensions = value;
    }
};

#endif //BRAINDAMAGED_BRAINFUCKCOMPILER_HPP
