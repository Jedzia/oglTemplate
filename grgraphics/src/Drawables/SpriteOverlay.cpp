//
// Created by Jedzia on 08.04.2020.
//

#include "grcore/warning/FMT_format_log.h"
#include "grgraphics/warning/SFML_Graphics.h"
//
#include "grgraphics/Drawables/SpriteOverlay.h"

void grg::SpriteOverlay::Initialize(const unsigned int width, const unsigned int height) {
    const unsigned int texWidth = width;
    const unsigned int texHeight =  height;
    //const unsigned int texWidth = 128;
    //const unsigned int texHeight = 128;
    m_playerTextureBorder.create(texWidth, texHeight);

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
    struct rgba {
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
    m_playerSpriteBorder.setTexture(m_playerTextureBorder);
    m_playerSpriteBorder.setPosition(getPosition());
}

void grg::SpriteOverlay::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    target.draw(m_playerSpriteBorder, states);
}

