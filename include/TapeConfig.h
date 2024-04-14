#ifndef TAPE_CONFIG_H
#define TAPE_CONFIG_H

#include <chrono>
#include <iostream>
#include <iomanip>
#include <string>

#include <libconfig.h++>

#include "Constants.h"

class TapeConfig {
 public:
    TapeConfig(std::string configPath);
    TapeConfig(TapeConfig&) = delete;
    TapeConfig(TapeConfig&&) = delete;

    ~TapeConfig() = default;

 private:
    std::string pathToFile;
    long long writeDelay;
    long long readDelay;
    long long changePositionDelay;
    long long tapeScrollDelay;
    libconfig::Config config;

    std::uint8_t readConfig(std::string configPath);

    void printCurrentConfig();
};
#endif // TAPE_CONFIG_H