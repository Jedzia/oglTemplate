/*---------------------------------------------------------*/
/*!
 * This file is part of GrCore, the efficient I/O library.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the test.cpp class.
 * \file       test.cpp
 * \date       2020-01-23
 * \author     Jedzia.
 *
 * modified    2020-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#include <grcore/grcore.h>
//
//#define SPDLOG_HEADER_ONLY
#include <iostream>
#include <memory>
#include <spdlog/sinks/ansicolor_sink.h>
#include <spdlog/sinks/wincolor_sink.h>
#include "grcore/warning/FMT_format_log.h"

#include "spdlog/sinks/rotating_file_sink.h"

namespace core {
/** Brief description of $(fclass), bla
 *  Detailed description.
 *
 */
void bla() {
    int a = 0;
    a++;
    std::cout << "core::bla() Hello from the Speed IO Department, test ... test ;)" << a << std::endl;

    //auto sink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
    //auto console = std::make_shared<spdlog::logger>("console", sink);
    //console->warn("Testing");
    //auto sink = spdlog::sinks::ansicolor_stdout_sink_st();
    //auto *sink = new spdlog::sinks::ansicolor_stdout_sink<spdlog::details::console_nullmutex>();

    //auto sink = new spdlog::sinks::ansicolor_stdout_sink_st(spdlog::color_mode::always);
    //static_cast<void>(sink);

    // create a thread safe sink which will keep its file size to a maximum of 5MB and a maximum of 3 rotated files.
    //auto file_logger = spdlog::rotating_logger_mt("file_logger", "logs/mylogfile", 1048576 * 5, 3);
    //file_logger->info("Fuck");

    //auto sink = new spdlog::sinks::wincolor_stderr_sink_st;
    auto sink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
    auto console = std::make_shared<spdlog::logger>("console", sink);
    console->warn("Testing spdlog::sinks::wincolor_stdout_sink_mt");

    //static_cast<void>(sink);


}
}
