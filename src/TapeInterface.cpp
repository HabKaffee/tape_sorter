#include "Constants.h"
#include "TapeInterface.h"

TapeInterface::TapeInterface(std::string configPath, std::string fileToRead) {
    this->tapeConfig = new TapeConfig(configPath);
    if (this->tapeConfig == nullptr) {
        std::cerr << "Can not allocate memory for tapeConfig" << std::endl;
        std::exit(kNotEnoughMemory);
    }
    tapeData.open(fileToRead);
    if (!tapeData.is_open()) {
        std::cerr << "Can't open file '" << fileToRead << "'" << std::endl;
        delete this->tapeConfig;
        std::exit(kFileNotOpen);
    }
}

TapeInterface::~TapeInterface() {
    tapeData.close();
    delete this->tapeConfig;
}

void TapeInterface::recoverFileStream(bool changedToLeft/* = false*/) {
    if (changedToLeft) {
        tapeData.seekg(0);
        tapeData.clear();
    } else {
        tapeData.seekg(0, tapeData.end);
        tapeData.clear();
        
        tapeData.unget();
        char sym = tapeData.get();
        while (sym != ' ') {
            tapeData.putback(sym);
            tapeData.unget();
            sym = tapeData.get();
        }
    }
}

void TapeInterface::changePositionImpl(bool changeToTheLeft/* = false*/) {
    if (changeToTheLeft) {
        tapeData.unget();
        if (isFileStreamBroken()) {
            recoverFileStream(/*changedToLeft = */true);
            return;
        }
        tapeData.unget();
        if (isFileStreamBroken()) {
            recoverFileStream(/*changedToLeft = */true);
            return;
        }
        char toRetrieve = tapeData.get();
        while (toRetrieve != ' ') {
            tapeData.unget();
            if (isFileStreamBroken()) {
                recoverFileStream(/*changedToLeft = */true);
                return;
            }
            tapeData.unget();
            if (isFileStreamBroken()) {
                recoverFileStream(/*changedToLeft = */true);
                return;
            }
            toRetrieve = tapeData.get();
        }
    } else {
        while (char sym = tapeData.get()) {
            if (sym == ' ' || tapeData.eof()) {
                break;
            }
        }
        if (tapeData.eof()) {
            recoverFileStream(/*changedToLeft = */false);
        }
    }
}

void TapeInterface::changePosition(bool changeToTheLeft/* = false*/) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(tapeConfig->getChangePositionDelay()));
    changePositionImpl(changeToTheLeft);
}

void TapeInterface::scrollTape(int numOfPositions) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(tapeConfig->getTapeScrollDelay()));
    bool changeToTheLeft = numOfPositions < 0;
    numOfPositions = std::abs(numOfPositions);

    for (int i = 0; i < numOfPositions; ++i) {
        changePositionImpl(changeToTheLeft);
    }
}

void TapeInterface::scrollToStart() {
    std::this_thread::sleep_for(std::chrono::nanoseconds(tapeConfig->getTapeScrollDelay()));
    tapeData.seekg(0);
}

void TapeInterface::scrollToEnd() {
    tapeData.seekg(0, tapeData.end);
    tapeData.unget();
    char sym = tapeData.get();
    while (sym != ' ') {
        tapeData.putback(sym);
        tapeData.unget();
        sym = tapeData.get();
    }
}
