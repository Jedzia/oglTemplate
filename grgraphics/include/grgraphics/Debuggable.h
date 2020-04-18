/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Debuggable.h class.
 * \file       Debuggable.h
 * \date       2020-04-08
 * \author     Jedzia.
 *
 * modified    2020-04-08, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef OPENGLTEMPLATE_47425121E51D4AB1BF1CF3E34AD684A0_DEBUGGABLE_H
#define OPENGLTEMPLATE_47425121E51D4AB1BF1CF3E34AD684A0_DEBUGGABLE_H

#include "grgraphics/warning/SFML_Graphics.h"
//
#include <SFML/Graphics/Font.hpp>

namespace grg {
class Debuggable {
protected:

    Debuggable();
    bool m_isInDebugMode = true;
    static sf::Font m_debugFont;
};
}

#endif//OPENGLTEMPLATE_47425121E51D4AB1BF1CF3E34AD684A0_DEBUGGABLE_H
