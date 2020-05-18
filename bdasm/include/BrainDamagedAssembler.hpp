//
// Created by atjontv on 4/16/20.
//

#ifndef BRAINDAMAGED_BRAINDAMAGEDASSEMBLER_HPP
#define BRAINDAMAGED_BRAINDAMAGEDASSEMBLER_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#ifdef linux
#include <libgen.h>
#endif

#include "../../bdvm/include/Bytecode.hpp"
#include "../../bdvm/include/Types.hpp"

class BrainDamagedAssembler {
    std::vector<instruction_t> instructions;
    std::vector<std::string> source;
    std::string outFilename;
    bool debug;

public:
    void loadFile(std::string filename);
    status_t compile();
    void writeFile();
    void setDebug(const bool value) {
        debug = value;
    }
};

#endif //BRAINDAMAGED_BRAINDAMAGEDASSEMBLER_HPP
