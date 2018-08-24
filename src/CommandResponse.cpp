//--------------------------------------------------------------------------------------------------
/// @file CommandResponse.cpp
/// @brief Provides command and response types associated function implementations.
//--------------------------------------------------------------------------------------------------

// System includes
#include <iomanip>

// Project includes
#include "CommandResponse.h"
#include "HexByte.h"

//--------------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& stream, const std::vector<std::uint8_t>& v)
{
    for (auto itr = v.begin(); itr != v.end(); ++itr)
    {
        stream << HexByte{*itr};
        if (std::next(itr) != v.end())
        {
            stream << " ";
        }
    }
    return stream;
}

//--------------------------------------------------------------------------------------------------
bool InputCommandMatches(Command& input, const Command& expected)
{
    // Can't match if input is not long enough
    if (input.size() < expected.size())
    {
        return false;
    }

    // Try and match all expected values
    bool matches = true;
    std::size_t position = 0U;
    for (auto& e : expected)
    {
        matches &= (input.at(position) == e);
        ++position;
    }

    // If a match has been found, pop from the front of the input
    if (matches)
    {
        input.erase(input.begin(), std::next(input.begin(), expected.size()));
    }

    return matches;
}
