#pragma once

#include <iostream>
#include <cstdint>
#include <string>

class Dial {

public:
    Dial(uint8_t aInitPosition);
    ~Dial() {};

    enum class Direction { NEGATIVE_ROT = 'L', POSITIVE_ROT = 'R' };
    
    /// @brief Update the current position of the dial.
    /// @arg int aRotCode : Angle change code [LR]<magnitude> (eg. R42, L69)
    void UpdatePosition(std::string& aRotCode);

    /// @brief Report the state of the zero counter to commandline
    void ReportZeroCounter() { std::cout << "Number of times the dial is left pointing at 0: " << std::to_string(mZeroCounter) << std::endl; }

private:

    void Part1PositionUpdate(std::string& aRotCode);
    void Part2PositionUpdate(std::string& aRotCode);

    static const uint8_t sMaxPosition = 100;

    uint8_t mPosition;    // Dial position [0-sMaxPosition]
    uint64_t mZeroCounter; // Number of times dial has pointed at zero
};