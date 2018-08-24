//--------------------------------------------------------------------------------------------------
/// @file Log.cpp
/// @brief Provides logging functions implementations.
//--------------------------------------------------------------------------------------------------

// System includes
#include <ctime>
#include <iomanip>

// Project includes
#include "Log.h"

//--------------------------------------------------------------------------------------------------
std::ostream& Log(std::ostream& stream)
{
    const std::time_t t = std::time(NULL);
    return (stream << "[" << std::put_time(std::localtime(&t), "%c") << "]: ");
}

//--------------------------------------------------------------------------------------------------
std::ostream& LogOut()
{
    return Log(std::cout);
}

//--------------------------------------------------------------------------------------------------
std::ostream& LogError()
{
    return Log(std::cerr);
}
