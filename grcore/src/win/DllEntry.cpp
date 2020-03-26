/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains code to handle
 *             the DLL Entry-Point behaviour.
 * \file       dllentry.cpp
 * \date       2020-03-26
 * \author     Jedzia.
 *
 * modified    2020-03-26, Jedzia
 */
/*---------------------------------------------------------*/
#include <grcore/Resource.h>
#include <windows.h>

void* HINST_DLL = nullptr;

BOOL WINAPI DllMain(
        HINSTANCE hinstDLL,// handle to DLL module
        DWORD fdwReason,// reason for calling function
        LPVOID /*lpReserved*/) {// reserved
    // Perform actions based on the reason for calling.
    switch(fdwReason) {
    case DLL_PROCESS_ATTACH:
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        //core::Resource::SetHandle(hinstDLL);
        HINST_DLL = hinstDLL;
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:
        // Perform any necessary cleanup.
        break;
    }// switch
    return TRUE;// Successful DLL_PROCESS_ATTACH.
}// DllMain
