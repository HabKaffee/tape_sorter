#ifndef TAPE_READER_H
#define TAPE_READER_H

#include <chrono>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

#include "TapeConfig.h"

class TapeConfig;

class TapeInterface {
 public:
    TapeInterface(std::string configPath, std::string fileToRead);
    TapeInterface(TapeInterface&) = delete;
    TapeInterface(TapeInterface&&) = delete;
    ~TapeInterface();

    template<typename T>
    T readItem() {
      std::this_thread::sleep_for(std::chrono::nanoseconds(tapeConfig->getReadDelay()));
      T item;
      inputFile >> item;
      return item;
    }
    
    template<typename T>
    void writeItem(T toWrite) {
      if (!inputFile.is_open()) {
         std::cerr << "Tape can not be accessed. Aborting";
         delete tapeConfig;
         std::exit(kFileNotOpen);
      }
      std::this_thread::sleep_for(std::chrono::nanoseconds(tapeConfig->getWriteDelay()));
      inputFile << toWrite << " ";
    }

    template<class T>
    std::vector<T> read(int& numOfItems) {
      std::vector<T> result;
      for (int i = 0; i < numOfItems; ++i) {
         result.emplace_back(readItem<T>());
      }
      return result;
    }

    template<class T>
    void write(std::vector<T> toWrite) {
      for (auto item: toWrite) {
         writeItem(item);
      }
    }
    
    void changePosition(bool changeToTheLeft = false);
    void scrollTape(int numOfPositions);
    void scrollToStart();
    void scrollToEnd();

    bool isTapeEnded() {
      return inputFile.eof();
    }

 private:
    TapeConfig* tapeConfig;
    std::ifstream inputFile;
};

#endif // TAPE_READER_H