//--------------------------------------------------------------------------------------------------
/// @file HexValue.h
/// @brief Provides structure and stream operator declaration for formatting a value as hexadecimal.
//--------------------------------------------------------------------------------------------------
#pragma once

// System includes
#include <iostream>

//--------------------------------------------------------------------------------------------------
/// @brief Structure for holding and streaming a value in hexadecimal form
struct HexValue
{
    HexValue(const std::size_t value, const std::size_t width)
    : m_value(value),
      m_width(width)
    {
    }

    const std::size_t m_value;
    const std::size_t m_width;
};

//--------------------------------------------------------------------------------------------------
/// @brief Stream the HexValue structure out to a stream. Prefixes with 0x, pads to necessary width
///        with 0s and outputs value.
///
/// @param stream Stream to stream to.
/// @param byte Byte to stream out.
///
/// @return Stream
std::ostream& operator<<(std::ostream& stream, const HexValue& hexValue);
