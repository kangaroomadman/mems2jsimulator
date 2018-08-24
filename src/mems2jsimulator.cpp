//--------------------------------------------------------------------------------------------------
/// @file mems2jsimulator.cpp
/// @brief Provides main() entry point for the application.
//--------------------------------------------------------------------------------------------------

// Project includes
#include "Log.h"
#include "HexByte.h"
#include "CommandResponse.h"
#include "Serial.h"

int main()
{
    LogOut() << "MEMS 2J Simulator" << std::endl;

    // Construct the serial port
    Serial serial;

    // Read bytes from the port
    Command inputCommand;
    while (true)
    {
        // Read a single byte at a time
        std::uint8_t byte = 0U;
        if (serial.Read(byte))
        {
            LogOut() << "Read byte: " << HexByte{byte} << std::endl;
            inputCommand.push_back(byte);

            // Process the current input command
            if (inputCommand.size())
            {
                // Commands and responses
                static const CommandResponses COMMAND_RESPONSES =
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

                LogOut() << "Current input command: " << inputCommand << std::endl;

                // Process received commands and respond
                for (auto& commandResponse : COMMAND_RESPONSES)
                {
                    if (InputCommandMatches(inputCommand, commandResponse.first))
                    {
                        LogOut() << "Found match for command " << commandResponse.first << " responding with " << commandResponse.second << std::endl;

                        // Send the response
                        serial.Write(commandResponse.second);

                        // Consume the response
                        Response response(commandResponse.second.size());
                        if (serial.Read(response))
                        {
                            LogOut() << "Received echoed response " << response << std::endl;
                        }
                    }
                }
            }
        }
    }

    return 0;
}
