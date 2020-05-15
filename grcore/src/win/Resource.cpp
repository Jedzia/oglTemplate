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
 * modified    2020-03-26, Jedzia
 */
/*---------------------------------------------------------*/

#include "grcore/Resource.h"
#include <spdlog/spdlog.h>
#include <iostream>
#include <stdexcept>
#include <windows.h>

extern void* G_DLL_INSTANCE_HANDLE;

grcore::Resource::Resource(int resourceName) : m_id(resourceName) {
    //std::cout << "+++ Constructor " << __PRETTY_FUNCTION__ << " called. +++" << "\n";
    spdlog::debug(" {1}:{2} +++ Constructor [{0}] (resourceName={0}) called. +++", __PRETTY_FUNCTION__, __FILE__, __LINE__, resourceName);
}

grcore::Resource::~Resource() {
    //std::cout << "+++ Destructor  " << __PRETTY_FUNCTION__ << " called. +++" << "\n";
    spdlog::debug(" {1}:{2} +++ Destructor  [{0}]  called. +++", __PRETTY_FUNCTION__, __FILE__, __LINE__);
    // no need to free something, its a embedded resource.
    //if(p_handle)
}

std::tuple<const void *, size_t, int> grcore::Resource::Get() {
    static_cast<void>(m_id);
    //int type = 333; //static_cast<int>(RT_FONT);
    int error = 0;
    if(!G_DLL_INSTANCE_HANDLE) {
        G_DLL_INSTANCE_HANDLE = ::GetModuleHandleW(L"libGrCore.dll");
        std::cout << __PRETTY_FUNCTION__ << ": Handle via GetModuleHandleW(L\"libGrCore.dll\")" << "\n";
    }

    if(!G_DLL_INSTANCE_HANDLE) {
        throw std::runtime_error("Missing DLL Handle");
    }

    HMODULE handle = static_cast<HMODULE>(G_DLL_INSTANCE_HANDLE);
    HRSRC rc = ::FindResourceW(handle, MAKEINTRESOURCEW(m_id), L"BINARY");
    HGLOBAL rcData = ::LoadResource(handle, rc);
    auto size = ::SizeofResource(handle, rc);
    auto data = static_cast<const void *>(::LockResource(rcData));
    //LockResource does not actually lock memory; it is just used to obtain a pointer to the memory
    // containing the resource data.
    return {
               data, size, error
    };
} // grcore::Resource::Get
