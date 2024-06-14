#include <catch2/catch_test_macros.hpp>
#include "Logger.hpp"

TEST_CASE("Logger test") {
    GlobalLogger* logger = GlobalLogger::getInstance();
    logger->init("config.yml");
    logger->log("Info", "This is an info message");
    logger->log("Fatal", "This is a fatal message");
    logger->log("Error", "This is an error message");
    // Assert on the log file contents.
}
