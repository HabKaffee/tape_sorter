#include "Constants.h"
#include "TapeInterface.h"

TapeInterface::TapeInterface(std::string configPath, std::string fileToRead) {
    this->tapeConfig = new TapeConfig(configPath);
    if (this->tapeConfig == nullptr) {
        std::cerr << "Can not allocate memory for tapeConfig" << std::endl;
        std::exit(kNotEnoughMemory);
    }
    inputFile.open(fileToRead);
    if (!inputFile.is_open()) {
        std::cerr << "Can't open file '" << fileToRead << "'" << std::endl;
        delete this->tapeConfig;
        std::exit(kFileNotOpen);
    }
}

TapeInterface::~TapeInterface() {
    delete this->tapeConfig;
}

// TODO: Fix behaviour
void TapeInterface::changePosition(bool changeToTheLeft/* = false*/) {
    if (changeToTheLeft) {
        while (inputFile.tellg() != inputFile.beg && inputFile.get() != ' ') {
            inputFile.seekg(-1, inputFile.cur);
        }
    } else {
        while (inputFile.tellg() != inputFile.end && inputFile.get() != ' ') {
            inputFile.seekg(1, inputFile.cur);
        }
    }
}

void TapeInterface::scrollTape(int numOfPositions) {

}

void TapeInterface::scrollToStart() {

}

void TapeInterface::scrollToEnd() {

}
