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

TEST(TapeSorter, doubleTest) {
    std::string input = std::string(std::filesystem::current_path()) + "/../tests/test_data/data2.txt";
    std::string output = std::string(std::filesystem::current_path()) + "/../tests/test_data/data_out2.txt";
    std::string configPath = std::string(std::filesystem::current_path()) + "/../tests/test_data/defaultConf.conf";
    
    std::vector<double> original;
    if (!std::filesystem::exists(input)) {
        std::ofstream tmp(input);
        std::mt19937 eng;
        std::uniform_real_distribution<> randomizer(-100, 100);

        for (int i = 0; i < 100; ++i) {
            double item;
            item = randomizer(eng);
            original.push_back(item);
            tmp << item;
            if (i < 99)
                tmp << " ";
        }
        tmp.close();
    } else {
        std::ifstream tmp(input);
        double item;
        while (tmp >> item) {
            original.push_back(item);
        }
    }
    if (!std::filesystem::exists(output)) {
        std::ofstream tmp(output);
        tmp.close();
    }
    
    TapeSorter<double> ts(input, output, configPath);
    ts.sortTape();

    std::ifstream ifs(output);
    std::vector<double> sortedData;
    std::stringstream ss;
    double item;
    while (ifs >> item) {
        sortedData.push_back(item);
    }
    ifs.close();

    std::sort(original.begin(), original.end());

    EXPECT_EQ(original.size(), sortedData.size());
    for (int i = 0; i < original.size(); ++i) {
        EXPECT_DOUBLE_EQ(original[i], sortedData[i]);
    }
}