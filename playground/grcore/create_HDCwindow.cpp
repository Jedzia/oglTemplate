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

#include <iostream>
#include <grcore/wgl_common.h>
#include <fmt/printf.h>
//
#include <winuser.h>

using namespace std;

static int
test_function(HDC hdc)
{
    fmt::printf("HDC: '%p'\r\n", hdc); // printf format string syntax
    //MessageBoxA(0,(char*)glGetString(GL_VERSION), "OPENGL VERSION",0);
    MessageBoxA(0,"Dreck !", "OPENGL VERSION",0);
    return true;
}

/** Brief description of $(fclass), main
 *  Detailed description.
 *  @return TODO
 */
int main(){ // the main code portion of a C++ program
    cout << "Hello cheesy World" << endl;  //print Hello World on the screen
    makeWindowAndTest(test_function);
    /* UNREACHED */
    return 0;
}
