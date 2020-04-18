/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Debuggable.cpp class.
 * \file       Debuggable.cpp
 * \date       2020-04-08
 * \author     Jedzia.
 *
 * modified    2020-04-08, Jedzia
 */
/*---------------------------------------------------------*/
#include "grgraphics/Debuggable.h"
#include <grgraphics/Utility/Common.h>

sf::Font grg::Debuggable::m_debugFont;

grg::Debuggable::Debuggable() {
    grg::loadDebugFont(m_debugFont);
}
