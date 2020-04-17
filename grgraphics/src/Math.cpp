/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Math.cpp class.
 * \file       Math.cpp
 * \date       2020-04-08
 * \author     Jedzia.
 *
 * modified    2020-04-08, Jedzia
 */
/*---------------------------------------------------------*/
#include "grgraphics/Math.h"


std::array grg::G_DIRECTIONS =
        {
                /** Up */
                sf::Vector2f{0.0F, -1.0F},
                /** Right */
                sf::Vector2f{1.0F, 0.0F},
                /** Down */
                sf::Vector2f{0.0F, 1.0F},
                /** Left */
                sf::Vector2f{-1.0F, 0.0F},
        };

