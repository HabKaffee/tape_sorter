#include "TapeConfig.h"

TapeConfig::TapeConfig(std::string configPath) {
    std::uint8_t ret = readConfig(configPath);
    if (ret != kSuccess) {
        std::cerr << "Config parsing failed" << std::endl;
        std::exit(ret);
    }
    #ifdef DEBUG
    printCurrentConfig();
    #endif
}

std::uint8_t TapeConfig::readConfig(std::string configPath) {
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
    try {
        const libconfig::Setting& root = config.getRoot();
        const libconfig::Setting& tapeConfig = root["application"]["tapeConfig"];
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
    } catch (const libconfig::SettingNotFoundException &snfe) {
        std::cerr << "Not found setting in config file" << std::endl;
        return kSettingNotExists;
    }
    return kSuccess;
}

void TapeConfig::printCurrentConfig() {
    std::cout << "Current configurtion:" << std::endl;
    std::cout << std::setw(22) << "writeDelay: " << this->writeDelay << std::endl
                << std::setw(22) << "readDelay: " << this->readDelay << std::endl
                << std::setw(22) << "changePositionDelay: " << this->changePositionDelay << std::endl
                << std::setw(22) << "tapeScrollDelay: " << this->tapeScrollDelay << std::endl;
    std::cout << std::endl;
}

long long TapeConfig::getWriteDelay() {
    return writeDelay;
}

long long TapeConfig::getReadDelay() {
    return readDelay;
}

long long TapeConfig::getChangePositionDelay() {
    return changePositionDelay;
}

long long TapeConfig::getTapeScrollDelay() {
    return tapeScrollDelay;
}