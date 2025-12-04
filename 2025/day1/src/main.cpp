#include <memory>
#include <iostream>
#include <fstream>
#include <string>

#include "dial.h"


std::string INPUT_DIR = "day1/input/";

int main(int argc, char **argv) 
{ 
    // Argument checking
    if (argc != 2) {
        std::cout << "Invalid number of arguments." << std::endl;
        return -1;
    }

    // Setup input file
    const std::string inputFilePath = INPUT_DIR + argv[1];
    std::ifstream inputFile(inputFilePath);
    std::string line;

    // Check file exists
    if (!inputFile) {
        std::string errMsg = "Error opening file `" + inputFilePath + "`";
        std::perror(errMsg.c_str());
        return -1;
    }

    // Initialise
    uint8_t initCondition = 50;
    Dial dial(initCondition); 

    // Loop over and update position
    while (std::getline(inputFile, line)) {
        dial.UpdatePosition(line);
    }

    // Finish and close
    dial.ReportZeroCounter();
    inputFile.close();
    return 0;
}