//--------------------------------------------------------------------------------------------------
/// @file Log.h
/// @brief Provides logging function declarations.
//--------------------------------------------------------------------------------------------------
#pragma once

// System includes
#include <iostream>

//--------------------------------------------------------------------------------------------------
/// @brief Start a new log message using provided stream by streaming out the current time stamp.
///
/// @param[in] stream Stream to log to.
///
/// @return Reference to stream.
std::ostream& Log(std::ostream& stream);

//--------------------------------------------------------------------------------------------------
/// @brief Start a new log message to STDOUT.
///
/// @return Reference to std::cout.
std::ostream& LogOut();

//--------------------------------------------------------------------------------------------------
/// @brief Start a new log message to STDERR.
///
/// @return Reference to std::cerr.
std::ostream& LogError();
