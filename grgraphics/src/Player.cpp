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

// player has its world coords. WASD and affected by a speed ramp
// a camera takes that and positions a view of the world according to the players coords.
// camara can limit to edges or have a delayed follow, or a strict follow.
// or move out of the window and swipe in a new screen.

grg::Player::Player() {
    //m_position = {-1280.0F / 2, -120.0F };
    //m_position = {-280.0F, -120.0F };
    m_position = {10.0F, 10.0F };
}

bool grg::Player::Load(const std::string &filename, sf::Vector2u tileSize, const unsigned int* tiles, unsigned int width,
        unsigned int height, float uniformScale) {
    //static_cast<void>(tileSize);
    //static_cast<void>(tiles);
    //static_cast<void>(width);
    static_cast<void>(height);
    //static_cast<void>(uniformScale);

    // load the tileSet texture
    if(!m_playerSprite.loadFromFile(filename)) {
        return false;
    }

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    //m_vertices.resize(width * height * 4);
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
    quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
    quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
    quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
    quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

    // define its 4 texture coordinates
    quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
    quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
    quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
    quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

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
}

void grg::Player::Update(sf::Time elapsed) {
    const float elapsedSeconds = elapsed.asSeconds();
    bool viewChanged = false;

    const float zoomFactor = 1.01F;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        //m_view.zoom(zoomFactor);
        this->scale(zoomFactor, zoomFactor);
        spdlog::info("Player zoom {}, {}.", getScale().x, getScale().y);
        viewChanged = true;
    } else {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            // m_view.zoom(1.0F / zoomFactor);
            this->scale(1.0F / zoomFactor, 1.0F / zoomFactor);
            spdlog::info("Player zoom {}, {}.", getScale().x, getScale().y);
            viewChanged = true;
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        //m_view.zoom(zoomFactor);
        //this->scale(zoomFactor, zoomFactor);
        m_position += {0.0F, 500.0F * elapsedSeconds};
        //spdlog::info("Player zoom {}, {}.", getScale().x, getScale().y);
        viewChanged = true;
    } else {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            // m_view.zoom(1.0F / zoomFactor);
            //this->scale(1.0F / zoomFactor, 1.0F / zoomFactor);
            m_position += {0.0F, -500.0F * elapsedSeconds};
            //spdlog::info("Player zoom {}, {}.", getScale().x, getScale().y);
            viewChanged = true;
        }
    }

    // scrolling/movement calculations
    {
        constexpr float speedUp = 2.0F;
        constexpr float keyAcceleration = 500.0F * speedUp;
        bool moveKeyPressed = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            // m_view.move(-1.0F * 1000 * elapsedSeconds, 0.0F);
            m_xVelocity -= speedUp * keyAcceleration * elapsedSeconds;
            //spdlog::info("m_xVelocity={}.", m_xVelocity);
            viewChanged = true;
            moveKeyPressed = true;
        } else {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                //m_view.move(1.0F * 1000 * elapsedSeconds, 0.0F);
                m_xVelocity += speedUp * keyAcceleration * elapsedSeconds;
                //spdlog::info("m_xVelocity={}.", m_xVelocity);
                viewChanged = true;
                moveKeyPressed = true;
            }
        }

        const float absVelocity = std::abs(m_xVelocity);
        float speedRamp = 1.0F - elapsedSeconds * speedUp;
        //if(absVelocity + 1.0F < lastAbsVelocity) {
        if(!moveKeyPressed) {
            //} else {
            constexpr float slowDown = 1.4F * speedUp;
            speedRamp = 1.0F - elapsedSeconds * slowDown;
            constexpr float hysteresisEdge = 50.0F * slowDown; // lower edge when friction
            // starts to
            // decrease velocity abrupt.
            if(absVelocity < hysteresisEdge) {
                speedRamp = 1.0F -
                            ((elapsedSeconds * slowDown * 1.0F) +
                             (0.01F * ((hysteresisEdge / 10.0F) - (absVelocity / (hysteresisEdge / 5.0F)))));
                //if(absVelocity < (hysteresisEdge / 100.0F)) {
                if(absVelocity < (0.5F)) {
                    // stop all movement at 1% of the hysteresis low point.
                    m_xVelocity = 0;
                }
            }
        }

        m_lastAbsVelocity = absVelocity;
        m_xVelocity *= speedRamp;
        //m_csvFile.WriteData(m_xVelocity);
        //grcore::writeTelemetryData(static_cast<double>(m_xVelocity));

        { // handle Graph
          //m_view.move(m_xVelocity * elapsedSeconds, 0.0F);

            m_position += {
                m_xVelocity* elapsedSeconds, 0.0F
            };

            /*if(viewChanged || m_window->getView().getTransform() != m_view.getTransform()) {
                m_window->setView(m_view);
               }*/
        }

        //this->setOrigin(m_position);
        this->setPosition(m_position);
        /*spdlog::info(fmt::format("elapsed time: {:.2f}s, x: {:.1f}, y: {:.1f}, xVelocity: {:.1f},
           speedRamp: {:.3f}",
                elapsed.asSeconds(), m_view.getCenter().x, m_view.getCenter().y, m_xVelocity,
                   speedRamp));*/
        /*spdlog::info(fmt::format("elapsed time: {:.2f}s, x: {:.1f}, y: {:.1f}, xVelocity: {:.1f}, speedRamp: {:.3f}",
                        elapsed.asSeconds(), m_position.x, m_position.y, m_xVelocity, speedRamp));*/

        /*m_backGround->setString(
                fmt::format("elapsed time: {:.2f}s, x: {:.1f}, y: {:.1f}, xVelocity: {:.1f},
                   speedRamp: {:.3f}",
                        m_totalTime.asSeconds(),
                        m_coord.x, m_coord.y, m_xVelocity, speedRamp));*/
    }
}

const sf::Vector2f &grg::Player::GetPlayerPosition() const {
    return m_position;
}

void grg::Player::SetPlayerPosition(const sf::Vector2f &position) {
    m_position = position;
}
// grg::Player::Update

// grg::Player::Update
