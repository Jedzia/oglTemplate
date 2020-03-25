/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the main.cpp class.
 * \file       main.cpp
 * \date       2020-01-23
 * \author     Jedzia.
 *
 * modified    2020-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#include <iostream>
#include <string>
#include <tuple>
#include <variant>

std::tuple<std::string, int> GetTuple() {
    return {
               "hello", 5
    };
}

/** Program Entry Function, main
 *  The designated start of the program.
 *  @return program exit code.
 */
int main() {
    // print variant sizes
    std::cout << "\n" << "===== variant sizes =====\n";
    std::variant<int, char, float, double, std::string> variant_data;
    std::cout << "sizeof(int): " << sizeof(int) << "\n";
    std::cout << "sizeof(char): " << sizeof(char) << "\n";
    std::cout << "sizeof(float): " << sizeof(float) << "\n";
    std::cout << "sizeof(double): " << sizeof(double) << "\n";
    std::cout << "sizeof(std::string): " << sizeof(std::string) << "\n";
    std::cout << "sizeof(variant_data<all above>): " << sizeof(variant_data) << "\n";
    /*
        sizeof(int): 4
        sizeof(char): 1
        sizeof(float): 4
        sizeof(double): 8
        sizeof(std::string): 32
        sizeof(variant_data<all above>): 40

        so "Multiple TYPES of Data in a SINGLE VARIABLE in C++?, The Cherno" (
           https://www.youtube.com/watch?v=qCc_Vqg3hJk)
        is wrong.
     */

    // tuple and structured bindings
    std::cout << "\n\n" << "===== tuples =====\n";
    auto [name, age] = GetTuple();
    std::cout << "name: " << name << "\n";
    std::cout << "age: " << age << "\n";

    std::cout << "\n\n";
    std::cout << "we are done." << std::endl;
    return 0;
} // main
