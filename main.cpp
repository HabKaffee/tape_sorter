#include <iostream>

#include "Constants.h"
#include "TapeInterface.h"


int main() {
    std::string configPath = "config/default.conf";
    std::string fileToOpen = "testFile.txt";
    TapeInterface iface(configPath, fileToOpen);


    std::cout << "Success" << std::endl;
    return kSuccess;
}