/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the return_type_trait.h class.
 * \file       return_type_trait.h
 * \date       2020-03-28
 * \author     Jedzia.
 *
 * modified    2020-03-28, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGLTEMPLATE_8126C7C5011C4F168C3A0358C2399C79_RETURN_TYPE_TRAIT_H
#define OPENGLTEMPLATE_8126C7C5011C4F168C3A0358C2399C79_RETURN_TYPE_TRAIT_H
namespace core {
namespace util {
template<typename F>
struct return_type_impl;

template<typename R, typename ... Args>
struct return_type_impl<R(Args ...)> {
    using type = R;
};

template<typename R, typename ... Args>
struct return_type_impl<R(Args ..., ...)> {
    using type = R;
};

template<typename R, typename ... Args>
struct return_type_impl<R (*)(Args ...)> {
    using type = R;
};

template<typename R, typename ... Args>
struct return_type_impl<R (*)(Args ..., ...)> {
    using type = R;
};

template<typename R, typename ... Args>
struct return_type_impl<R( &)(Args ...)> {
    using type = R;
};

template<typename R, typename ... Args>
struct return_type_impl<R( &)(Args ..., ...)> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ...)> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ..., ...)> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ...) &> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ..., ...) &> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ...) &&> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ..., ...) &&> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ...) const> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ..., ...) const> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ...) const &> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ..., ...) const &> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ...) const&&> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ..., ...) const&&> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ...) volatile> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ..., ...) volatile> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ...) volatile &> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ..., ...) volatile &> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ...) volatile&&> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ..., ...) volatile&&> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ...) const volatile> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ..., ...) const volatile> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ...) const volatile &> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ..., ...) const volatile &> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ...) const volatile&&> {
    using type = R;
};

template<typename R, typename C, typename ... Args>
struct return_type_impl<R (C::*)(Args ..., ...) const volatile&&> {
    using type = R;
};

template<typename T, typename = void>
struct return_type :
    return_type_impl<T> {};

template<typename T>
struct return_type<T, decltype(void( &T::operator()))> :
    return_type_impl<decltype( &T::operator())> {};

template<typename T>
using return_type_t = typename return_type<T>::type;
}
}
#endif//OPENGLTEMPLATE_8126C7C5011C4F168C3A0358C2399C79_RETURN_TYPE_TRAIT_H
