/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the create_window.cpp class.
 * \file       create_window.cpp
 * \date       2020-01-23
 * \author     Jedzia.
 *
 * modified    2020-01-23, Jedzia
 */
/*---------------------------------------------------------*/

//#include <fmt/format.h>
#include <grcore/warning/FMT_format.h>
#include <grcore/Resource.h>
#include <iostream>
//

using namespace std;

/** Code called during window event loop
 *  @param hdc window device context
 *  @return forwarded to program exit code
 */
/*static int test_function(HDC hdc) {
    fmt::printf("HDC: '%p'\r\n", hdc); // printf format string syntax
    //MessageBoxA(0,(char*)glGetString(GL_VERSION), "OPENGL VERSION",0);
    return true;
}*/

/** Program Entry Function, main
 *  The designated start of the program.
 *  @return program exit code.
 */
int main(){ // the main code portion of a C++ program
    cout << "Hello cheesy World" << endl;  //print Hello World on the screen

    const int fontId = 129;
    grcore::Resource res(fontId);
    auto [data, size, error] = res.Get();

    std::cout << fmt::format("[{}] Loaded Font from resource (id={}): '{}'.", __PRETTY_FUNCTION__, fontId, data);
    std::cout << "data:" << data << std::endl;
    std::cout << "size:" << size << std::endl;
    std::cout << "error:" << error << std::endl;

    return EXIT_SUCCESS;
}
