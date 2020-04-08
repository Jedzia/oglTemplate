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
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>

namespace grg {
class SpriteOverlay : public sf::Drawable,
                      public sf::Transformable {
public:
    struct Rgba {
        sf::Uint8 m_r;
        sf::Uint8 m_g;
        sf::Uint8 m_b;
        sf::Uint8 m_a;
    };

    void Initialize(const unsigned int width, const unsigned int height);

    virtual void Update(sf::Time elapsed);

private:

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void switchState(bool state);

    Rgba* m_tex1;
    Rgba* m_tex2;
    bool m_isInitialized = false;
    sf::Texture m_playerTextureBorder;
    sf::Sprite m_playerSpriteBorder;
    sf::Time m_totalTime;
    bool m_state = false;
};
}

#endif //OPENGLTEMPLATE_10669B502CC44940B381173DAC702560_SPRITEOVERLAY_H
