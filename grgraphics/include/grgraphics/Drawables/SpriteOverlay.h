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
#include <experimental/propagate_const>
#include <memory>

namespace grg {
class SpriteOverlay : public sf::Drawable,
                      public sf::Transformable {
public:

// FOR FUCKS SAKE, this is BULLSHIT!
/*#if defined(__GNUC__) && defined(WARNINGS_SKIP_TEMPORARY)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wpragmas"
//#pragma GCC diagnostic ignored "-Werror=unknown-pragmas"
#endif
#if defined(__clang__) && defined(WARNINGS_SKIP_TEMPORARY)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#endif
#pragma ide diagnostic ignored "OCInconsistentNamingInspection"*/
    struct PixelRGBA {
        sf::Uint8 m_r;
        sf::Uint8 m_g;
        sf::Uint8 m_b;
        sf::Uint8 m_a;
    };
/*#if defined(__GNUC__) && defined(WARNINGS_SKIP_TEMPORARY)
#pragma GCC diagnostic pop
#endif
#if defined(__clang__) && defined(WARNINGS_SKIP_TEMPORARY)
#pragma clang diagnostic pop
#endif*/

    SpriteOverlay();

    virtual ~SpriteOverlay();

    void Initialize(const unsigned int width, const unsigned int height, float uniformScale);

    virtual void Update(sf::Time elapsed, const sf::Transformable &t);

private:

    struct Impl;
    std::experimental::propagate_const<std::unique_ptr<Impl>> m_pImpl;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void switchState(bool state);

    PixelRGBA* m_tex1;
    PixelRGBA* m_tex2;
    bool m_isInitialized = false;
    sf::Texture m_playerTextureBorder;
    sf::Sprite m_playerSpriteBorder;
    sf::Time m_totalTime;
    bool m_state = false;
};
}

#endif //OPENGLTEMPLATE_10669B502CC44940B381173DAC702560_SPRITEOVERLAY_H
