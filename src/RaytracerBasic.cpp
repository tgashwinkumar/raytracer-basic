#include <iostream>
#include <string>
#include "RaytracerBasicConfig.h"

int main(int argc, char** argv){
    if(argc < 2){
        const double inputValue = std::stod(argv[1]);
        std::cout << argv[0] << "Version " << RaytracerBasic_VERSION_MAJOR << "."
                    << RaytracerBasic_VERSION_MINOR << std::endl;

        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }
    return 0;
}