/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TileMap.cpp class.
 * \file       TileMap.cpp
 * \date       2020-03-29
 * \author     Jedzia.
 *
 * modified    2020-03-29, Jedzia
 */
/*---------------------------------------------------------*/
#include "grgraphics/Drawables/TileMap.h"
#include "grgraphics/warning/FMT_format.h"
#include "grgraphics/warning/SFML_Graphics.h"

//#pragma clang diagnostic warning "-Wconversion"

bool
grg::TileMap::Load(const std::string &tileSet, sf::Vector2u tileSize, const unsigned int *tiles, unsigned int width,
                   unsigned int height, float uniformScale) {
#if defined(__clang__)
    // load the tileSet texture
    if(!m_tileSet.loadFromFile(tileSet)) {
        return false;
    }

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for(unsigned int i = 0; i < width; ++i) {
        for(unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            unsigned int tileNumber = tiles[i + j * width];

            // find its position in the tileSet texture
            unsigned int tu = tileNumber % (m_tileSet.getSize().x / tileSize.x);
            unsigned int tv = tileNumber / (m_tileSet.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }

    this->scale(uniformScale, uniformScale);

#else
    static_cast<void>(tileSet);
    static_cast<void>(tileSize);
    static_cast<void>(tiles);
    static_cast<void>(width);
    static_cast<void>(height);
    static_cast<void>(uniformScale);
#endif
    return true;
} // grg::TileMap::Load

void grg::TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileSet;

    // draw the vertex array
    target.draw(m_vertices, states);
}
