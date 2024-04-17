#include <algorithm>
#include <cmath>
#include <filesystem>

#include "TapeSorter.h"


template<typename T>
void TapeSorter<T>::findMaxValueOnTape() {
    while (!inputTape->isTapeEnded()) {
        maxValueOnTape = std::max(maxValueOnTape, inputTape->readItem<T>());
    }
    inputTape->scrollToStart();
}

template<typename T>
void TapeSorter<T>::createTemporaryTapes() {
    std::string basePath = std::filesystem::temp_directory_path() / "tape_sorter/";
    std::filesystem::create_directory(basePath);
    for (size_t i = 0; i < numOfTempTapes; ++i) {
        std::string tmpName = 
            basePath + "temp_tape" + std::to_string(i) + ".txt";
        temporaryTapes[i] = new TapeInterface(tapeConfigPath, tmpName);
    }
}

template<typename T>
std::vector<T> TapeSorter<T>::sortTemporaryTape(size_t idx) {
    std::vector<T> temporaryTapeData = 
        temporaryTapes[idx]->read<T>(-1); // read all data from tape
    std::sort(temporaryTapeData.begin(), temporaryTapeData.end());
    return temporaryTapeData;
}

template<typename T>
void TapeSorter<T>::sortTape() {
    createTemporaryTapes();
    findMaxValueOnTape();

    while (!inputTape->isTapeEnded()) {
        T elem = inputTape->readItem<T>();
        if (elem < 0) {
            temporaryTapes[0]->writeItem<T>(elem);
            continue;
        }
        int bucketRatio = static_cast<int>(maxValueOnTape / static_cast<double>(numOfTempTapes));
        if (elem >= bucketRatio * static_cast<int>(numOfTempTapes)) {
            temporaryTapes[numOfTempTapes - 1]->writeItem<T>(elem);
            continue;
        }
        for (int i = 1; i <= static_cast<int>(numOfTempTapes); ++i) {
            if (elem >= (bucketRatio * (i - 1)) && elem < (bucketRatio * i)) {
                temporaryTapes[i - 1]->writeItem<T>(elem);
            }
        }
    }

    for (size_t tapeIdx = 0; tapeIdx < temporaryTapes.size(); ++tapeIdx) {
        temporaryTapes[tapeIdx]->scrollToStart();
    }

    for (size_t tapeIdx = 0; tapeIdx < temporaryTapes.size(); ++tapeIdx) {
        if (temporaryTapes[tapeIdx]->isTapeEmpty()) {
            continue;
        }
        auto temporaryTapeData = sortTemporaryTape(tapeIdx);
        if (temporaryTapeData.empty()) {
            return;
        }
        outputTape->write(temporaryTapeData);
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

template std::vector<int> TapeSorter<int>::sortTemporaryTape(size_t idx);
template std::vector<float> TapeSorter<float>::sortTemporaryTape(size_t idx);
template std::vector<double> TapeSorter<double>::sortTemporaryTape(size_t idx);