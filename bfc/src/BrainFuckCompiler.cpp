//
// Created by atjontv on 4/16/20.
//

#include "../include/BrainFuckCompiler.hpp"
#include "../../bdvm/include/Bytecode.hpp"

BrainFuckCompiler::BrainFuckCompiler() {
}

std::vector<i32> BrainFuckCompiler::compile(const std::string code) {
    i32 brace = 0;
    std::vector<i32> braceCounts;
    for(char i : code) {
        if(brace > 0) {
            braceCounts[brace]++;
        }
        switch (i) {
            case '+':
                instructions.push_back(INC);
                break;
            case '[':
                brace++;
                break;
            case ']':
                i32 icount;
                icount = braceCounts[brace];
                braceCounts[brace] = 0;

                brace--;

                instructions.push_back(icount);
                instructions.push_back(JMP);

                break;
            case '-':
                instructions.push_back(DEC);
                break;
        }
    }

    return instructions;
}