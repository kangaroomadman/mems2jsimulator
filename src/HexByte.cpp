//--------------------------------------------------------------------------------------------------
/// @file HexByte.cpp
/// @brief Provides stream operator implementation for formatting a byte as hexadecimal.
//--------------------------------------------------------------------------------------------------

// System includes
#include <iomanip>

// Project includes
#include "HexByte.h"

//--------------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& stream, const HexByte& hexByte)
{
    stream << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
           << static_cast<std::uint32_t>(hexByte.value) << std::dec << std::nouppercase;
    return stream;
}
