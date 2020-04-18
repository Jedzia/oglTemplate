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
#include <grgraphics/Debuggable.h>
#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>

namespace sf {
class Text;
}

namespace grg {
class TileMap : public sf::Drawable,
                public sf::Transformable,
                protected Debuggable {
public:

    virtual ~TileMap();
    bool Load(const std::string &tileSet, sf::Vector2u tileSize, const unsigned int* tiles, unsigned int width,
            unsigned int height, float uniformScale = 1.0F);

    /** @brief Get the size of the TileMap
     *
     * Scaling is reflected in the value.
     * @return Size of the TileMap
     *
     * @see getCenter, setSize
     */
    sf::Vector2f GetSize() const;

    /** Get position of a tile.
     *
     * Gets the position of a specified tile in world(?) coordinates.
     * Scaling is considered in the calculation.
     * @param x Horizontal tile position.
     * @param y Vertical tile position
     * @return the position of the tile in world(?) space.
     */
    sf::Vector2f GetTilePosition(unsigned int x, unsigned int y) const;

    /** Get horizontal tile number
     *
     * @return the amount of horizontal tiles in this map.
     */
    unsigned int GetTileWidth() const {
        return m_tileWidth;
    }

    /** Get vertical tile number
     *
     * @return the amount of vertical tiles in this map.
     */
    unsigned int GetTileHeight() const {
        return m_tileHeight;
    }

private:

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileSet;
    unsigned int m_tileWidth = 0;
    unsigned int m_tileHeight = 0;
    sf::Vector2u m_tileSize {};
    std::vector<std::unique_ptr<sf::Text>> m_vCoords;
};
}
#endif//OPENGLTEMPLATE_54C63F12088447AE842BF69192838603_TILEMAP_H
