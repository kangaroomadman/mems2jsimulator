//--------------------------------------------------------------------------------------------------
/// @file mems2jsimulator.cpp
/// @brief Provides main() entry point for the application.
//--------------------------------------------------------------------------------------------------

// Project includes
#include "Log.h"
#include "CommandHandler.h"

int main()
{
    LogOut() << "MEMS 2J Simulator" << std::endl;

    // Construct and start the command handler
    CommandHandler commandHandler;
    commandHandler.Run();

    return 0;
}
