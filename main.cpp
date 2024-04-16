#include <iostream>

#include "Constants.h"
#include "TapeConfig.h"
#include "TapeInterface.h"


int main() {
    std::string configPath = "config/default.conf";
    std::string fileToOpen = "testFile.txt";
    TapeInterface iface(configPath, fileToOpen);
    std::cout << "Full tape data:" << std::endl;
    while (!iface.isTapeEnded()) {
        std::cout << iface.readItem<int>() << "\t";
        iface.changePosition(false);
    }
    std::cout << std::endl;
    iface.scrollToStart();

    auto item = iface.readItem<int>();
    std::cout << "Item before change = " <<  item << std::endl;
    iface.changePosition();
    std::cout << iface.readItem<int>() << std::endl;
    iface.changePosition(true);
    std::cout << iface.readItem<int>() << std::endl;
    iface.scrollTape(15);
    std::cout << iface.readItem<int>() << std::endl;
    iface.scrollTape(-15);
    std::cout << iface.readItem<int>() << std::endl;

    iface.scrollToEnd();
    std::cout << iface.readItem<int>() << std::endl;
    iface.changePosition();
    std::cout << "Scroll to end + change pos to right -> " << iface.isTapeEnded() << std::endl;
    iface.changePosition(true);
    std::cout << "is tape ended after move to left from end ? -> " << iface.isTapeEnded() << std::endl;


    iface.scrollToStart();
    std::cout << iface.readItem<int>() << std::endl;
    
    std::cout << "Success" << std::endl;
    return kSuccess;
}