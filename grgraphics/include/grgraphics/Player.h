/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Player.h class.
 * \file       Player.h
 * \date       2020-04-06
 * \author     Jedzia.
 *
 * modified    2020-04-19, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef OPENGLTEMPLATE_0ACA883A006045E5AB9D1D11863338CF_PLAYER_H
#define OPENGLTEMPLATE_0ACA883A006045E5AB9D1D11863338CF_PLAYER_H

#include "Drawables/SpriteOverlay.h"
#include <grgraphics/Utility/Velocity.h>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>

namespace grg {
class Player : public sf::Drawable,
               public sf::Transformable {
public:

    Player();

    bool Load(const std::string &filename, sf::Vector2u tileSize, const unsigned int* tiles, unsigned int width,
            unsigned int height, float uniformScale = 1.0F);

    void Update(sf::Time elapsed);

    const sf::Vector2f &GetPlayerPosition() const;

    void SetPlayerPosition(const sf::Vector2f &position);

private:

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_playerSprite;
    grg::SpriteOverlay m_spriteOverlay;
    sf::Vector2f m_position;
    grg::Velocity m_velocity{ grg::KeyToDirectionMapping::Wasd() };
};
}

#endif //OPENGLTEMPLATE_0ACA883A006045E5AB9D1D11863338CF_PLAYER_H
