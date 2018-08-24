//--------------------------------------------------------------------------------------------------
/// @file HexByte.h
/// @brief Provides structure and stream operator declaration for formatting a byte as hexadecimal.
//--------------------------------------------------------------------------------------------------
#pragma once

// System includes
#include <iostream>

//--------------------------------------------------------------------------------------------------
/// @brief Structure for holding and streaming a byte in hexadecimal form
struct HexByte
{
    std::uint8_t value;
};

//--------------------------------------------------------------------------------------------------
/// @brief Stream the HexByte structure out to a stream. Prefixes with 0x, pads to two wide with 0s
///        and outputs value.
///
/// @param stream Stream to stream to.
/// @param byte Byte to stream out.
///
/// @return Stream
std::ostream& operator<<(std::ostream& stream, const HexByte& hexByte);