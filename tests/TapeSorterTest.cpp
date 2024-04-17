#include <gtest/gtest.h>

#include <random>
#include <filesystem>
#include <string>

#include "TapeSorter.h"

TEST(TapeSorter, intTest) {
    std::string input = std::string(std::filesystem::current_path()) + "/../tests/test_data/data.txt";
    std::string output = std::string(std::filesystem::current_path()) + "/../tests/test_data/data_out.txt";
    std::string configPath = std::string(std::filesystem::current_path()) + "/../tests/test_data/defaultConf.conf";
    if (!std::filesystem::exists(output)) {
        std::ofstream tmp(output);
        tmp.close();
    }

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

    std::fstream ifs(output);
    std::vector<int> sortedData;
    std::stringstream ss;
    if (ifs) {
        ss << ifs.rdbuf();
        ifs.close();
    }
    while (ss) {
        int item;
        ss >> item;
        sortedData.push_back(item);
    }
    sortedData.pop_back();

    std::sort(original.begin(), original.end());

    EXPECT_EQ(original.size(), sortedData.size());
    for (int i = 0; i < original.size(); ++i) {
        EXPECT_EQ(original[i], sortedData[i]);
    }
}
