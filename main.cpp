#include <iostream>

#include "Constants.h"
#include "TapeConfig.h"


int main() {
    std::string configPath = "config/default.conf";
    TapeConfig tapeCfg(configPath);
    std::cout << "Success" << std::endl;
    return kSuccess;
}