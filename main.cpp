#include <iostream>

#include "Constants.h"
#include "TapeConfig.h"
#include "TapeInterface.h"


int main() {
    std::string configPath = "config/default.conf";
    std::string fileToOpen = "testFile.txt";
    TapeInterface iface(configPath, fileToOpen);
    // while (!iface.isTapeEnded()) {
    //     auto item = iface.readItem<int>();
    //     std::cout << item << std::endl;
    // }
    auto item = iface.readItem<int>();
    std::cout << item << std::endl;
    iface.changePosition();
    iface.changePosition();
    // iface.changePosition();
    // iface.changePosition();
    // std::cout << iface.readItem<int>() << std::endl;
    // item = iface.readItem<int>();
    auto item2 = iface.readItem<int>();
    std::cout << item << " " << item2 << std::endl;

    std::cout << "Success" << std::endl;
    return kSuccess;
}