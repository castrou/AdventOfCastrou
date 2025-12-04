#include <string>
#include <tuple>

#include "dial.h"

Dial::Dial(uint8_t aInitPosition) 
    : mPosition(aInitPosition) 
    , mZeroCounter(0)
{
    std::cout << "The dial starts by pointing at 50" << std::endl;

    if (aInitPosition == 0)
    {
        ++mZeroCounter;
    }
}

void Dial::Part1PositionUpdate(std::string& aRotCode) {
    auto direction = static_cast<Dial::Direction>(aRotCode.front());
    uint8_t angle = std::stoi(aRotCode.substr(1, aRotCode.size() - 1)) % (Dial::sMaxPosition);

    // Update the angle, constraining between 0-100
    if (direction == Direction::POSITIVE_ROT) {
        mPosition = (mPosition + angle) % Dial::sMaxPosition;
    } else {
        mPosition = (((mPosition - angle) + Dial::sMaxPosition) % Dial::sMaxPosition);
    }

    // Check if at zero position
    if (mPosition == 0) {
        ++mZeroCounter;
    }

    std::cout << "The dial is rotated " << aRotCode << " to point at " << std::to_string(mPosition) << "." << std::endl;
}

void printDialRotationStats(std::string& aRotCode, uint8_t aFinalPos, uint64_t zeroCrossCount)
{
    std::string statsMessage = "The dial is rotated " + aRotCode + " to point at " 
                                + std::to_string(aFinalPos);

    if (zeroCrossCount > 0) {
        if (zeroCrossCount == 1 && aFinalPos != 0) {
            statsMessage += "; during this rotation, it points at 0 once";
        } else if (zeroCrossCount > 1) {
            statsMessage += "; during this rotation, it points at 0 " 
                                + std::to_string(zeroCrossCount) + " times";
        } 
    }
    statsMessage += ".";

    std::cout << statsMessage << std::endl;

}

void Dial::Part2PositionUpdate(std::string& aRotCode) {
    uint64_t zeroCrossCount = 0;
    auto direction = static_cast<Dial::Direction>(aRotCode.front());
    int64_t angle = std::stoi(aRotCode.substr(1, aRotCode.size() - 1));

    // Check angle change
    if (angle >= Dial::sMaxPosition) {
        zeroCrossCount += angle / Dial::sMaxPosition;
        angle %= Dial::sMaxPosition;
    }

    // Update the angle, constraining between 0-100
    int64_t newPos;
    if (direction == Direction::POSITIVE_ROT) {
        newPos = (mPosition + angle);
    } else {
        newPos = (mPosition - angle);
    }

    // Dial passing zero checks
    // Lands on zero
    if (newPos == 0) {
        ++zeroCrossCount;
    }
    // Exceeds moving leftwards
    if (newPos < 0) {
        // doesn't cross zero if it starts there
        if (mPosition != 0) {
            ++zeroCrossCount;
        }
        newPos += Dial::sMaxPosition;
    }
    // Exceeds moving rightwards
    if (newPos >= Dial::sMaxPosition) {
        ++zeroCrossCount;
    }
    
    mPosition = newPos % Dial::sMaxPosition; // constrain to [0..99]
    mZeroCounter += zeroCrossCount;
    printDialRotationStats(aRotCode, mPosition, zeroCrossCount);
}


void Dial::UpdatePosition(std::string& aRotCode) {
    // Part1PositionUpdate(aRotCode);
    Part2PositionUpdate(aRotCode);
}