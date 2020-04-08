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
#include "grgraphics/warning/SFML_Graphics.h"
//
#include "grgraphics/Player.h"
#include "grgraphics/Utility/Velocity.h"
#include <exception>
#include <array>

// The player should be positioned with x,y -1.0 to 0 to +1.0 like opengl system.

// player has its world coords. WASD and affected by a speed ramp
// a camera takes that and positions a view of the world according to the players coords.
// camara can limit to edges or have a delayed follow, or a strict follow.
// or move out of the window and swipe in a new screen.

grg::Player::Player() {
    //m_position = {-1280.0F / 2, -120.0F };
    //m_position = {-280.0F, -120.0F };
    //m_position = {10.0F, 10.0F};
    m_position = {0.0F, 0.0F};
}

bool
grg::Player::Load(const std::string &filename, sf::Vector2u tileSize, const unsigned int *tiles, unsigned int width,
                  unsigned int height, float uniformScale) {
    // ToDo: unused
    static_cast<void>(height);

    // load the tileSet texture
    if(!m_playerSprite.loadFromFile(filename)) {
        //return false;
        throw std::runtime_error(fmt::format("[{}] Cannot load sprite '{}'.", __PRETTY_FUNCTION__, filename));
    }
    m_SpriteOverlay.Initialize(tileSize.x, tileSize.y);
    //m_playerTextureBorder.create(m_playerSprite.getSize().x, m_playerSprite.getSize().y);
//    const unsigned int texWidth = tileSize.x;
//    const unsigned int texHeight =  tileSize.y;
    //const unsigned int texWidth = 128;
    //const unsigned int texHeight = 128;
//    m_playerTextureBorder.create(texWidth, texHeight);

    //sf::Uint8 tex[m_playerSprite.getSize().x * m_playerSprite.getSize().y];
    //std::vector<sf::Uint8> tex(m_playerSprite.getSize().x * m_playerSprite.getSize().y);
    /*std::vector<sf::Uint8> *tex = new std::vector<sf::Uint8>(m_playerSprite.getSize().x * m_playerSprite.getSize().y);
    for(unsigned int x = 0; x < m_playerSprite.getSize().x; ++x) {
        for(unsigned int y = 0; y < m_playerSprite.getSize().y; ++y) {
            (*tex)[x*m_playerSprite.getSize().x + y] = 123;
        }
    }

    m_playerTextureBorder.update((*tex).data());*/
    //sf::Uint8 tex[128 * 128];
/*struct rgba {
    sf::Uint8 r;
    sf::Uint8 g;
    sf::Uint8 b;
    sf::Uint8 a;
};
    rgba *tex = new rgba[texWidth * texHeight];
    for(unsigned int x = 0; x < texWidth; ++x) {
        for(unsigned int y = 0; y < texHeight; ++y) {
            tex[x*texHeight + y].r = 123;
            tex[x*texHeight + y].g = 123;
            tex[x*texHeight + y].b = 123;
            tex[x*texHeight + y].a = 123;
        }
    }

    m_playerTextureBorder.update(reinterpret_cast<sf::Uint8*>(tex));
    m_playerSpriteBorder.setTexture(m_playerTextureBorder);*/
    m_SpriteOverlay.setPosition(getPosition());



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
    sf::Vertex *quad = &m_vertices[(i + j * width) * 4];

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
    target.draw(m_SpriteOverlay, states);
}

void grg::Player::Update(sf::Time elapsed) {
    const float elapsedSeconds = elapsed.asSeconds();
    //bool viewChanged = false;
    //static_cast<void>(viewChanged);

    const float zoomFactor = 1.01F;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        //m_view.zoom(zoomFactor);
        this->scale(zoomFactor, zoomFactor);
        spdlog::info("Player zoom {}, {}.", getScale().x, getScale().y);
        //viewChanged = true;
    } else {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            // m_view.zoom(1.0F / zoomFactor);
            this->scale(1.0F / zoomFactor, 1.0F / zoomFactor);
            spdlog::info("Player zoom {}, {}.", getScale().x, getScale().y);
            //viewChanged = true;
        }
    }


    // scrolling/movement calculations,
    // Todo: this speed/velocity calculation can be generalized + used for W+S above
    {
        constexpr float speedUp = 2.0F;
        constexpr float keyAcceleration = 500.0F * speedUp;

        bool moveKeyPressedVer = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            m_position += {0.0F, 500.0F * elapsedSeconds};
            moveKeyPressedVer = true;
        } else {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                m_position += {0.0F, -500.0F * elapsedSeconds};
                moveKeyPressedVer = true;
            }
        }
        static_cast<void>(moveKeyPressedVer);
        // here the m_yVelocity stuff
        // m_yVelocity *= Velocity::DoCalc(elapsed, m_yVelocity, moveKeyPressedVer);

        bool moveKeyPressedHor = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            m_xVelocity -= speedUp * keyAcceleration * elapsedSeconds;
            moveKeyPressedHor = true;
        } else {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                m_xVelocity += speedUp * keyAcceleration * elapsedSeconds;
                moveKeyPressedHor = true;
            }
        }

        m_xVelocity *= Velocity::DoCalc(elapsed, m_xVelocity, moveKeyPressedHor);
        m_position += {m_xVelocity * elapsedSeconds, 0.0F};
        //this->setOrigin(m_position);
        this->setPosition(m_position);
        //m_playerSpriteBorder.setPosition(m_position);

        //static bool swRGB = false;
        //m_playerSprite.setSrgb(swRGB);
        //swRGB = !swRGB;
        //m_playerSprite.update()

        /*spdlog::info(fmt::format("elapsed time: {:.2f}s, x: {:.1f}, y: {:.1f}, xVelocity: {:.1f},
           speedRamp: {:.3f}",
                elapsed.asSeconds(), m_view.getCenter().x, m_view.getCenter().y, m_xVelocity,
                   speedRamp));*/
        /*spdlog::info(fmt::format("elapsed time: {:.2f}s, x: {:.1f}, y: {:.1f}, xVelocity: {:.1f},
           speedRamp: {:.3f}",
                        elapsed.asSeconds(), m_position.x, m_position.y, m_xVelocity, speedRamp));*/

        /*m_backGround->setString(
                fmt::format("elapsed time: {:.2f}s, x: {:.1f}, y: {:.1f}, xVelocity: {:.1f},
                   speedRamp: {:.3f}",
                        m_totalTime.asSeconds(),
                        m_coord.x, m_coord.y, m_xVelocity, speedRamp));*/
    }
} // grg::Player::Update

const sf::Vector2f &grg::Player::GetPlayerPosition() const {
    return m_position;
}

void grg::Player::SetPlayerPosition(const sf::Vector2f &position) {
    m_position = position;
}

