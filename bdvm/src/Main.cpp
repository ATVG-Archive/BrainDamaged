#include <fstream>

#include "../../lib/include/cxxopts.hpp"
#include "../include/BrainDamagedVM.hpp"

#define VERSION "0.5.0"

int main(int argc, char* argv[]) {
    std::printf("BrainDamagedVM (v%s)\n", VERSION);

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

    std::vector<i32> data;
    try {
        std::ifstream inFile;
        size_t size = 0;

        inFile.open(filename, std::ios::in | std::ios::binary | std::ios::ate);

        i32* rawData = 0;
        inFile.seekg(0, std::ios::end);
        size = inFile.tellg();
        inFile.seekg(0, std::ios::beg);

        // Size of actual instruction count
        size_t isize = size  / sizeof(i32);

        rawData = new i32[isize];
        inFile.read((char*)rawData, size);
        inFile.close();

        for(size_t i = 0; i < isize; i++) {
            data.push_back(rawData[i]);
        }

        free(rawData);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    BrainDamagedVM vm;
    vm.loadProgram(data);
    vm.setDebug(debug);
    vm.run();

    return 0;
}