//--------------------------------------------------------------------------------------------------
/// @file CommandHandler.h
/// @brief Provides the declaration of the CommandHandler class.
//--------------------------------------------------------------------------------------------------
#pragma once

// System includes
#include <vector>
#include <iostream>

// Project includes
#include "Serial.h"

//--------------------------------------------------------------------------------------------------
/// @brief Stream operator for a Command or Response. Prints each byte of the Command or Response to
///        the stream in hex format.
///
/// @param stream Stream to output to.
/// @param v Vector to stream.
///
/// @return Reference to stream.
std::ostream& operator<<(std::ostream& stream, const std::vector<std::uint8_t>& v);

//--------------------------------------------------------------------------------------------------
/// @brief Class for handling commands received from the diagnostic machine.
class CommandHandler
{
public:
    /// @brief Type definition for a command.
    typedef std::vector<std::uint8_t> Command;

    /// @brief Type defintion for a response.
    typedef std::vector<std::uint8_t> Response;

    /// @brief Type definition for a command response pair.
    typedef std::pair<Command, Response> CommandResponsePair;

    /// @brief Type definition for a vector of command and response pairs.
    typedef std::vector<CommandResponsePair> CommandResponses;

    //----------------------------------------------------------------------------------------------
    /// @brief Run the command handler.
    void Run();

private:
    //----------------------------------------------------------------------------------------------
    /// @brief Handle static commands.
    void HandleStaticCommands();

    //--------------------------------------------------------------------------------------------------
    /// @brief Determine if the input command matches an expected command. If a match is found, the
    ///        command bytes are removed from the input.
    ///
    /// @param exepcted Expected command to look for.
    ///
    /// @return True if found.
    bool InputCommandMatches(const Command& expected);

    /// @brief Interface to the serial port
    Serial m_serial;

    /// @brief Current input command
    Command m_inputCommand;
};
