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
//#include <grcore/grcore.h>
//
//#define SPDLOG_HEADER_ONLY
#include "grcore/warning/FMT_format_log.h"
#include <iostream>
#include <memory>

namespace core {
/** Brief description of $(fclass), bla
 *  Detailed description.
 *
 */
void blubb() {
    int a = 0;
    a++;
    std::cout << "core::bla() Hello from the Speed IO Department, test ... test ;)" << a << std::endl;

    //static_cast<void>(sink);
}
}
