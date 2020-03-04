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

#ifndef OPENGLTEMPLATE_WGL_COMMON_H
#define OPENGLTEMPLATE_WGL_COMMON_H

#include <windef.h>

/** Brief description of $(fclass), make_window_and_test
 *  Detailed description.
 *  @param hdc TODO
 */
void make_window_and_test(int (* callback)(HDC hdc));

#endif //OPENGLTEMPLATE_WGL_COMMON_H
