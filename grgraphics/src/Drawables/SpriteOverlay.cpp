//
// Created by Jedzia on 08.04.2020.
//

#include "grcore/warning/FMT_format_log.h"
#include "grgraphics/warning/SFML_Graphics.h"
//
#include "grgraphics/Drawables/SpriteOverlay.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <grcore/Resource.h>
#include <grgraphics/Constants.h>

struct grg::SpriteOverlay::Impl {
    void Init(const unsigned int width, const unsigned int height, float uniformScale) {
        m_width = width;
        m_height = height;
        spdlog::trace("grg::SpriteOverlay Init width={}, height={}.", m_width, m_height);

        auto [data, size, error] = m_resource.Get();
        if(error != 0) {
            //throw std::runtime_error(fmt::format("[{}] Loading Font Resource({}) failed: {}",
            // __PRETTY_FUNCTION__,
            //                m_resource.GetId(), error));
            spdlog::error("[{}] Loading Font Resource({}) failed: {}", __PRETTY_FUNCTION__, m_resource.GetId(), error);
            return;
        }

        bool success = m_debugFont.loadFromMemory(data, size);
        if(success) {
            auto fi = m_debugFont.getInfo();
            spdlog::debug("[{}] Loaded Font from resource (id={}): '{}'.", __PRETTY_FUNCTION__, m_resource.GetId(),
                    fi.family);
        } else {
            spdlog::error("[{}] ERROR loading Font from resource (id={}).", __PRETTY_FUNCTION__,
                    m_resource.GetId());
        }

        //const unsigned int fontSize = static_cast<unsigned int>(static_cast<float>(
        // Debug_Font_Character_Size) * uniformScale);
        //static_cast<void>(uniformScale);
        const unsigned int fontSize = Debug_Font_Character_Size;
        const float scaleFactor = 1.0F / uniformScale;
        spdlog::warn("grg::SpriteOverlay scaleFactor={}, fontSize={}.", scaleFactor, fontSize);
        m_coordDisplay1 = sf::Text("Size: ", m_debugFont, fontSize);
        m_coordDisplay1.scale({scaleFactor, scaleFactor});
        float offsetY = (static_cast<float>(m_height) / 1.2F) + m_coordDisplay1.getGlobalBounds().getSize().y * 1.1F;
        m_coordDisplay1.move(0, offsetY);
        m_coordDisplay2 = sf::Text("Pos : ", m_debugFont, fontSize);
        m_coordDisplay2.scale({scaleFactor, scaleFactor});
        offsetY += m_coordDisplay2.getGlobalBounds().getSize().y * 1.1F;
        m_coordDisplay2.move(0, offsetY);

        m_initialized = true;
    } // Init

    void Update(sf::Time, const sf::Transformable &sprite) {
        //auto size = sprite.getGlobalBounds();
        //m_coordDisplay1.setString(fmt::format("Size: x({:.1f}), y({:.1f})", size.getSize().x, size.getSize().y));
        auto scale = sprite.getScale();
        m_coordDisplay1.setString(fmt::format("Scale: x({:.1f}), y({:.1f})", scale.x, scale.y));

        auto position = sprite.getPosition();
        m_coordDisplay2.setString(fmt::format("Pos : x({:.1f}), y({:.1f})", position.x, position.y));
        //m_coordDisplay1.setPosition(textPositionF + sf::Vector2f { 00.F,
        // m_coordDisplay2.getLocalBounds().getSize().y });
    }

    void Draw(sf::RenderTarget &target, sf::RenderStates states) const {
        if(!m_initialized)
            return;

        target.draw(m_coordDisplay1, states);
        target.draw(m_coordDisplay2, states);
    }

private:

    grcore::Resource m_resource {129};
    sf::Font m_debugFont;
    sf::Text m_coordDisplay1;
    sf::Text m_coordDisplay2;
    bool m_initialized = false;
    unsigned int m_width;
    unsigned int m_height;
};

void grg::SpriteOverlay::Initialize(const unsigned int width, const unsigned int height, float uniformScale) {
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
    m_tex1 = new PixelRGBA[texWidth * texHeight];
    m_tex2 = new PixelRGBA[texWidth * texHeight];

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
    m_pImpl->Init(texWidth, texHeight, uniformScale);

    m_isInitialized = true;
} // grg::SpriteOverlay::Initialize

void grg::SpriteOverlay::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if(!m_isInitialized) {
        return;
    }

    // apply the transform
    states.transform *= getTransform();

    target.draw(m_playerSpriteBorder, states);
    m_pImpl->Draw(target, states);
}

void grg::SpriteOverlay::Update(sf::Time elapsed, const sf::Transformable &t) {
    m_totalTime += elapsed;
    //m_pImpl->Update(elapsed, *this);
    m_pImpl->Update(elapsed, t);
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

grg::SpriteOverlay::SpriteOverlay() : m_pImpl(std::make_unique<grg::SpriteOverlay::Impl>()) {}

grg::SpriteOverlay::~SpriteOverlay() {}
