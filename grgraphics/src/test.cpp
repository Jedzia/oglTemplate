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
#include <grgraphics/GrGraphics.h>
//
#include <iostream>
//
#if defined(__clang__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma clang diagnostic ignored "-Wsign-conversion"
#  pragma clang diagnostic ignored "-Wdouble-promotion"
#endif
#if defined(__GNUC__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma GCC diagnostic ignored "-Wsign-conversion"
#  pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif

#include <spdlog/spdlog.h>

/** Brief description of $(fclass), bla
 *  Detailed description.
 *
 */
void grg::bla() {
    int a = 0;
    a++;
    std::cout << "grg::bla() Hello from the Speed IO Department, test ... test ;)" << a << std::endl;

    spdlog::info("grg::bla(), spdlog -> Hello, {}!", "World");

}
