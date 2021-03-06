//--------------------------------------------------------------------------------------------------
/// @file Serial.cpp
/// @brief Provides implementation of the Serial class.
//--------------------------------------------------------------------------------------------------

// System includes
#include <ftd2xx.h>
#include <string>
#include <stdexcept>

// Project includes
#include "Serial.h"
#include "StringBuilder.h"

//--------------------------------------------------------------------------------------------------
/// @brief Variadic template function for wrapping an FTDI method with status checking.
///
/// @tparam Function Type of FTDI function to call
/// @tparam Args Type of arguments to pass to FTDI function
///
/// @param[in] name Name of function (Used for exception)
/// @param[in] f FTDI function to call
/// @param[in] args Arguments to pass to FTDI function
template<typename Function, typename... Args>
void FtFuncWrapper(const std::string name, Function&& f, Args... args)
{
    const FT_STATUS status = f(args...);
    if (status != FT_OK)
    {
        throw std::runtime_error(StringBuilder() << name << "(): Invalid FT status: " << status);
    }
}

//--------------------------------------------------------------------------------------------------
Serial::Serial()
: m_ftHandle(nullptr)
{
}

//--------------------------------------------------------------------------------------------------
Serial::~Serial()
{
    if (m_ftHandle)
    {
        FT_Close(m_ftHandle);
    }
}

//----------------------------------------------------------------------------------------------
void Serial::Connect()
{
    FtFuncWrapper("FT_Open", FT_Open, 0, &m_ftHandle);
    FtFuncWrapper("FT_SetDataCharacteristics", FT_SetDataCharacteristics, m_ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
    FtFuncWrapper("FT_SetBaudRate", FT_SetBaudRate, m_ftHandle, 10400);
    FtFuncWrapper("FT_SetTimeouts", FT_SetTimeouts, m_ftHandle, 100, 100);
    FtFuncWrapper("FT_SetFlowControl", FT_SetFlowControl, m_ftHandle, FT_FLOW_NONE, 0, 0);
}

//--------------------------------------------------------------------------------------------------
bool Serial::Read(std::uint8_t& byte)
{
    unsigned long bytesRead = 0U;
    FtFuncWrapper("FT_Read", FT_Read, m_ftHandle, reinterpret_cast<void *>(&byte), 1, &bytesRead);
    return (bytesRead == 1U);
}

//--------------------------------------------------------------------------------------------------
bool Serial::Read(CommandOrResponse& response)
{
    unsigned long bytesRead = 0U;
    FtFuncWrapper("FT_Read", FT_Read, m_ftHandle, reinterpret_cast<void *>(response.data()), response.size(), &bytesRead);
    return (bytesRead == response.size());
}

//--------------------------------------------------------------------------------------------------
bool Serial::Write(const CommandOrResponse& response)
{
    unsigned long bytesWritten = 0U;
    // Grab local copy for FTDI to use
    CommandOrResponse localResponse = response;
    FtFuncWrapper("FT_Write", FT_Write, m_ftHandle, reinterpret_cast<void *>(localResponse.data()), response.size(), &bytesWritten);
    return (bytesWritten == response.size());
}
