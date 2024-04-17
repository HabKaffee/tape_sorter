#include <cmath>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <random>

#include "Constants.h"
#include "TapeSorter.h"


int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "You should provide path to input file, output file and configuration file(optional)" << std::endl;
        std::exit(kConfigValueNotFound);
    }
    std::string inputTapePath, outputTapePath, configPath;
    if (argc >= 3) {
        inputTapePath = std::string(argv[1]);
        outputTapePath = std::string(argv[2]);
        if (argc > 3) {
            configPath = std::string(argv[3]);
        }
    }

    if (std::filesystem::exists(std::filesystem::temp_directory_path() / "tape_sorter")) {
        for (auto& path : std::filesystem::directory_iterator(
                std::filesystem::temp_directory_path() / "tape_sorter")) {
            std::filesystem::remove(path);
        }
    }
    
    if (configPath.empty()) {
        configPath = "config/default.conf";
    }

    TapeSorter<int> sorter(inputTapePath, outputTapePath, configPath, 10);
    sorter.sortTape();

    std::cout << "Success" << std::endl;
    return kSuccess;
}