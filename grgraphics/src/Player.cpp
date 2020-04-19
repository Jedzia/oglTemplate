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
 * modified    2020-04-19, Jedzia
 */
/*---------------------------------------------------------*/
#include "grcore/warning/FMT_format_log.h"
#include "grgraphics/warning/SFML_Graphics.h"
//
#include "grgraphics/Player.h"
#include <array>

//#include <exception>

// The player should be positioned with x,y -1.0 to 0 to +1.0 like opengl system.

// player has its world coords. WASD and affected by a speed ramp
// a camera takes that and positions a view of the world according to the players coords.
// camera can limit to edges or have a delayed follow, or a strict follow.
// or move out of the window and swipe in a new screen.

grg::Player::Player() : m_position{0.0F, 0.0F} {}

bool grg::Player::Load(const std::string &filename, sf::Vector2u tileSize, const unsigned int* tiles, unsigned int width,
        unsigned int height, float uniformScale) {
    // ToDo: unused
    static_cast<void>(height);

    // load the tileSet texture
    if(!m_playerSprite.loadFromFile(filename)) {
        throw std::runtime_error(fmt::format("[{}] Cannot load sprite '{}'.", __PRETTY_FUNCTION__, filename));
    }

    m_spriteOverlay.Initialize(tileSize.x, tileSize.y, uniformScale);
    m_spriteOverlay.setPosition(getPosition());

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(4);

    unsigned int i = 0;
    unsigned int j = 0;
    // get the current tile number
    unsigned int tileNumber = tiles[i + j * width];

    // find its position in the tileSet texture
    unsigned int tu = tileNumber % (m_playerSprite.getSize().x / tileSize.x);
    unsigned int tv = tileNumber / (m_playerSprite.getSize().x / tileSize.x);

    // get a pointer to the current tile's quad
    sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

    // define its 4 corners
    quad[0].position = sf::Vector2f(static_cast<float>(i * tileSize.x), static_cast<float>(j * tileSize.y));
    quad[1].position = sf::Vector2f(static_cast<float>((i + 1) * tileSize.x), static_cast<float>(j * tileSize.y));
    quad[2].position = sf::Vector2f(static_cast<float>((i + 1) * tileSize.x), static_cast<float>((j + 1) * tileSize.y));
    quad[3].position = sf::Vector2f(static_cast<float>(i * tileSize.x), static_cast<float>((j + 1) * tileSize.y));

    // define its 4 texture coordinates
    quad[0].texCoords = sf::Vector2f(static_cast<float>(tu * tileSize.x), static_cast<float>(tv * tileSize.y));
    quad[1].texCoords = sf::Vector2f(static_cast<float>((tu + 1) * tileSize.x), static_cast<float>(tv * tileSize.y));
    quad[2].texCoords = sf::Vector2f(static_cast<float>((tu + 1) * tileSize.x),
            static_cast<float>((tv + 1) * tileSize.y));
    quad[3].texCoords = sf::Vector2f(static_cast<float>(tu * tileSize.x), static_cast<float>((tv + 1) * tileSize.y));

    this->scale(uniformScale, uniformScale);
    return true;
} // grg::Player::Load

void grg::Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the player texture
    states.texture = &m_playerSprite;

    // draw the vertex array
    target.draw(m_vertices, states);

    // draw debug sprite overlay
    target.draw(m_spriteOverlay, states);
}

void grg::Player::Update(sf::Time elapsed) {
    //const float elapsedSeconds = elapsed.asSeconds();
    //bool viewChanged = false;

    const float zoomFactor = 1.01F;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
        this->scale(zoomFactor, zoomFactor);
        spdlog::info("Player zoom {}, {}.", getScale().x, getScale().y);
        //viewChanged = true;
    } else {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            this->scale(1.0F / zoomFactor, 1.0F / zoomFactor);
            spdlog::info("Player zoom {}, {}.", getScale().x, getScale().y);
            //viewChanged = true;
        }
    }

    m_velocity.DoUpdate(elapsed);
    this->setPosition(m_velocity.GetPosition());
    m_spriteOverlay.Update(elapsed, *this);
} // grg::Player::Update

const sf::Vector2f &grg::Player::GetPlayerPosition() const {
    return m_position;
}

void grg::Player::SetPlayerPosition(const sf::Vector2f &position) {
    m_velocity.SetVelocity({});
    m_velocity.SetPosition(position);
    m_position = position;
}
