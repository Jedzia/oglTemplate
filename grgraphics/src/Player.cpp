/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Player.cpp class.
 * \file       Player.cpp
 * \date       2020-04-06
 * \author     Jedzia.
 *
 * modified    2020-04-06, Jedzia
 */
/*---------------------------------------------------------*/
#include "grcore/warning/FMT_format_log.h"
#include "grgraphics/Player.h"
#include "grgraphics/warning/SFML_Graphics.h"

// The player should be positioned with x,y -1.0 to 0 to +1.0 like opengl system.

bool grg::Player::Load(const std::string &tileSet, sf::Vector2u tileSize, const unsigned int *tiles, unsigned int width,
                       unsigned int height, float uniformScale) {
    static_cast<void>(tileSet);
    static_cast<void>(tileSize);
    static_cast<void>(tiles);
    static_cast<void>(width);
    static_cast<void>(height);
    static_cast<void>(uniformScale);
    return false;
}

void grg::Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_playerSprite;

    // draw the vertex array
    target.draw(m_vertices, states);
}

