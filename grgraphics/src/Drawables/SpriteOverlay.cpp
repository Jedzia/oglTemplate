//
// Created by Jedzia on 08.04.2020.
//

#include "grcore/warning/FMT_format_log.h"
#include "grgraphics/warning/SFML_Graphics.h"
//
#include "grgraphics/Drawables/SpriteOverlay.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

void grg::SpriteOverlay::Initialize(const unsigned int width, const unsigned int height) {
    const unsigned int texWidth = width;
    const unsigned int texHeight = height;
    //const unsigned int texWidth = 128;
    //const unsigned int texHeight = 128;
    m_playerTextureBorder.create(texWidth, texHeight);

    //sf::Uint8 tex[m_playerSprite.getSize().x * m_playerSprite.getSize().y];
    //std::vector<sf::Uint8> tex(m_playerSprite.getSize().x * m_playerSprite.getSize().y);
    /*std::vector<sf::Uint8> *tex = new std::vector<sf::Uint8>(m_playerSprite.getSize().x *
       m_playerSprite.getSize().y);
       for(unsigned int x = 0; x < m_playerSprite.getSize().x; ++x) {
        for(unsigned int y = 0; y < m_playerSprite.getSize().y; ++y) {
            (*tex)[x*m_playerSprite.getSize().x + y] = 123;
        }
       }

       m_playerTextureBorder.update((*tex).data());*/
    //sf::Uint8 tex[128 * 128];
    m_tex1 = new Rgba[texWidth * texHeight];
    m_tex2 = new Rgba[texWidth * texHeight];

    for(unsigned int x = 0; x < texWidth; ++x) {
        for(unsigned int y = 0; y < texHeight; ++y) {
            m_tex1[x * texHeight + y].m_r = 123;
            m_tex1[x * texHeight + y].m_g = 123;
            m_tex1[x * texHeight + y].m_b = 123;
            m_tex1[x * texHeight + y].m_a = 123;

            m_tex2[x * texHeight + y].m_r = 233;
            m_tex2[x * texHeight + y].m_g = 233;
            m_tex2[x * texHeight + y].m_b = 233;
            m_tex2[x * texHeight + y].m_a = 233;
        }
    }
    m_playerTextureBorder.update(reinterpret_cast<sf::Uint8 *>(m_tex1));
    m_playerSpriteBorder.setTexture(m_playerTextureBorder);
    m_playerSpriteBorder.setPosition(getPosition());
    m_isInitialized = true;
} // grg::SpriteOverlay::Initialize

void grg::SpriteOverlay::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if(!m_isInitialized) {
        return;
    }

    // apply the transform
    states.transform *= getTransform();

    target.draw(m_playerSpriteBorder, states);
}

void grg::SpriteOverlay::Update(sf::Time elapsed) {
    m_totalTime += elapsed;
    const uint8_t elapsedUint = static_cast<uint8_t>(m_totalTime.asSeconds());
    switchState(elapsedUint % 2 == 0);
}

void grg::SpriteOverlay::switchState(bool state) {
    if(state && !m_state) {
        spdlog::trace("grg::SpriteOverlay Switch <m_tex1> state from {} to {}.", m_state, state);
        m_playerTextureBorder.update(reinterpret_cast<sf::Uint8 *>(m_tex1));
        m_state = true;
    } else if(!state && m_state) {
        spdlog::trace("grg::SpriteOverlay Switch <m_tex2> state from {} to {}.", m_state, state);
        m_playerTextureBorder.update(reinterpret_cast<sf::Uint8 *>(m_tex2));
        m_state = false;
    }
}
