/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the logging.h class.
 * \file       logging.h
 * \date       2020-03-16
 * \author     Jedzia.
 *
 * modified    2020-03-26, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGLTEMPLATE_D9DE905FD50845E5B4199AA409BE0950_LOGGING_H
#define OPENGLTEMPLATE_D9DE905FD50845E5B4199AA409BE0950_LOGGING_H

#include "warning/FMT_format_log.h"
#include <iostream>
#include <memory>
#include <string>

namespace grcore {
namespace logging {
//#define NAMED_DEFAULT_LOGGER(name) spdlog::set_default_logger(grcore::logging::setUpLogger("\""
// #name "\""))
//#define NAMED_DEFAULT_LOGGER(name) spdlog::set_default_logger(grcore::logging::setUpLogger(#name))
#define NAMED_DEFAULT_LOGGER(name) spdlog::set_default_logger(grcore::logging::setUpLogger(name))
#define NAMED_DEFAULT_LOGGER_DEBUG(name) spdlog::set_default_logger(grcore::logging::setUpLogger(name, spdlog::level::debug))
#define NAMED_DEFAULT_LOGGER_LEVEL(name, level) spdlog::set_default_logger(grcore::logging::setUpLogger(name, level))

/** @brief Create and configure default logger
 *
 * To keep the setup of the default logger in application and library in sync.
 * @param loggerName Name of the logger.
 * @param level Minimal threshold level.
 * @return a shared pointer to a new instance of a logger that is used by the library, ready to be
 *         used by the application.
 * @example
 * @code
 * spdlog::set_default_logger(grcore::logging::setUpDefaultLogger("MyApplication",
 * spdlog::level::debug));
 * or
 * NAMED_DEFAULT_LOGGER("MyApplication");
 *
 * spdlog::info("+++ [{}]  called. +++", __PRETTY_FUNCTION__);
 * spdlog::warn("LogLevel: WARN");
 * spdlog::info("LogLevel: INFO");
 * spdlog::debug("LogLevel: DEBUG");
 * spdlog::trace("LogLevel: TRACE");
 * @endcode
 */
std::shared_ptr<spdlog::logger> setUpDefaultLogger(const std::string &loggerName, spdlog::level::level_enum level = spdlog::level::info);

/** @brief Configure default logger
 *
 * To keep the setup of the default logger in application and library in sync.
 * @param logger The logger used as the new default logger for the library.
 * @param level Minimal threshold level.
 * @example
 * @code
 * auto otherLogger = spdlog::stdout_color_mt("other");
 * setUpDefaultLogger(otherLogger, spdlog::level::info);
 * otherLogger->info("This is the 'other' logger.");
 * spdlog::warn("LogLevel: WARN"); // also 'other' logger, used as default logger.
 * @endcode
 */
void setUpDefaultLogger(std::shared_ptr<spdlog::logger> logger, spdlog::level::level_enum level = spdlog::level::info);

/** @brief Create and configure named logger [incomplete]
 *
 * To keep the setup of a named logger in application and library in sync.
 * ToDo: The sync of the library logger(named) part is not implemented.
 * @param loggerName Name of the logger.
 * @param level Minimal threshold level.
 * @return a shared pointer to a new instance of a logger that is used by the library, ready to be
 *         used by the application.
 * @example
 * @code
 * auto otherLogger = grcore::logging::setUpLogger("other");
 * otherLogger->info("This is the 'other' logger.");
 * @endcode
 */
std::shared_ptr<spdlog::logger> setUpLogger(const std::string &loggerName, spdlog::level::level_enum level = spdlog::level::info);

/** @brief Set the threshold level for the libraries default logger.
 *
 * @param level global logging level.
 */
void libSetDefaultLoggerLevel(spdlog::level::level_enum level);

/**
 * Try to send a message to (internal) 'LOGGER_NAME'.
 * @param message The log message content.
 */
void test(std::string message);
}

/** Log Hello World.
 *
 *  Logs a hello world message. For testing
 *  @code
 *  spdlog::info("grcore::info() -> Hello, {}!", "World from core::info()");
 *  @endcode
 */
void info();

/** For R&D, removed later.  */
void bla();

//using string_view_t = fmt::basic_string_view<char>;
/** For R&D, removed later.  */
using string_view_t = std::string;

/** For R&D, removed later.  */
template<typename ... Args>
void depp(/*source_loc loc, level::level_enum lvl,`*/ string_view_t fmt, const Args & ... /*args*/) {
    static_cast<void>(fmt);
    //static_cast<void>(args)...;
}

/** For R&D, removed later.  */
template<typename ... Args>
void log(/*source_loc loc, level::level_enum lvl,`*/ string_view_t fmt, const Args & ... args) {
    std::cout << "core::log::fmt: " << fmt << "\n";
    //bool log_enabled = should_log(lvl);
    //bool traceback_enabled = tracer_.enabled();
    /*if (!log_enabled && !traceback_enabled)
       {
        return;
       }*/
    //SPDLOG_TRY
    {
        //memory_buf_t buf;
        //fmt::format_to(buf, fmt, args...);
        //details::log_msg log_msg(loc, name_, lvl, string_view_t(buf.data(), buf.size()));
        //log_it_(log_msg, log_enabled, traceback_enabled);
    }
    //SPDLOG_LOGGER_CATCH()

    (std::cout << ... << args) << "<- core::log::args" << '\n';
}

/** For R&D, removed later.  */
template<typename ... Args>
inline void info(string_view_t fmt, const Args & ... args) {
    //default_logger_raw()->info(fmt, args...);
    log(fmt, args ...);
}
}
#endif //OPENGLTEMPLATE_D9DE905FD50845E5B4199AA409BE0950_LOGGING_H
