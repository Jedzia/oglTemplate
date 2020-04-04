/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the wgl_common.h class.
 * \file       wgl_common.h
 * \date       2020-03-04
 * \author     Jedzia.
 *
 * modified    2020-03-04, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGLTEMPLATE_019DC44D962B4EE993A8802847A9A0C3_WGL_COMMON_H
#define OPENGLTEMPLATE_019DC44D962B4EE993A8802847A9A0C3_WGL_COMMON_H

#include <windef.h>

/** Setup a GUI window.
 *
 *  A wrapper to quickly setup a GUI window.
 *  @param hdc Callback routine for the window loop.
 */
void makeWindowAndTest(int (* callback)(HDC hdc));

#endif //OPENGLTEMPLATE_019DC44D962B4EE993A8802847A9A0C3_WGL_COMMON_H
