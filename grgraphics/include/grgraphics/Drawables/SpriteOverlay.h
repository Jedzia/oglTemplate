/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the SpriteOverlay.h class.
 * \file       SpriteOverlay.h
 * \date       2020-04-08
 * \author     Jedzia.
 *
 * modified    2020-04-08, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef OPENGLTEMPLATE_10669B502CC44940B381173DAC702560_SPRITEOVERLAY_H
#define OPENGLTEMPLATE_10669B502CC44940B381173DAC702560_SPRITEOVERLAY_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace grg {
class SpriteOverlay : public sf::Drawable,
                      public sf::Transformable {
public:
    //SpriteOverlay(const unsigned int width, const unsigned int height);
    void Initialize(const unsigned int width, const unsigned int height);

private:

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::Texture m_playerTextureBorder;
    sf::Sprite m_playerSpriteBorder;

};
}

#endif //OPENGLTEMPLATE_10669B502CC44940B381173DAC702560_SPRITEOVERLAY_H
