/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the resource.cpp class.
 * \file       resource.cpp
 * \date       2020-03-25
 * \author     Jedzia.
 *
 * modified    2020-03-25, Jedzia
 */
/*---------------------------------------------------------*/
//
// Created by Jedzia on 26.03.2020.
//

//#include <libloaderapi.h>
//#include <winuser.h>
#include "grcore/resource.h"
#include <iostream>
#include <stdexcept>
#include <windows.h>
//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Wunused-variable"
core::Resource::Resource(int resourceName) : m_id(resourceName) {}

core::Resource::~Resource() {
    // no need to free something, its a embedded resource.
    //if(p_handle)
}

std::tuple<const void *, size_t, int> core::Resource::Get() {
    static_cast<void>(m_id);
    //int type = 333; //static_cast<int>(RT_FONT);
    int error = 0;
    //int name = 129;
    //int type = 256;
    //int name = 255;
    //HMODULE handle = ::GetModuleHandleW(NULL);
    if(!p_handle) {
        p_handle = ::GetModuleHandleW(L"libGrCore.dll");
        std::cout << __PRETTY_FUNCTION__ << ": Handle via GetModuleHandleW(L\"libGrCore.dll\")" << std::endl;
    }

    if(!p_handle) {
        throw new std::runtime_error("Missing DLL Handle");
    }

    HMODULE handle = static_cast<HMODULE>(p_handle);
    //HRSRC rc = ::FindResourceW(handle, MAKEINTRESOURCEW(name), MAKEINTRESOURCEW(type));
    HRSRC rc = ::FindResourceW(handle, MAKEINTRESOURCEW(m_id), L"BINARY");
    //HRSRC rc = ::FindResource(handle, MAKEINTRESOURCE(name), MAKEINTRESOURCE(type));
    HGLOBAL rcData = ::LoadResource(handle, rc);
    auto size = ::SizeofResource(handle, rc);
    //static_cast<void>(size);
    //auto data = static_cast<const wchar_t*>(::LockResource(rcData));
    //auto data = static_cast<const char *>(::LockResource(rcData));
    auto data = static_cast<const void *>(::LockResource(rcData));
    //static_cast<void>(data);
    return {
               data, size, error
    };
    //LockResource does not actually lock memory; it is just used to obtain a pointer to the memory
    // containing the resource data.
} // core::Resource::Get

void * core::Resource::p_handle = nullptr;

//#pragma clang diagnostic pop
