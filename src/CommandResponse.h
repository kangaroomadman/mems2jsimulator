//--------------------------------------------------------------------------------------------------
/// @file CommandResponse.h
/// @brief Provides command and response types and associated function definitions.
//--------------------------------------------------------------------------------------------------
#pragma once

// System includes
#include <vector>
#include <utility>
#include <cstdint>

/// @brief Type definition for a command or response.
typedef std::vector<std::uint8_t> CommandOrResponse;

/// @brief Type definition for a command response pair.
typedef std::pair<CommandOrResponse, CommandOrResponse> CommandResponsePair;

/// @brief Type definition for a vector of command and response pairs.
typedef std::vector<CommandResponsePair> CommandResponses;
