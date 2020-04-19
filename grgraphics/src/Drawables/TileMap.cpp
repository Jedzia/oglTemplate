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
#include "grcore/warning/FMT_format_log.h"
#include "grgraphics/warning/SFML_Graphics.h"
//
#include "grgraphics/Drawables/TileMap.h"

bool grg::TileMap::Load(const std::string &tileSet, sf::Vector2u tileSize, const unsigned int* tiles, unsigned int width,
        unsigned int height, float uniformScale) {
    m_tileSize = tileSize;
    m_tileWidth = width;
    m_tileHeight = height;

    // load the tileSet texture
    if(!m_tileSet.loadFromFile(tileSet)) {
        return false;
    }

    const sf::Vector2f scaling{ uniformScale, uniformScale };
    const sf::Vector2f downscaling{ 1.0F / uniformScale, 1.0F / uniformScale };

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for(unsigned int i = 0; i < width; ++i) {
        for(unsigned int j = 0; j < height; ++j) {
            // get the current tile number
            const auto indexPosition = i + j * width;
            unsigned int tileNumber = tiles[indexPosition];

            // find its position in the tileSet texture
            unsigned int tu = tileNumber % (m_tileSet.getSize().x / tileSize.x);
            unsigned int tv = tileNumber / (m_tileSet.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[indexPosition * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(static_cast<float>(i * tileSize.x), static_cast<float>(j * tileSize.y));
            quad[1].position = sf::Vector2f(static_cast<float>((i + 1) * tileSize.x), static_cast<float>(j * tileSize.y));
            quad[2].position = sf::Vector2f(static_cast<float>((i + 1) * tileSize.x), static_cast<float>((j + 1) * tileSize.y));
            quad[3].position = sf::Vector2f(static_cast<float>(i * tileSize.x), static_cast<float>((j + 1) * tileSize.y));

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(static_cast<float>(tu * tileSize.x), static_cast<float>(tv * tileSize.y));
            quad[1].texCoords = sf::Vector2f(static_cast<float>((tu + 1) * tileSize.x), static_cast<float>(tv * tileSize.y));
            quad[2].texCoords = sf::Vector2f(static_cast<float>((tu + 1) * tileSize.x), static_cast<float>((tv + 1) * tileSize.y));
            quad[3].texCoords = sf::Vector2f(static_cast<float>(tu * tileSize.x), static_cast<float>((tv + 1) * tileSize.y));

            if(Is_In_Debug_Mode) {
                float horizontalPosition = static_cast<float>(tileSize.x * i);
                float verticalPosition = static_cast<float>(tileSize.y * j);
                sf::Vector2f textPosition = { horizontalPosition, verticalPosition };
                auto &txt1 = make_debug_text<sf::Text>(fmt::format("[{}:]", indexPosition, tileNumber, horizontalPosition,
                        verticalPosition), m_debugFont, 24);
                txt1->setScale(downscaling);
                txt1->setPosition(textPosition);
                float txt1Height = txt1->getGlobalBounds().height;

                auto &txt2 = make_debug_text<sf::Text>(fmt::format("[No.{}]", tileNumber), m_debugFont, 24);
                txt2->setScale(downscaling);
                textPosition.y += txt1Height;
                txt2->setPosition(textPosition);
                float txt2Height = txt2->getGlobalBounds().height;

                auto &txt3 = make_debug_text<sf::Text>(fmt::format("({}, {})", horizontalPosition, verticalPosition), m_debugFont, 12);
                txt3->setScale(downscaling);
                textPosition.y += txt2Height + txt3->getGlobalBounds().height / 2.0F;
                txt3->setPosition(textPosition);
            }
        }
    }
    this->scale(uniformScale, uniformScale);

    return true;
}// grg::TileMap::Load

void grg::TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileSet;

    // draw the vertex array
    target.draw(m_vertices, states);

    Debuggable::draw(target, states);
}

sf::Vector2f grg::TileMap::GetSize() const {
    float fullWidth = static_cast<float>(m_tileSize.x * m_tileWidth);
    float fullHeight = static_cast<float>(m_tileSize.y * m_tileHeight);
    sf::Vector2f result(fullWidth, fullHeight);
    sf::Vector2f adapted(result.x * this->getScale().x, result.y * this->getScale().y);
    return adapted;
}

sf::Vector2f grg::TileMap::GetTilePosition(unsigned int x, unsigned int y) const {
    float fullWidth = static_cast<float>(m_tileSize.x * x);
    float fullHeight = static_cast<float>(m_tileSize.y * y);
    sf::Vector2f result(fullWidth, fullHeight);
    sf::Vector2f adapted(result.x * this->getScale().x, result.y * this->getScale().y);
    return adapted;
}

grg::TileMap::~TileMap() {}
