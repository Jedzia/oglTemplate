/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the main.cpp class.
 * \file       main.cpp
 * \date       2020-01-25
 * \author     Jedzia.
 *
 * modified    2020-01-25, Jedzia
 */
/*---------------------------------------------------------*/
#include <iostream>
#include <memory>
#include <vector>

class Dummy {
public:

    Dummy() {
        std::cout << "+++ Constructor Dummy() called. +++" << std::endl;
    }

    virtual ~Dummy() {
        std::cout << "--- Destructor  Dummy() called. ---" << std::endl;
    }

private:
};

/** Program Entry Function, main
 *  The designated start of the program.
 *  @return program exit code.
 */
int main() {
    std::cout << "> Hello cheesy World" << std::endl;

    // *** Automatic destruction via std::vector ***
    {
        std::vector<std::unique_ptr<Dummy>> pointers;
        pointers.push_back(std::make_unique<Dummy>());
        pointers.push_back(std::make_unique<Dummy>());
        {
            pointers.push_back(std::make_unique<Dummy>());
            std::cout << "> Going out of Sub-Scope" << std::endl;
        }
        std::cout << "> out of Sub-Scope" << std::endl;

        std::cout << "> Going out of Scope" << std::endl;
    }
    std::cout << "> Out of Scope" << std::endl;

    return 0;
} // main
