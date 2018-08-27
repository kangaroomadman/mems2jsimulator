//--------------------------------------------------------------------------------------------------
/// @file HexValue.cpp
/// @brief Provides stream operator implementation for formatting a value as hexadecimal.
//--------------------------------------------------------------------------------------------------

// System includes
#include <iomanip>

// Project includes
#include "HexValue.h"

//--------------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& stream, const HexValue& hexValue)
{
    stream << "0x" << std::hex << std::uppercase << std::setw(hexValue.m_width)
           << std::setfill('0') << static_cast<std::uint32_t>(hexValue.m_value) << std::dec
           << std::nouppercase;
    return stream;
}