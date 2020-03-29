/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the console.cpp class.
 * \file       console.cpp
 * \date       2020-03-26
 * \author     Jedzia.
 *
 * modified    2020-03-26, Jedzia
 */
/*---------------------------------------------------------*/
#include "../console.h"
#include <codecvt>
#include <io.h>
#include <iostream>
#include <locale>

grcore::ConsoleCheckResult grcore::checkConsole() {
    //std::wcout << "User-preferred locale setting is " << std::locale("").name().c_str() << '\n';

    auto consoleResult = ConsoleCheckResult::None;
    int decide = 0;
    try {
        std::cout << "std::locale(\"\").name(): " << std::locale("").name() << std::endl;
        decide--;
    }
    catch(std::runtime_error &e) {
        // fires on MSYS
        std::cout << "std::locale(\"\").name(), std::runtime_error: " << e.what() << std::endl;
        decide++;
        //return MSys;
    }

    if(isatty(STDOUT_FILENO)) {
        /* this is a terminal */
        std::cout << "isatty !" << std::endl;
        decide--;
    } else {
        // fires on MSYS
        decide++;
        std::cout << "NO isatty !" << std::endl;
    }

    std::cout << "core::checkConsole(), decide: " << decide << std::endl;
    if(decide < 0) {
        consoleResult = Windows;
    } else if(decide > 0) {
        consoleResult = MSys;
    }

/*    std::locale l1;  // l1 is a copy of the classic "C" locale
    std::cout << "Locale names:\nl1: " << l1.name() << std::endl;
    std::locale l2("en_US.UTF-8"); // l2 is a unicode locale
    std::cout << "Locale names:\nl2: " << l2.name() << std::endl;
    std::locale l3(l1, l2, std::locale::ctype); // l3 is "C" except for ctype, which is unicode
    std::cout << "Locale names:\nl3: " << l3.name() << std::endl;
    std::locale l4(l1, new std::codecvt_utf8<wchar_t>); // l4 is "C" except for codecvt
    std::cout << "Locale names:\nl4: " << l4.name() << std::endl;*/
    /*std::cout << "Locale names:\nl1: " << l1.name() << "\nl2: " << l2.name()
              << "\nl3: " << l3.name() << "\nl4: " << l4.name() << '\n';*/
    return consoleResult;
} // core::checkConsole
