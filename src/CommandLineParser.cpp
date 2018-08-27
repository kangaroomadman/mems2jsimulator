//--------------------------------------------------------------------------------------------------
/// @file CommandLineParser.cpp
/// @brief Provides implementation of the CommandLineParser class.
//--------------------------------------------------------------------------------------------------

// System includes
#include <string>

// Project includes
#include "CommandLineParser.h"
#include "StringBuilder.h"
#include "HexValue.h"

//--------------------------------------------------------------------------------------------------
CommandLineParser::CommandLineParser(const int argc, const char* argv[])
{
    // We expect any arguments to come in pairs of a command index and a reponse value, so there
    // should always be an even number of arguments.
    if (argc % 2U == 0U)
    {
        throw std::runtime_error(StringBuilder() << "Unexpected number of arguments found: " << argc);
    }

    // Process the command line options
    for (std::size_t i = 1U; i < static_cast<std::size_t>(argc); i += 2U)
    {
        const std::uint8_t commandIndex = std::stoul(argv[i], nullptr, 16);
        const std::uint16_t commandResponse = std::stoul(argv[i + 1U], nullptr, 16);

        // Check we're not overwriting
        if (m_commandResponses.find(commandIndex) != m_commandResponses.end())
        {
            throw std::runtime_error(StringBuilder() << "Command index " << HexValue(commandIndex, 2U) << " already has a response defined");
        }
        m_commandResponses[commandIndex] = commandResponse;
    }
}

//--------------------------------------------------------------------------------------------------
std::map<std::uint8_t, std::uint16_t> CommandLineParser::GetCommandResponses() const
{
    return m_commandResponses;
}
