/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TileMap.h class.
 * \file       TileMap.h
 * \date       2020-03-29
 * \author     Jedzia.
 *
 * modified    2020-03-29, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGLTEMPLATE_54C63F12088447AE842BF69192838603_TILEMAP_H
#define OPENGLTEMPLATE_54C63F12088447AE842BF69192838603_TILEMAP_H
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace grg {
class TileMap : public sf::Drawable,
                public sf::Transformable {
public:

    bool Load(const std::string &tileSet, sf::Vector2u tileSize, const unsigned int* tiles, unsigned int width,
            unsigned int height, float uniformScale = 1.0F);

private:

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileSet;
};
}
#endif//OPENGLTEMPLATE_54C63F12088447AE842BF69192838603_TILEMAP_H
