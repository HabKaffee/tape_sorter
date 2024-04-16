#include <cmath>
#include <filesystem>

#include "TapeSorter.h"


template<typename T>
void TapeSorter<T>::findMaxValueOnTape() {
    while (!inputTape->isTapeEnded()) {
        maxValueOnTape = std::max(maxValueOnTape, inputTape->readItem<T>());
        inputTape->changePosition(/*changeToTheLeft =*/false);
    }
    inputTape->scrollToStart();
}

template<typename T>
void TapeSorter<T>::createTemporaryTapes() {
    std::filesystem::create_directory("/tmp/tape_sorter/");
    for (size_t i = 0; i < numOfTempTapes; ++i) {
        std::string tmpName = "/tmp/tape_sorter/temp_tape" + std::to_string(i) + ".txt";
        temporaryTapes[i] = new TapeInterface(tapeConfigPath, tmpName);
    }
}

template<typename T>
void TapeSorter<T>::sortTape() {
    createTemporaryTapes();
    findMaxValueOnTape();
    int M = static_cast<int>(maxValueOnTape) + 1;
    while (!inputTape->isTapeEnded()) {
        T elem = inputTape->readItem<T>();
        size_t tempTapeIdx = 
            static_cast<size_t>(std::floor((numOfTempTapes * elem) / M));
        temporaryTapes[tempTapeIdx]->writeItem<T>(elem);
        inputTape->changePosition(/*changeToTheLeft =*/false);
    }

}

template void TapeSorter<int>::createTemporaryTapes();
template void TapeSorter<float>::createTemporaryTapes();
template void TapeSorter<double>::createTemporaryTapes();

template void TapeSorter<int>::sortTape();
template void TapeSorter<float>::sortTape();
template void TapeSorter<double>::sortTape();

template void TapeSorter<int>::findMaxValueOnTape();
template void TapeSorter<float>::findMaxValueOnTape();
template void TapeSorter<double>::findMaxValueOnTape();