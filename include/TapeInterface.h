#ifndef TAPE_READER_H
#define TAPE_READER_H

#include <chrono>
#include <fstream>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

#include "TapeConfig.h"

class TapeConfig;

class TapeInterface {
 public:
    TapeInterface(std::string configPath, std::string fileToRead);
    TapeInterface(TapeInterface&) = default;
    TapeInterface(TapeInterface&&) = default;
    ~TapeInterface();

    template<typename T>
    T readItem() {
      std::this_thread::sleep_for(std::chrono::nanoseconds(tapeConfig->getReadDelay()));
      T item;
      tapeData >> item;
      std::this_thread::sleep_for(std::chrono::nanoseconds(tapeConfig->getChangePositionDelay()));
      return item;
    }
    
    template<typename T>
    void writeItem(T toWrite) {
      if (!tapeData.is_open()) {
         std::cerr << "Tape can not be accessed. Aborting...";
         delete tapeConfig;
         std::exit(kFileNotOpen);
      }
      std::this_thread::sleep_for(std::chrono::nanoseconds(tapeConfig->getWriteDelay()));
      tapeData << toWrite << " ";
    }

    template<class T>
    std::vector<T> read(const int& numOfItems) {
      std::vector<T> result;
      if (!tapeData.is_open()) {
        std::cout << "File can't be accessed\n";
        return std::vector<T>();
      }
      if (numOfItems == -1) {
        while(!isTapeEnded()) {
          result.emplace_back(readItem<T>());
        }
        result.pop_back();
        return result;
      }
      for (int i = 0; !isTapeEnded() && (i < numOfItems); ++i) {
         result.emplace_back(readItem<T>());
      }
      return result;
    }

    template<class T>
    void write(std::vector<T>& toWrite) {
      for (auto item: toWrite) {
         writeItem(item);
      }
    }
    
    void changePosition(bool changeToTheLeft = false);
    void scrollTape(int numOfPositions);
    void scrollToStart();
    void scrollToEnd();

    bool isTapeEnded() {
      return tapeData.eof() || isEndRecovered;
    }

    bool isTapeEmpty() {
      return tapeData.peek() == std::fstream::traits_type::eof();
    }

 private:
    bool isFileStreamBroken() {
      return tapeData.bad();
    }

    void recoverFileStream(bool changedToLeft = false);

    void changePositionImpl(bool changeToTheLeft = false);

    bool isEndRecovered = false;
    TapeConfig* tapeConfig;
    std::fstream tapeData;
};

#endif // TAPE_READER_H