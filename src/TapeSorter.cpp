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
    for (size_t i = 0; i < numOfTempTapes; ++i) {
        std::filesystem::create_directory("/tmp/tape_sorter/");
        std::string tmpName = "/tmp/tape_sorter/temp_tape" + std::to_string(i);
        temporaryTapes.push_back(new TapeInterface(tapeConfigPath, tmpName));
    }
}

template<typename T>
void TapeSorter<T>::sortTape() {
    
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