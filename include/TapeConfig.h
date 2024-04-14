#ifndef TAPE_CONFIG_H
#define TAPE_CONFIG_H

#include <string>
#include <chrono>
#include <iostream>
#include <iomanip>

#include <libconfig.h++>

#include "Constants.h"

class TapeConfig {
 private:
    std::string pathToFile;
    long long writeDelay;
    long long readDelay;
    long long changePositionDelay;
    long long tapeScrollDelay;
    libconfig::Config config;

    std::uint8_t readConfig(std::string configPath) {
        try {
            config.readFile(configPath.c_str());
        } catch (const libconfig::FileIOException &fioex) {
            std::cerr << "I/O error occurs while reading config file" << std::endl;
            return kFileIOError;
        } catch(const libconfig::ParseException &pex) {
            std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
              << " - " << pex.getError() << std::endl;
            return kFileParseError;
        }

        const libconfig::Setting& root = config.getRoot();
        const libconfig::Setting& tapeConfig = root["tapeConfig"];
        if (!tapeConfig.lookupValue("writeDelay", this->writeDelay)) {
            std::cerr << "\'writeDelay\' value not found in config file. Aborting..." << std::endl;
            return kConfigValueNotFound;
        }
        if (!tapeConfig.lookupValue("readDelay", this->readDelay)) {
            std::cerr << "\'readDelay\' value not found in config file. Aborting..." << std::endl;
            return kConfigValueNotFound;
        }
        if (!tapeConfig.lookupValue("changePositionDelay", this->changePositionDelay)) {
            std::cerr << "\'changePositionDelay\' value not found in config file. Aborting..." << std::endl;
            return kConfigValueNotFound;
        }
        if (!tapeConfig.lookupValue("tapeScrollDelay", this->tapeScrollDelay)) {
            std::cerr << "\'tapeScrollDelay\' value not found in config file. Aborting..." << std::endl;
            return kConfigValueNotFound;
        }
        return kSuccess;
    }
    void printCurrentConfig() {
        std::cout << "Current configurtion:" << std::endl;
        std::cout << std::setw(22) << "writeDelay: " << this->writeDelay << std::endl
                  << std::setw(22) << "readDelay: " << this->readDelay << std::endl
                  << std::setw(22) << "changePositionDelay: " << this->changePositionDelay << std::endl
                  << std::setw(22) << "tapeScrollDelay: " << this->tapeScrollDelay << std::endl;
    }

 public:
    TapeConfig(std::string configPath) {
        std::uint8_t ret = readConfig(configPath);
        if (ret) {
            std::cerr << "Config parsing failed" << std::endl;
            std::exit(ret);
        }
        printCurrentConfig();

    }
    TapeConfig(TapeConfig&) = delete;
    TapeConfig(TapeConfig&&) = delete;

    ~TapeConfig() = default;
};
#endif // TAPE_CONFIG_H