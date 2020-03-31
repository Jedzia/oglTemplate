/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the coroutine1.cpp class.
 * \file       coroutine1.cpp
 * \date       2020-03-31
 * \author     Jedzia.
 *
 * modified    2020-03-31, Jedzia
 */
/*---------------------------------------------------------*/
//#include <iostream>
//#include <experimental/coroutine>
//#include <boost/coroutine2/all.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <experimental/coroutine>
#include <future>
#include <chrono>
//(1/2) installing mingw-w64-x86_64-libc++abi                                                                  [###############################################################] 100%
//(2/2) installing mingw-w64-x86_64-libc++                                                                     [###############################################################] 100%

using namespace std;

class Resumable {
public:
    struct promise_type;
    using coro_handle = std::experimental::coroutine_handle<promise_type>;

    Resumable(coro_handle handle) : handle_(handle) { assert(handle); }

    Resumable(Resumable &) = delete;

    Resumable(Resumable &&) = delete;

    bool resume() {
        if(not handle_.done())
            handle_.resume();
        return not handle_.done();
    }

    ~Resumable() { handle_.destroy(); }

private:
    coro_handle handle_;
    std::string m_test = "Hello coroutines";
};

struct Resumable::promise_type {
    using coro_handle = std::experimental::coroutine_handle<promise_type>;

    auto get_return_object() {
        return coro_handle::from_promise(*this);
    }

    auto initial_suspend() { return std::experimental::suspend_always(); }

    auto final_suspend() { return std::experimental::suspend_always(); }

    void return_void() {}

    void unhandled_exception() {
        std::terminate();
    }

    //auto yield_value(const int& dreck) {
    auto yield_value(const std::string &value) {
        std::cout << "yield_value: '" << value << "'\n";
        return *this;
    }

    bool await_ready() {
        std::cout << "await_ready" << "'\n";
        return true;
    }

    void await_suspend(const std::experimental::coroutines_v1::coroutine_handle<Resumable::promise_type> &dreck) {
        std::cout << "await_suspend" << "'\n";
        //return true;
    }

    void await_resume() {
        std::cout << "await_resume" << "'\n";
        //return true;
    }

};



// Not there yet
/*void foo(){
    //std::cout << "Hello" << std::endl;
    co_await std::experimental::suspend_always();
    //std::cout << "World" << std::endl;
   }*/

/*lazy<int> f() {
    co_return 7;
}*/

Resumable foo() {
    while(true) {
        co_yield
        "Hello";
        co_yield
        "Coroutine";
        //co_yield 5;
        //co_yield 6;
    }
}

/** Program Entry Function, main
 *  The designated start of the program.
 *  @return program exit code.
 */
int main() {
    // print Hello World on the screen
    //
    std::cout << "Hello cheesy World" << std::endl;
    Resumable res = foo();
    while(res.resume());
    // needs linkage
    /*boost::coroutines2::coroutine<int>::pull_type source(
            [](boost::coroutines2::coroutine<int>::push_type &sink) {
        int first = 1, second = 1;
        sink(first);
        sink(second);

        for(int i = 0; i < 8; ++i) {
            int third = first + second;
            first = second;
            second = third;
            sink(third);
        }
    });

    for(auto i : source) {
        std::cout << i << " ";
    }
    std::cout << "\nDone" << std::endl;*/
    return EXIT_SUCCESS;
} // main
