//--------------------------------------------------------------------------------------------------
/// @file CommandHandler.cpp
/// @brief Provides the implementation of the CommandHandler class.
//--------------------------------------------------------------------------------------------------

// Project includes
#include "CommandHandler.h"
#include "CommandResponse.h"
#include "Log.h"
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

//----------------------------------------------------------------------------------------------
void CommandHandler::Run()
{
    // Run forever
    while (true)
    {
        std::uint8_t byte = 0U;
        if (m_serial.Read(byte))
        {
            m_inputCommand.push_back(byte);
            LogOut() << "Current input command: " << m_inputCommand << std::endl;

            HandleStaticCommands();
        }
    }
}

//----------------------------------------------------------------------------------------------
void CommandHandler::HandleStaticCommands()
{
    // Static commands and responses
    static const CommandResponses STATIC_COMMAND_RESPONSES =
    {
        // First initialisation command
        {
            {0x00, 0x81, 0x13, 0xF7, 0x81, 0x0C},
            {0x03, 0xC1, 0xD5, 0x8F, 0x28}
        },
        // Second initialisation command
        {
            {0x02, 0x10, 0xA0, 0xB2},
            {0x01, 0x50, 0x51}
        },
        // Third initialisation command
        {
            {0x02, 0x27, 0x01, 0x2A},
            {0x04, 0x67, 0x01, 0x96, 0xA4, 0xA6}
        },
        // Fourth initialisation command
        {
            {0x04, 0x27, 0x02, 0xD9, 0x34, 0x3A},
            {0x02, 0x67, 0x02, 0x6B}
        },
        // Heartbeat command
        {
            {0x02, 0x3E, 0x01, 0x41},
            {0x01, 0x7E, 0x7F}
        }
    };

    // Check input command against any static commands
    for (auto& commandResponse : STATIC_COMMAND_RESPONSES)
    {
        if (InputCommandMatches(commandResponse.first))
        {
            LogOut() << "Found match for command " << commandResponse.first << " responding with " << commandResponse.second << std::endl;

            // Send the response
            m_serial.Write(commandResponse.second);

            // Consume the response
            Response response(commandResponse.second.size());
            if (m_serial.Read(response))
            {
                LogOut() << "Received echoed response " << response << std::endl;
            }

            break;
        }
    }
}

//--------------------------------------------------------------------------------------------------
bool CommandHandler::InputCommandMatches(const Command& expected)
{
    // Can't match if input is not long enough
    if (m_inputCommand.size() < expected.size())
    {
        return false;
    }

    // Try and match all expected values
    bool matches = true;
    std::size_t position = 0U;
    for (auto& e : expected)
    {
        matches &= (m_inputCommand.at(position) == e);
        ++position;
    }

    // If a match has been found, pop from the front of the input
    if (matches)
    {
        m_inputCommand.erase(m_inputCommand.begin(), std::next(m_inputCommand.begin(), expected.size()));
    }

    return matches;
}