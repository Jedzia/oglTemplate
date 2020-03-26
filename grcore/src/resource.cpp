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
#include <windows.h>
#include "grcore/resource.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
core::Resource::Resource(int mId) : m_id(mId) {
}
void core::Resource::Get() {
    static_cast<void>(m_id);
    //int type = 333; //static_cast<int>(RT_FONT);
    int name = 129;
    //int type = 256;
    //int name = 255;
    //HMODULE handle = ::GetModuleHandleW(NULL);
    HMODULE handle = ::GetModuleHandleW(L"libGrCore.dll");
    //HRSRC rc = ::FindResourceW(handle, MAKEINTRESOURCEW(name), MAKEINTRESOURCEW(type));
    HRSRC rc = ::FindResourceW(handle, MAKEINTRESOURCEW(name), L"BINARY");
    //HRSRC rc = ::FindResource(handle, MAKEINTRESOURCE(name), MAKEINTRESOURCE(type));
    HGLOBAL rcData = ::LoadResource(handle, rc);
    auto size = ::SizeofResource(handle, rc);
    //auto data = static_cast<const wchar_t*>(::LockResource(rcData));
    auto data = static_cast<const char*>(::LockResource(rcData));
    //LockResource does not actually lock memory; it is just used to obtain a pointer to the memory containing the resource data.
}

#pragma clang diagnostic pop