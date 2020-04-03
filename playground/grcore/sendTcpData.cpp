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

#include <chrono>
#include <grcore/Utility/TcpClient.h>
#include <iostream>
#include  <thread>

/** Program Entry Function, main
 *  The designated start of the program.
 *  @return program exit code.
 */
int main() { // the main code portion of a C++ program
    std::cout << "Hello cheesy World" << "\n";  //print Hello World on the screen
    //makeWindowAndTest(test_function);

    try {
        grcore::util::TcpClient tcpClient(true);
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2s);
        tcpClient.SendFile("graphics-vertex-array-tilemap-tileset.png");
    }
    catch(std::exception &ex) {
        std::cout << ex.what() << "\n";
        return EXIT_FAILURE;
    }

    return 0;
} // main
