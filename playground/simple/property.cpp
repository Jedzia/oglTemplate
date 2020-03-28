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
#include <functional>
//#include "../../grcore/include/grcore/Utility/Property.h"

template <typename F>
struct return_type_impl;

template <typename R, typename... Args>
struct return_type_impl<R(Args...)> { using type = R; };

template <typename R, typename... Args>
struct return_type_impl<R(Args..., ...)> { using type = R; };

template <typename R, typename... Args>
struct return_type_impl<R(*)(Args...)> { using type = R; };

template <typename R, typename... Args>
struct return_type_impl<R(*)(Args..., ...)> { using type = R; };

template <typename R, typename... Args>
struct return_type_impl<R(&)(Args...)> { using type = R; };

template <typename R, typename... Args>
struct return_type_impl<R(&)(Args..., ...)> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...)> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...)> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) &> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) &> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) &&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) &&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) const> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) const> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) const&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) const&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) const&&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) const&&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) volatile> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) volatile> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) volatile&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) volatile&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) volatile&&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) volatile&&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) const volatile> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) const volatile> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) const volatile&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) const volatile&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args...) const volatile&&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type_impl<R(C::*)(Args..., ...) const volatile&&> { using type = R; };

template <typename T, typename = void>
struct return_type
  : return_type_impl<T> {};

template <typename T>
struct return_type<T, decltype(void(&T::operator()))>
  : return_type_impl<decltype(&T::operator())> {};

template <typename T>
using return_type_t = typename return_type<T>::type;

template<typename TFunctor/*, typename TReturn*/>
class Property2 final  {
  public:
    //typedef TFunctor::result_type storage_type;
    //typedef std::result_of<TFunctor> storage_type;
    //typedef int storage_type;
    typedef return_type_t<TFunctor> storage_type;

    Property2(TFunctor updater) : m_updater(updater) {
        m_value = updater();
        std::cout << "+++ Constructor " << __PRETTY_FUNCTION__ << " -> " <<
                  ": " << m_value << " called. +++" << std::endl;
    }

    Property2(const Property2 &) = delete;  // non construction-copyable
    Property2 &operator=(const Property2 &) = delete;  // non copyable

    [[nodiscard]] bool HasChanged() {
        auto newValue = m_updater();
        std::cout << "newValue: " << newValue << std::endl;
        bool result = newValue != m_value;
        m_value = newValue;
        return result;
    }

    [[nodiscard]] const storage_type &Get() const {
        return m_value;
    }

  private:


    storage_type m_value;
    //TReturn m_value;
    TFunctor m_updater;
};

template<typename TFunctor>
auto MyFunc(TFunctor Func)
{
    return Func();
}

/** Program Entry Function, main
 *  The designated start of the program.
 *  @return program exit code.
 */
int main() {
    // print Hello World on the screen
    std::cout << "Hello cheesy World" << std::endl;

    int a = 7;
    std::function<int(void)> f = [&a]() { return a; };
    //std::function<int(void)>::result_type
    //auto p1 = core::util::Property<int>(f);
    //auto p1 = core::util::Property<int>([&a]() { return a; });
    auto p2 = Property2<std::function<int(void)>>( [&a]() { return a; } );
    auto p3 = MyFunc( [&a]() { return a; } );
    auto p4 = Property2( [&a]() { return a; } );
    //auto p5 = Property2( f );

    return 0; // program exit code
}
