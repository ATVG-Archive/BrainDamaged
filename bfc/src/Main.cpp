#include <cxxopts.hpp>
#include "../include/BrainFuckCompiler.hpp"

#define VERSION "0.2.0"

int main(int argc, char* argv[]) {
    std::printf("BrainFuckCompiler (v%s)\n", VERSION);
    cxxopts::Options options("BrainDamagedVM", "A 32-bit Bytecode Virtual Machine");
    options.add_options()
            ("if,ifile", "Input File", cxxopts::value<std::string>())
            ("of,ofile", "Input File", cxxopts::value<std::string>())
            ("enable-bdvm-extensions", "Enable BDVM Extensions to the Brainfuck Language", cxxopts::value<bool>()->default_value("false"))
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

    const std::string inFilename = args["ifile"].as<std::string>();
    const std::string outFileName = args["ofile"].as<std::string>();

    const bool enableExtensions = args["enable-bdvm-extensions"].as<bool>();

    BrainFuckCompiler compiler;
    compiler.setBDExtensions(enableExtensions);
    compiler.loadFile(inFilename);
    status_t s = compiler.compile();

    if(!outFileName.empty())
        compiler.writeFile(outFileName);
    else
        compiler.writeFile(std::string{});

    return s;
}