#ifndef TAPE_READER_H
#define TAPE_READER_H

#include <fstream>
#include <string>

#include "TapeConfig.h"

class TapeConfig;

class TapeInterface {
 public:
    TapeInterface(std::string configPath, std::string fileToRead);
    TapeInterface(TapeInterface&) = delete;
    TapeInterface(TapeInterface&&) = delete;
    ~TapeInterface();

    template<typename T>
    T read();
    bool write();
    void changePosition(bool changeToTheLeft = false);
    void scrollTape(int numOfPositions);
    void scrollToStart();
    void scrollToEnd();

 private:
    TapeConfig* tapeConfig;
    std::ifstream inputFile;
};

#endif // TAPE_READER_H