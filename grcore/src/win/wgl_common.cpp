/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the wgl_common.cpp class.
 * \file       wgl_common.cpp
 * \date       2020-03-04
 * \author     Jedzia.
 *
 * modified    2020-03-04, Jedzia
 */
/*---------------------------------------------------------*/

//
// Created by Jedzia on 04.03.2020.
//

#include <cstdio>
//#include <epoxy/wgl.h>
#include "grcore/wgl_common.h"
#include <windows.h>

static int (* TEST_CALLBACK)(HDC hdc);

/** Brief description of $(fclass), setupPixelFormat
 *
 *  Detailed description.
 *  @param hdc TODO
 */
static void setupPixelFormat(HDC hdc) {
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        /*(unsigned int)*/ PFD_SUPPORT_OPENGL |
        PFD_DRAW_TO_WINDOW |
        PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        16,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0,
    };
    int pixelFormat;

    pixelFormat = ChoosePixelFormat(hdc, &pfd);
    if(!pixelFormat) {
        fputs("ChoosePixelFormat failed.\n", stderr);
        exit(1);
    }

    if(SetPixelFormat(hdc, pixelFormat, &pfd) != TRUE) {
        fputs("SetPixelFormat() failed.\n", stderr);
        exit(1);
    }
} // setupPixelFormat

/** Brief description of $(fclass), window_proc
 *
 *  Detailed description.
 *  @param hwnd TODO
 *  @param message TODO
 *  @param wparam TODO
 *  @param lparam TODO
 *  @return TODO
 */
static LRESULT CALLBACK window_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
    HDC hdc = GetDC(hwnd);
    int ret;

    switch(message) {
    case WM_CREATE:
        setupPixelFormat(hdc);
        ret = TEST_CALLBACK(hdc);
        ReleaseDC(hwnd, hdc);
        exit(ret);
        return 0;

    default:
        return DefWindowProc(hwnd, message, wparam, lparam);
    }
}

/** Brief description of $(fclass), makeWindowAndTest
 *
 *  Detailed description.
 *  @param hdc TODO
 */
void makeWindowAndTest(int (* callback)(HDC hdc)) {
    const char* className = "epoxy";
    const char* windowName = "epoxy";
    int width = 150;
    int height = 150;
    HWND hwnd;
    HINSTANCE currentInstance = nullptr;
    WNDCLASS windowClass;
    MSG msg;

    TEST_CALLBACK = callback;

    memset(&windowClass, 0, sizeof(windowClass));
    windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = window_proc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = currentInstance;
    windowClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.hbrBackground = reinterpret_cast<HBRUSH>((COLOR_WINDOW + 1));
    windowClass.lpszMenuName = nullptr;
    windowClass.lpszClassName = className;
    if(!RegisterClass(&windowClass)) {
        fputs("Failed to register window class\n", stderr);
        exit(1);
    }

    /* create window */
    hwnd = CreateWindow(className, windowName,
            WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
            0, 0, width, height,
            nullptr, nullptr, currentInstance, nullptr);

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
} // makeWindowAndTest
