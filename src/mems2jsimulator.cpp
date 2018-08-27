//--------------------------------------------------------------------------------------------------
/// @file mems2jsimulator.cpp
/// @brief Provides main() entry point for the application.
//--------------------------------------------------------------------------------------------------

// Project includes
#include "Log.h"
#include "CommandLineParser.h"
#include "CommandHandler.h"

//--------------------------------------------------------------------------------------------------
/// @brief Application entry point.
///
/// @param[in] argc Number of arguments provided on the command line.
/// @param[in] argv Array of arguments provided on the command line.
///
/// @return Application exit code.
int main(const int argc, const char* argv[])
{
    LogOut() << "MEMS 2J Simulator" << std::endl;

    // Parse the command line options
    CommandLineParser parser(argc, argv);

    // Construct and start the command handler
    CommandHandler commandHandler(parser.GetCommandResponses());
    commandHandler.Run();

    return 0;
}
