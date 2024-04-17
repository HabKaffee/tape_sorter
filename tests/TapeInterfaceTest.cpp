#include <gtest/gtest.h>

#include <filesystem>

#include "TapeInterface.h"

TEST(TapeIface, changePosToTheLeft) {
    std::string configPath = 
        std::string(std::filesystem::current_path()) + "/../config/default.conf";
    std::string inputDataPath = 
        std::string(std::filesystem::current_path()) + "/../tests/test_data/data.txt";
    TapeInterface iface(configPath, inputDataPath);
    iface.changePosition(/*changeToTheLeft = */true);
    int item = iface.readItem<int>();
    EXPECT_EQ(94, item);
}

TEST(TapeIface, changePosToTheRight) {
    std::string configPath = 
        std::string(std::filesystem::current_path()) + "/../config/default.conf";
    std::string inputDataPath = 
        std::string(std::filesystem::current_path()) + "/../tests/test_data/data.txt";
    TapeInterface iface(configPath, inputDataPath);
    iface.changePosition(/*changeToTheLeft = */false);
    int item = iface.readItem<int>();
    EXPECT_EQ(-38, item);
}

TEST(TapeIface, changePosToTheLeftAndRight) {
    std::string configPath = 
        std::string(std::filesystem::current_path()) + "/../config/default.conf";
    std::string inputDataPath = 
        std::string(std::filesystem::current_path()) + "/../tests/test_data/data.txt";
    TapeInterface iface(configPath, inputDataPath);
    iface.changePosition(/*changeToTheLeft = */true);
    iface.changePosition(/*changeToTheLeft = */true);
    int item = iface.readItem<int>();
    EXPECT_EQ(94, item);
    iface.changePosition(/*changeToTheLeft = */false);
    iface.changePosition(/*changeToTheLeft = */false);
    iface.changePosition(/*changeToTheLeft = */false);
    item = iface.readItem<int>();
    EXPECT_EQ(-9, item);
}
