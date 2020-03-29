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

#ifndef OPENGLTEMPLATE_LOGGING_H
#define OPENGLTEMPLATE_LOGGING_H

#include "warning/FMT_format_log.h"
#include <iostream>
#include <memory>
#include <string>

namespace grcore {
namespace logging {
//#define NAMED_DEFAULT_LOGGER(name) spdlog::set_default_logger(core::logging::setUpLogger("\"" #name "\""))
//#define NAMED_DEFAULT_LOGGER(name) spdlog::set_default_logger(core::logging::setUpLogger(#name))
#define NAMED_DEFAULT_LOGGER(name) spdlog::set_default_logger(core::logging::setUpLogger(name))

std::shared_ptr<spdlog::logger> setUpLogger(const std::string &loggerName, spdlog::level::level_enum level = spdlog::level::info);

void setUpDefaultLogger(std::shared_ptr<spdlog::logger> logger, spdlog::level::level_enum level = spdlog::level::info);

void set_level(spdlog::level::level_enum level);

void test(std::string message);
}
void info();

void bla();

//using string_view_t = fmt::basic_string_view<char>;
using string_view_t = std::string;

template<typename ... Args>
void depp(/*source_loc loc, level::level_enum lvl,`*/ string_view_t fmt, const Args & ... /*args*/) {
    static_cast<void>(fmt);
    //static_cast<void>(args)...;
}

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

template<typename ... Args>
inline void info(string_view_t fmt, const Args & ... args) {
    //default_logger_raw()->info(fmt, args...);
    log(fmt, args ...);
}
}
#endif //OPENGLTEMPLATE_LOGGING_H
