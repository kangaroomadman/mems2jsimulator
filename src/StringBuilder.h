//--------------------------------------------------------------------------------------------------
/// @file StringBuilder.h
/// @brief Provides class for wrapping string stream building and returning a string.
//--------------------------------------------------------------------------------------------------
#pragma once

// System includes
#include <sstream>

//--------------------------------------------------------------------------------------------------
/// @brief Class for building strings using stream operators.
class StringBuilder
{
public:
    //----------------------------------------------------------------------------------------------
    /// @brief Stream operator for building the string.
    ///
    /// @param[in] arg Argument to append to the string.
    ///
    /// @return Reference to self.
    template<typename T>
    StringBuilder& operator<<(const T& arg)
    {
        m_stream << arg;
        return *this;
    }

    //----------------------------------------------------------------------------------------------
    /// @brief Conversion operator to std:string.
    ///
    /// @return std::string of build string.
    operator std::string() const
    {
        return m_stream.str();
    }

private:
    /// @brief Internal string stream for build string
    std::ostringstream m_stream;
};
