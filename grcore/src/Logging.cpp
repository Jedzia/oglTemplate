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
#include <grcore/Logging.h>
//#if USE_SPDLOG
#include <spdlog/spdlog.h>
//#endif
#include <fmt/core.h>

//using string_view_t = fmt::basic_string_view<char>;

/** Brief description of core, info
 *  Detailed description.
 *  @return TODO
 */
void core::info() {
    //Use the default logger (stdout, multi-threaded, colored)
//#if USE_SPDLOG
    spdlog::info("core::info() -> Hello, {}!", "World from core::info()");
//#endif
}

void core::logging::setLevel(int level) {
    spdlog::set_level(static_cast<spdlog::level::level_enum>(level));
}
