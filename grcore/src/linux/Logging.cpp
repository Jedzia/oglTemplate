/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the logging.cpp class.
 * \file       logging.cpp
 * \date       2020-03-16
 * \author     Jedzia.
 *
 * modified    2020-03-16, Jedzia
 */
/*---------------------------------------------------------*/

#if defined(__clang__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma clang diagnostic ignored "-Wsign-conversion"
#  pragma clang diagnostic ignored "-Wdouble-promotion"
#endif
#if defined(__GNUC__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma GCC diagnostic ignored "-Wsign-conversion"
#  pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif
#include <spdlog/spdlog.h>
#include <grcore/Logging.h>
#include <iostream>
#include <memory>
#include <spdlog/logger.h>
#include <spdlog/sinks/ansicolor_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <vector>

namespace grcore {
static std::string G_LOGGER_NAME = spdlog::default_logger()->name();

void info() {
    //Use the default logger (stdout, multi-threaded, colored)
    spdlog::info("grcore::info() -> Hello, {}!", "World from core::info()");
}

void logging::libSetDefaultLoggerLevel(spdlog::level::level_enum level) {
    spdlog::set_level(level);
}

std::shared_ptr<spdlog::logger> setupDefaultLoggerInternal(std::vector<spdlog::sink_ptr> sinks) {
    auto logger = spdlog::get(G_LOGGER_NAME);
    if(not logger) {
        if(sinks.size() > 0) {
            logger = std::make_shared<spdlog::logger>(G_LOGGER_NAME,
                    std::begin(sinks),
                    std::end(sinks));
            spdlog::register_logger(logger);
        } else {
            logger = spdlog::stdout_color_mt(G_LOGGER_NAME);
        }
    }

    return logger;
}

std::shared_ptr<spdlog::logger> setupLoggerInternal(const std::string &loggerName) {
    auto logger = spdlog::get(loggerName);
    if(not logger) {
        logger = spdlog::stdout_color_mt(loggerName);
    }

    return logger;
}

void colorizeLogger(std::shared_ptr<spdlog::logger> logger) {
    auto sink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
    sink->set_color_mode(spdlog::color_mode::always);
    logger->sinks().clear();
    logger->sinks().push_back(sink);
} // colorizeLogger

std::shared_ptr<spdlog::logger> logging::setUpDefaultLogger(const std::string &loggerName, spdlog::level::level_enum level) {
    auto logger = setupLoggerInternal(loggerName);
    setUpDefaultLogger(logger, level);
    return logger;
}

void logging::setUpDefaultLogger(std::shared_ptr<spdlog::logger> logger, spdlog::level::level_enum level) {
    // unite the application and library loggers.
    G_LOGGER_NAME = logger->name();
    colorizeLogger(logger);
    logger->set_level(level);
    spdlog::set_default_logger(logger);
    libSetDefaultLoggerLevel(level);
    logger->warn("You should see spdlog with color.");
}

std::shared_ptr<spdlog::logger> logging::setUpLogger(const std::string &loggerName, spdlog::level::level_enum level) {
    // ToDo: maybe set the named logger for the library, too here
    auto logger = setupLoggerInternal(loggerName);
    colorizeLogger(logger);
    logger->set_level(level);
    //libSetDefaultLoggerLevel(level);
    logger->warn("You should now see spdlog with color.");
    return logger;
}

void logging::test(std::string message) {
    auto logger = spdlog::get(G_LOGGER_NAME);
    //auto logger = spdlog::default_logger();
    if(logger) {
        logger->debug("{}::{}", __FUNCTION__, message);
    }
}

void bla() {
    int a = 0;
    a++;
    std::cout << "core::bla() Hello from the Speed IO Department, test ... test ;)" << a << std::endl;
    auto sink2 = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
    sink2->set_color_mode(spdlog::color_mode::always);
    auto console2 = std::make_shared<spdlog::logger>("console", sink2);
    console2->warn("Testing spdlog::sinks::ansicolor_stdout_sink_mt");
}// bla
}// namespace core
