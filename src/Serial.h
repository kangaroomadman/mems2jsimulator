//--------------------------------------------------------------------------------------------------
/// @file Serial.h
/// @brief Provides definition of the Serial class.
//--------------------------------------------------------------------------------------------------
#pragma once

// Project includes
#include "CommandResponse.h"

//--------------------------------------------------------------------------------------------------
/// @brief Class for interfacing to a Serial device using FTDI.
class Serial
{
public:
    //----------------------------------------------------------------------------------------------
    /// @brief Constructor. Initialises FTDI.
    Serial();

    //----------------------------------------------------------------------------------------------
    /// @brief Destructor. Closes FTDI device.
    ~Serial();

    //----------------------------------------------------------------------------------------------
    /// @brief Read a single byte from the serial device.
    ///
    /// @param[out] byte Read byte
    ///
    /// @return True if read was successful
    bool Read(std::uint8_t& byte);

    //----------------------------------------------------------------------------------------------
    /// @brief Read a response from the serial device. The Responce must be sized for the desired
    ///        read size.
    ///
    /// @param[in,out] response Read response
    ///
    /// @return True if read was successful
    bool Read(Response& response);

    //----------------------------------------------------------------------------------------------
    /// @brief Write a response to the serial device.
    ///
    /// @param[in] response Response to write
    ///
    /// @return True if write was successful
    bool Write(const Response& response);

private:
    /// @brief Handle for the FTDI device
    void* m_ftHandle;
};
