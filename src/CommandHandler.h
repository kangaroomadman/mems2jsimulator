//--------------------------------------------------------------------------------------------------
/// @file CommandHandler.h
/// @brief Provides the declaration of the CommandHandler class.
//--------------------------------------------------------------------------------------------------
#pragma once

// System includes
#include <map>
#include <vector>
#include <iostream>

// Project includes
#include "Serial.h"
#include "CommandResponse.h"

//--------------------------------------------------------------------------------------------------
/// @brief Stream operator for a Command or Response. Prints each byte of the Command or Response to
///        the stream in hex format.
///
/// @param stream Stream to output to.
/// @param v Vector to stream.
///
/// @return Reference to stream.
std::ostream& operator<<(std::ostream& stream, const CommandOrResponse& v);

//--------------------------------------------------------------------------------------------------
/// @brief Class for handling commands received from the diagnostic machine.
class CommandHandler
{
public:
    //----------------------------------------------------------------------------------------------
    /// @brief Constructor.
    ///
    /// @param[in] dynamicCommandResponses A map of dynamic command responses for the simulator to
    ///                                    use
    CommandHandler(const std::map<std::uint8_t, std::uint16_t>& dynamicCommandResponses);

    //----------------------------------------------------------------------------------------------
    /// @brief Run the command handler.
    void Run();

private:
    //----------------------------------------------------------------------------------------------
    /// @brief Handle static commands.
    void HandleStaticCommands();

    //----------------------------------------------------------------------------------------------
    /// @brief Handle dynamic commands.
    void HandleDynamicCommands();

    //----------------------------------------------------------------------------------------------
    /// @brief Determine if the input command matches an expected command. If a match is found, the
    ///        command bytes are removed from the input.
    ///
    /// @param exepcted Expected command to look for.
    ///
    /// @return True if found.
    bool InputCommandMatches(const CommandOrResponse& expected);

    //----------------------------------------------------------------------------------------------
    /// @brief Calculate a checksum.
    ///
    /// @param[in] commandOrResponse The input command or response to calculate checksum for.
    ///
    /// @return Calculated checksum.
    std::uint8_t CalculateChecksum(const CommandOrResponse& commandOrResponse);

    /// @brief Map of dynamic command responses.
    const std::map<std::uint8_t, std::uint16_t> m_dynamicCommandResponses;

    /// @brief Interface to the serial port
    Serial m_serial;

    /// @brief Current input command
    CommandOrResponse m_inputCommand;
};
