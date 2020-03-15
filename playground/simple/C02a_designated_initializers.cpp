/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the C02a_designated_initializers.cpp class.
 * \file       C02a_designated_initializers.cpp
 * \date       2020-01-23
 * \author     Jedzia.
 *
 * modified    2020-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#include <iostream> // include API
#include <thread>

using namespace std;

struct A {
    int x;
    int y;
    int z;
};

/** Brief description of $(fclass), operator <<
 *  Detailed description.
 *  @param o TODO
 *  @param p TODO
 *  @return TODO
 */
std::ostream& operator << (std::ostream &o, const A &p){
    return o << "x: " << p.x << "\ty: " << p.y << "\tz: " << p.z;
}

void do_nothing() {

}

/** Brief description of $(fclass), main
 *  Detailed description.
 *  @return TODO
 */
int main(){ // the main code portion of a C++ program
#if __clang__
    A a { .y = 2, .x = 1 }; // error; designator order does not match declaration order
    A b { .x = 1, .z = 2 }; // ok, b.y initialized to 0

    cout << "a: " << a << "\n";
    cout << "b: " << b << "\n";

    thread t{do_nothing};
    t.join();

    cout << endl;
#endif
    return 0; // conventional
}
