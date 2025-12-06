#include <cassert>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "repeatingSequenceInt.h"

std::string INPUT_DIR = "day2/input/";

std::vector<std::string> parseIdFile(std::string aFileContents) 
{
    std::vector<std::string> idList;
    std::istringstream is(aFileContents);
    std::string idRange;
    // size_t rangeCount = 0;
    while (std::getline(is, idRange, ',')) {
        // std::cout << "Range #" << std::to_string(++rangeCount) << ": " << idRange << std::endl;
        idList.push_back(idRange);
    }

    return idList;
}

bool isEven(size_t aValue) 
{
    return !(aValue % 2);
}

std::vector<std::string> scanIdRangeAscending(std::string aLowerId, std::string aUpperId)
{
    std::vector<std::string> invalidIds;
    uint64_t upperValue = std::stoll(aUpperId);
    uint64_t lowerValue = std::stoll(aLowerId);
    for (RepeatingSequenceInt invalidId(aLowerId); invalidId.value() <= upperValue; ++invalidId)
    {
        // May initialise below the range
        if (invalidId.value() < lowerValue)
            continue;

        size_t digitCount = invalidId.asString().size() - 1;
        assert((digitCount >= aLowerId.size() - 1) && (digitCount <= aUpperId.size() - 1));
        // std::cout << "Invalid ID Detected: " << invalidId.asString() << std::endl;
        invalidIds.push_back(invalidId.asString());
    }

    return invalidIds;
}

std::vector<std::string> scanIdRangeDescending(std::string aLowerId, std::string aUpperId)
{
    std::vector<std::string> invalidIds;
    uint64_t upperValue = std::stoll(aUpperId);
    uint64_t lowerValue = std::stoll(aLowerId);
    for (RepeatingSequenceInt invalidId(aUpperId); (invalidId.size() > 1) && invalidId.value() >= lowerValue; --invalidId)
    {
        // May initialise above the range
        if (invalidId.value() > upperValue)
            continue;

        size_t digitCount = invalidId.asString().size() - 1;
        assert((digitCount >= aLowerId.size() - 1) && (digitCount <= aUpperId.size() - 1));
        // std::cout << "Invalid ID Detected: " << invalidId.asString() << std::endl;
        invalidIds.push_back(invalidId.asString());
    }

    return invalidIds;
}

void logIdRangeValidity(std::string aRange, std::vector<std::string> invalidIdList)
{
    // Assemble message
    std::vector<std::string> invalidIdMessageList;
    std::string plural = "";
    if (invalidIdList.size() > 1) {
        plural = "s";
        for (std::string invalidId : invalidIdList)
        {
            invalidIdMessageList.push_back(", " + invalidId);
        }
        invalidIdMessageList.pop_back();
        invalidIdMessageList.push_back(" and " + invalidIdList.back() + ".");
    } else {
        invalidIdMessageList.push_back(" " + invalidIdList.front() + ".");
    }

    // Print the log
    std::cout << aRange << " has " << std::to_string(invalidIdList.size()) << " invalid ID" << plural;
    for (auto msg : invalidIdMessageList)
    {
        std::cout << msg;
    }
    std::cout << std::endl;
}

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

    // Read in contents
    std::getline(inputFile, line);
    // parse input to vector
    std::vector<std::string> idList = parseIdFile(line);

    // iterate vector and check validity of ID range
    std::vector<std::string> invalidIds;
    uint64_t invalidIdSum = 0;
    size_t rangeId = 0;
    for (auto idRange : idList) {
        ++rangeId;
        int rangeDelimPos = idRange.find('-');
        std::string lowerId = idRange.substr(0,rangeDelimPos);
        std::string upperId = idRange.substr(rangeDelimPos + 1, idRange.size());
        // std::cout << "Range #" << std::to_string(rangeId) << " - Lower = " << lowerId \
        //     << "\tUpper = " << upperId << std::endl;

        std::vector<std::string> rangeInvalidIds;
        size_t numberOfDigitsLower = lowerId.size();
        size_t numberOfDigitsUpper = upperId.size();
        if (!isEven(numberOfDigitsLower) && (numberOfDigitsLower == numberOfDigitsUpper)) {
            // All odd digit IDs are valid
            continue; 
        } else if (!isEven(numberOfDigitsLower)) {
            rangeInvalidIds = scanIdRangeDescending(lowerId, upperId);
        } else {
            rangeInvalidIds = scanIdRangeAscending(lowerId, upperId);
        }
        
        if (rangeInvalidIds.size() > 0)
        {
            invalidIds.insert(invalidIds.end(), rangeInvalidIds.begin(), rangeInvalidIds.end());
            // logIdRangeValidity(idRange, rangeInvalidIds);
        }
        for (auto invalidId : rangeInvalidIds)
        {
            std::cout << std::to_string(invalidIdSum) << "\t + " << invalidId << std::endl;
            uint64_t idValue = std::stoll(invalidId);
            invalidIdSum += idValue;
        }
    }
    
    std::cout << "Adding up all the invalid IDs produces " << invalidIdSum << std::endl;

    return 0;
}