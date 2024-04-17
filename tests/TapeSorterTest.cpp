#include <gtest/gtest.h>

#include <random>
#include <filesystem>

#include "TapeSorter.h"

TEST(TapeSorter, intTest) {
    // std::mt19937 eng;
    // std::uniform_int_distribution<> randomizer(-100, 100);

    std::string input = std::string(std::filesystem::current_path()) + "/../tests/test_data/data.txt";
    std::string output = std::string(std::filesystem::current_path()) + "/../tests/test_data/data_out.txt";
    std::string configPath = std::string(std::filesystem::current_path()) + "/../tests/test_data/defaultConf.conf";

    std::vector<int> original;
    std::fstream f;
    f.open(input);
    int item;
    while (f >> item) {
        original.push_back(item);
    }
    f.close();
    
    TapeSorter<int> ts(input, output, configPath);
    ts.sortTape();

    std::ifstream ifs;
    ifs.open(output);
    std::vector<int> sortedData;
    while (!ifs.eof()) {
        int item;
        ifs >> item;
        std::cout << item << std::endl;
        sortedData.push_back(item);
    }

    std::sort(original.begin(), original.end());

    EXPECT_EQ(original.size(), sortedData.size());
    for (int i = 0; i < original.size(); ++i) {
        EXPECT_EQ(original[i], sortedData[i]);
    }
}