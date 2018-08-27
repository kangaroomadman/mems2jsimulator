//--------------------------------------------------------------------------------------------------
/// @file CommandLineParser.h
/// @brief Provides declaration of the CommandLineParser class.
//--------------------------------------------------------------------------------------------------
#pragma once

// System includes
#include <cstdint>
#include <map>

//--------------------------------------------------------------------------------------------------
/// @brief Class for parsing options provided on the command line.
class CommandLineParser
{
public:
    //----------------------------------------------------------------------------------------------
    /// @brief Constructor - parse the arguments.
    ///
    /// @param[in] argc Number of arguments.
    /// @param[in] argv Array of arguments.
    CommandLineParser(const int argc, const char* argv[]);

    //----------------------------------------------------------------------------------------------
    /// @brief Get the map of command responses.
    ///
    /// @return std::map of commands and response values.
    std::map<std::uint8_t, std::uint16_t> GetCommandResponses() const;

private:
    /// @brief Map of command and response values.
    std::map<std::uint8_t, std::uint16_t> m_commandResponses;
};
