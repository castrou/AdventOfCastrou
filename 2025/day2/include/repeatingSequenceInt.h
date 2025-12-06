#pragma once

#include <cstdint>
#include <string>

class RepeatingSequenceInt {
public:
    RepeatingSequenceInt(std::string aValue) : mValueSequence(aValue.substr(0, aValue.size() / 2)) {};
    ~RepeatingSequenceInt() {};

    // prefix increment
    RepeatingSequenceInt& operator++()
    {
        mValueSequence = std::to_string(std::stoll(mValueSequence) + 1);
        return *this;
    }
    // postfix increment
    RepeatingSequenceInt operator++(int)
    {
        RepeatingSequenceInt old = *this;
        operator++();
        return old;
    }
    // prefix decrement
    RepeatingSequenceInt& operator--()
    {
        mValueSequence = std::to_string(std::stoll(mValueSequence) - 1);
        return *this;
    }
    // postfix decrement
    RepeatingSequenceInt operator--(int)
    {
        RepeatingSequenceInt old = *this;
        operator--();
        return old;
    }

    std::string asString() { return mValueSequence + mValueSequence; }
    uint64_t value() { return std::stoll(asString()); }
    size_t size() { return mValueSequence.size(); }

private:
    std::string mValueSequence;
};