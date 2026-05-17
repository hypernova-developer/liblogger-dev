#include "include/logger.hpp"

int main()
{
    Logger logger("app.log");

    logger.log(LogLevel::INFO, "liblogger-dev successfully initialized without namespace.");
    logger.log(LogLevel::WARNING, "Testing asynchronous queue processing speed.");
    logger.log(LogLevel::ERROR, "Simulated error log entry for TIG testing.");
    logger.log(LogLevel::CRITICAL, "Critical system check complete.");

    return 0;
}
