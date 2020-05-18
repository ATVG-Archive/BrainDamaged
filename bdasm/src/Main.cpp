//
// Created by atjontv on 4/16/20.
//

#include <iostream>
#include <cxxopts.hpp>

#include "../include/BrainDamagedAssembler.hpp"

#define VERSION "0.4.0"

int main(int argc, char* argv[]) {
    std::printf("BrainDamagedAssembler (v%s)\n", VERSION);

    cxxopts::Options options("BrainDamagedVM", "A 32-bit Bytecode Virtual Machine");
    options.add_options()
            ("f,file", "Input File", cxxopts::value<std::string>())
            ("d,debug", "Enable Debug output", cxxopts::value<bool>()->default_value("false"))
            ("v,version", "Print Version")
            ("h,help", "Print usage")
            ;

    const auto args = options.parse(argc, argv);

    if (args.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    if(args.count("version")) {
        std::printf("Version %s\n", VERSION);
        return 0;
    }

    if(!args.count("file")) {
        std::cout << options.help() << std::endl;
        std::cerr << "Missing file parameter, -f or --file must be specified" << std::endl;
        return 1;
    }

    const std::string filename = args["file"].as<std::string>();

    const bool debug = args["debug"].as<bool>();

    BrainDamagedAssembler assembler;

    assembler.setDebug(debug);
    assembler.loadFile(filename);

    i32 s = assembler.compile();
    assembler.writeFile();

    return s;
}