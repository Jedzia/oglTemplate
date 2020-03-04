/*---------------------------------------------------------*/
/*!
 * This file is part of GrCore, the efficient I/O library.
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
#include <chrono>
#include <fmt/format.h>
#include <fmt/printf.h>
#include <fstream>
#include <iostream>
#include <locale>
#include <grcore/grcore.h>

struct separate_thousands : std::numpunct<char>{
    /** Brief description of $(fclass), do_thousands_sep
     *  Detailed description.
     *  @return TODO
     */
    char_type do_thousands_sep() const override { return '.'; }  // separate with commas

    /** Brief description of $(fclass), do_grouping
     *  Detailed description.
     *  @return TODO
     */
    string_type do_grouping() const override { return "\3"; } // groups of 3 digit
};

/** Main application entry point.
 *  Program execution starts here.
 *  @return an exit code available for other programs.
 */
int main(int argc, char* * argv) {
    using namespace std;

    //fmt::print("Hello, {}!", "world");  // Python-like format string syntax
    fmt::printf("Hello, %s!\r\n", "world"); // printf format string syntax
    cout << fmt::format("Huhu, {}!", "world") << endl;

    cout << chrono::high_resolution_clock::period::den << endl;
    auto start_time = chrono::high_resolution_clock::now();
    long temp = 0;
    //for (unsigned long i = 0; i< 1420000000lu; i++)
    //    temp+=temp;

    //cout << "Hello, World!" << endl;
    spio::bla();

    ofstream my_file;
    //my_file.open("C:\\usr\\example.txt");
    my_file.open("example.txt");

    for(unsigned long i = 0; i < 1000000lu; i++) {
        my_file << "Writing this to a file. Without any reason! And a lot more of it, ha ha ha ha ha ....... Until this stops.\n";
    }
    my_file.close();

    auto end_time = chrono::high_resolution_clock::now();
    auto thousands = std::make_unique<separate_thousands>();
    std::cout.imbue(std::locale(std::cout.getloc(), thousands.release()));
    cout << chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() << " ns" << endl;
    cout << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() << " micro-s" << endl; // µs
    cout << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() << " ms" << endl;
    cout << chrono::duration_cast<chrono::seconds>(end_time - start_time).count() << " s" << endl;

    return 0;
} // main
