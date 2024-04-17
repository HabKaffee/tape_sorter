#include <gtest/gtest.h>

#include <random>
#include <filesystem>

#include "TapeSorter.h"

TEST(TapeSorter, intTest) {
    std::vector<int> original;
    std::ofstream ofs;
    std::mt19937 eng;
    std::uniform_int_distribution<> randomizer(-100, 100);

    std::string input = std::string(std::filesystem::current_path()) + "/../tests/test_data/data.txt";
    std::string output = std::string(std::filesystem::current_path()) + "/../tests/test_data/data_out.txt";
    std::string configPath = std::string(std::filesystem::current_path()) + "/../tests/test_data/defaultConf.conf";


    // ofs.open(input, std::ofstream::out | std::ofstream::trunc);
    // for (int i = 0; i < 10; ++i) {
    //     int elem = randomizer(eng);
    //     original.push_back(elem);
    //     ofs << elem;
    //     if (i != 10) {
    //         ofs << " ";
    //     }
    // }
    // ofs.close();
    
    TapeSorter<int> ts(input, output, configPath);
    ts.sortTape();

    std::ifstream ifs;
    ifs.open(output);
    std::vector<int> sortedData;
    while (!ifs.eof()) {
        int item;
        ifs >> item;
        sortedData.push_back(item);
    }

    std::sort(original.begin(), original.end());

    EXPECT_EQ(original.size(), sortedData.size());
    for (int i = 0; i < original.size(); ++i) {
        EXPECT_EQ(original[i], sortedData[i]);
    }
}