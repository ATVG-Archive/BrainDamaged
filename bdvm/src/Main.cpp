#include <fstream>

#include "../include/BrainDamagedVM.hpp"

int main(int argc, char* argv[]) {
    std::printf("BrainDamagedVM (v0.4.0)\n");
    if(argc < 2 || argc > 3) {
    #ifdef linux
        std::printf("Usage: %s [-d] <filename>", basename(argv[0]));
    #endif
    #ifdef _WIN32
        std::printf("Usage: BrainDamagedVM.exe [-d] <filename>");
    #endif
        return 1;
    }

    std::vector<i32> data;
    try {
        std::ifstream inFile;
        size_t size = 0;

        // TODO: Remove this
        if (argc == 3 && std::string(argv[1]) == "-d") {
            inFile.open(argv[2], std::ios::in | std::ios::binary | std::ios::ate);
        }

        // TODO: Remove this
        if (argc == 2 && std::string(argv[1]) != "-d") {
            inFile.open(argv[1], std::ios::in | std::ios::binary | std::ios::ate);
        }

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
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    BrainDamagedVM vm;
    vm.loadProgram(data);

    // TODO: Remove this
    if (argc == 3 && std::string(argv[1]) == "-d") {
        vm.setDebug(true);
    }

    // TODO: Remove this
    if (argc == 2 && std::string(argv[1]) != "-d") {
        vm.setDebug(false);
    }
    vm.run();

    return 0;
}