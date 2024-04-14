#include "Constants.h"
#include "TapeInterface.h"

TapeInterface::TapeInterface(std::string configPath, std::string fileToRead) {
    this->tapeConfig = new TapeConfig(configPath);
    inputFile.open(fileToRead);
    if (!inputFile.is_open()) {
        std::cerr << "Can't open file '" << fileToRead << "'!" << std::endl;
        delete this->tapeConfig;
        std::exit(kFileNotOpen);
    }
}

TapeInterface::~TapeInterface() {
    delete this->tapeConfig;
}

template<typename T>
T TapeInterface::read() {

}

bool TapeInterface::write() {
    return true;
}

void TapeInterface::changePosition(bool changeToTheLeft /* = false*/) {

}

void TapeInterface::scrollTape(int numOfPositions) {

}

void TapeInterface::scrollToStart() {

}

void TapeInterface::scrollToEnd() {

}
