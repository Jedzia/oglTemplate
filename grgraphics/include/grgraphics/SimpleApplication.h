/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the SimpleApplication.h class.
 * \file       SimpleApplication.h
 * \date       2020-03-17
 * \author     Jedzia.
 *
 * modified    2020-03-17, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGLTEMPLATE_61CDCBB50D51466E91769A07F3D44D19_SIMPLEAPPLICATION_H
#define OPENGLTEMPLATE_61CDCBB50D51466E91769A07F3D44D19_SIMPLEAPPLICATION_H

#include "warning/SFML_Graphics.h"

namespace grg {
/** @class SimpleApplication:
 *  Detailed description.
 *  @param window TODO
 *  @param elapsed TODO
 */
class SimpleApplication {
public:

    virtual void OnDraw(sf::RenderWindow &window, sf::Time elapsed) = 0;

    virtual ~SimpleApplication() = default;
};
}

#endif //OPENGLTEMPLATE_61CDCBB50D51466E91769A07F3D44D19_SIMPLEAPPLICATION_H
