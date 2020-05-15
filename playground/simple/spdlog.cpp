/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the spdlog.cpp class.
 * \file       spdlog.cpp
 * \date       2020-05-15
 * \author     Jedzia.
 *
 * modified    2020-05-15, Jedzia
 */
/*---------------------------------------------------------*/
#include <iostream>
#include <spdlog/spdlog.h>

/** Program Entry Function, main
 *  The designated start of the program.
 *  @return program exit code.
 */
int main() {
    // print Hello World on the screen
    std::cout << "Hello cheesy World" << std::endl;
    spdlog::info("Hello, {}!", "World");
    return 0; // program exit code
}
