//--------------------------------------------------------------------------------------------------
/// @file CommandHandler.cpp
/// @brief Provides the implementation of the CommandHandler class.
//--------------------------------------------------------------------------------------------------

// Project includes
#include "CommandHandler.h"
#include "Log.h"
#include "HexValue.h"
#include "StringBuilder.h"

/// @brief Vector of dynamic commands.
static const std::vector<std::pair<std::uint8_t, std::uint8_t>> DYNAMIC_COMMANDS =
{
    {0x00, 20U}, // ???
    {0x01, 2U},  // ECT
    {0x03, 2U},  // IAT
    {0x06, 10U}, // ???
    {0x07, 2U},  // MAP Sensor
    {0x08, 2U},  // Throttle position
    {0x09, 2U},  // RPM
    {0x0A, 2U},  // O2 volts bank 1
    {0x0B, 2U},  // Coil 1 charge time (Is this also coil 2?)
    {0x0C, 2U},  // Injector 2 pulse width (Is this also injector 4?)
    {0x0F, 2U},  // Status (Throttle Switch = Bit 2)
    {0x10, 2U},  // Battery volts
    {0x11, 2U},  // Status (CAM = Bit 2, Crank Sync = Bit 3, Also ignition switch?? and air con req?)
    {0x12, 2U},  // Stepper position
    {0x13, 2U}   // E/Back bank 1
};

//--------------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& stream, const CommandOrResponse& v)
{
    for (auto itr = v.begin(); itr != v.end(); ++itr)
    {
        stream << HexValue(*itr, 2U);
        if (std::next(itr) != v.end())
        {
            stream << " ";
        }
    }
    return stream;
}

//----------------------------------------------------------------------------------------------
CommandHandler::CommandHandler(const std::map<std::uint8_t, std::uint16_t>& dynamicCommandResponses)
: m_dynamicCommandResponses(dynamicCommandResponses)
{
    // Verify that the dynamic command responses are in the list of dynamic commands
    for (auto& dynamicCommandResponse : dynamicCommandResponses)
    {
        bool found = false;
        for (auto& supportedCommand : DYNAMIC_COMMANDS)
        {
            if (dynamicCommandResponse.first == supportedCommand.first &&
                supportedCommand.second == 2U) // Only single status value commands supported
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            throw std::runtime_error(StringBuilder() << "Command " <<
                HexValue(dynamicCommandResponse.first, 2U) << " is not supported");
        }

        LogOut() << "Command index: " << HexValue(dynamicCommandResponse.first, 2U)
                 << ", Response: " << HexValue(dynamicCommandResponse.second, 4U) << std::endl;
    }

    // Connect the serial
    m_serial.Connect();
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

            // First try to handle the static commands during initialisation
            HandleStaticCommands();

            // If there are still bytes in the input command now try and handle dynamic commands
            // for reporting status values of sensors
            if (m_inputCommand.size() > 0U)
            {
                HandleDynamicCommands();
            }
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
            CommandOrResponse response(commandResponse.second.size());
            if (m_serial.Read(response))
            {
                LogOut() << "Received echoed response " << response << std::endl;
            }

            break;
        }
    }
}

//--------------------------------------------------------------------------------------------------
void CommandHandler::HandleDynamicCommands()
{
    for (auto& dynamicCommand : DYNAMIC_COMMANDS)
    {
        CommandOrResponse command = {0x02, 0x21, dynamicCommand.first};
        command.push_back(CalculateChecksum(command));
        if (InputCommandMatches(command))
        {
            // Respond to the command with the correct number of bytes
            CommandOrResponse response =
            {
                static_cast<std::uint8_t>(dynamicCommand.second + 1U), 0x61, dynamicCommand.first
            };

            // If a response has been defined use it, otherwise use zeros.
            const auto& dynamicCommandResponse = m_dynamicCommandResponses.find(dynamicCommand.first);
            if (dynamicCommandResponse != m_dynamicCommandResponses.end())
            {
                response.push_back((dynamicCommandResponse->second >> 1U) & 0xFF);
                response.push_back(dynamicCommandResponse->second & 0xFF);
            }
            else
            {
                for (std::size_t i = 0U; i < dynamicCommand.second; ++i)
                {
                    response.push_back(0x00);
                }
            }
            response.push_back(CalculateChecksum(response));

            // Send the response
            m_serial.Write(response);

            // Consume the response
            CommandOrResponse echoedResponse(response.size());
            if (m_serial.Read(echoedResponse))
            {
                LogOut() << "Received echoed response " << echoedResponse << std::endl;
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------
bool CommandHandler::InputCommandMatches(const CommandOrResponse& expected)
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

//--------------------------------------------------------------------------------------------------
std::uint8_t CommandHandler::CalculateChecksum(const CommandOrResponse& commandOrResponse)
{
    std::uint8_t checksum = 0U;
    for (auto& byte : commandOrResponse)
    {
        checksum += byte;
    }
    return checksum;
}