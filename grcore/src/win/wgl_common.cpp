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

static int (* test_callback)(HDC hdc);

/** Brief description of $(fclass), setup_pixel_format
 *  Detailed description.
 *  @param hdc TODO
 */
static void setup_pixel_format(HDC hdc)             {
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
    int pixel_format;

    pixel_format = ChoosePixelFormat(hdc, &pfd);
    if(!pixel_format) {
        fputs("ChoosePixelFormat failed.\n", stderr);
        exit(1);
    }

    if(SetPixelFormat(hdc, pixel_format, &pfd) != TRUE) {
        fputs("SetPixelFormat() failed.\n", stderr);
        exit(1);
    }
} // setup_pixel_format

/** Brief description of $(fclass), window_proc
 *  Detailed description.
 *  @param hwnd TODO
 *  @param message TODO
 *  @param wparam TODO
 *  @param lparam TODO
 *  @return TODO
 */
static LRESULT CALLBACK window_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)                         {
    HDC hdc = GetDC(hwnd);
    int ret;

    switch(message) {
    case WM_CREATE:
        setup_pixel_format(hdc);
        ret = test_callback(hdc);
        ReleaseDC(hwnd, hdc);
        exit(ret);
        return 0;

    default:
        return DefWindowProc(hwnd, message, wparam, lparam);
    }
}

/** Brief description of $(fclass), make_window_and_test
 *  Detailed description.
 *  @param hdc TODO
 */
void make_window_and_test(int (* callback)(HDC hdc))       {
    const char* class_name = "epoxy";
    const char* window_name = "epoxy";
    int width = 150;
    int height = 150;
    HWND hwnd;
    HINSTANCE currentInstance = nullptr;
    WNDCLASS window_class;
    MSG msg;

    test_callback = callback;

    memset(&window_class, 0, sizeof(window_class));
    window_class.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = window_proc;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance = currentInstance;
    window_class.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    window_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
    window_class.hbrBackground = reinterpret_cast<HBRUSH>((COLOR_WINDOW + 1));
    window_class.lpszMenuName = nullptr;
    window_class.lpszClassName = class_name;
    if(!RegisterClass(&window_class)) {
        fputs("Failed to register window class\n", stderr);
        exit(1);
    }

    /* create window */
    hwnd = CreateWindow(class_name, window_name,
            WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
            0, 0, width, height,
            nullptr, nullptr, currentInstance, nullptr);

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
} // make_window_and_test
