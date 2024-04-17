#ifndef TAPE_SORTER_H
#define TAPE_SORTER_H

#include <string>
#include <vector>
#include <memory>

#include "TapeInterface.h"
template<typename T>
class TapeSorter {
 public:
    TapeSorter(std::string inputTapePath, std::string outputTapePath,
               std::string tapeConfigPath = "../config/default.conf",
               size_t numOfTempTapes = 10) : 
               numOfTempTapes(numOfTempTapes), tapeConfigPath(tapeConfigPath) {
        inputTape = new TapeInterface(tapeConfigPath, inputTapePath);
        outputTape = new TapeInterface(tapeConfigPath, outputTapePath);
        temporaryTapes = std::vector<TapeInterface*>(numOfTempTapes);
        maxValueOnTape = inputTape->readItem<T>();
    }

    TapeSorter(TapeSorter&) = delete;
    TapeSorter(TapeSorter&&) = delete;
    
    ~TapeSorter() {
        for (size_t i = 0; i < numOfTempTapes; ++i) {
            delete temporaryTapes[i];
        }
        delete inputTape;
        delete outputTape;
    }

    void sortTape();

 private:
    const size_t numOfTempTapes;
    const std::string tapeConfigPath;
    T maxValueOnTape;

    TapeInterface* inputTape;
    TapeInterface* outputTape;
    std::vector<TapeInterface*> temporaryTapes;
    
    void findMaxValueOnTape();
    void createTemporaryTapes();
    std::vector<T> sortTemporaryTape(size_t idx);
};

#endif // TAPE_SORTER_H