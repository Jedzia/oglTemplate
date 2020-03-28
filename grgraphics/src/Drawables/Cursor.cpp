/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Cursor.cpp class.
 * \file       Cursor.cpp
 * \date       2020-03-28
 * \author     Jedzia.
 *
 * modified    2020-03-28, Jedzia
 */
/*---------------------------------------------------------*/

#include "grgraphics/Drawables/Cursor.h"
#include "grgraphics/warning/FMT_format.h"
#include "grgraphics/warning/SFML_Graphics.h"
#include <array>
#include <iostream>
#include <vector>

struct grg::Cursor::Impl {
    Impl(sf::RenderWindow &window, const sf::Font &font) : m_window(window) {/*, m_font(font)*/
        std::cout << "+++ Constructor " << __PRETTY_FUNCTION__ << " called. +++" << std::endl;

        if(m_cursor.loadFromSystem(sf::Cursor::Hand)) {
            window.setMouseCursor(m_cursor);
        }

        const float radius = m_circle.getRadius();
        m_circle.setOrigin(radius, radius);
        m_circle.setFillColor(sf::Color::Transparent);
        m_circle.setOutlineColor(sf::Color::Red);
        m_circle.setOutlineThickness(2.F);

        UpdateCross(radius, sf::Vector2f());

        m_coordDisplay = sf::Text("Coords: ", font);
    }

    void UpdateCross(const float radius, sf::Vector2f translation) {
        //auto xxx = translation / 2.0F;
        // cross is 90 % of outline/radius
        auto drawRadius = radius * 90.0F / 100.F; //
        m_cross[0].position = sf::Vector2f(0, -drawRadius) + translation;
        m_cross[1].position = sf::Vector2f(0, drawRadius) + translation;
        m_cross[2].position = sf::Vector2f(-drawRadius, 0) + translation;
        m_cross[3].position = sf::Vector2f(drawRadius, 0) + translation;
    }

    ~Impl() {
        std::cout << "+++ Destructor  " << __PRETTY_FUNCTION__ << " called. +++" << std::endl;
    }

    void Update(sf::Time elapsed) {
        static_cast<void>(elapsed);

        // get the local mouse position (relative to a window)
        const sf::Vector2i localPosition = sf::Mouse::getPosition(m_window);

        if(m_lastPosition != localPosition) {
            const sf::Vector2f localPositionF {static_cast<float>(localPosition.x), static_cast<float>(localPosition.y)};
            m_rect.setPosition(localPositionF);
            //m_circle.center
            m_circle.setPosition(localPositionF);
            UpdateCross(m_circle.getRadius(), localPositionF);
            m_coordDisplay.setString(fmt::format("Coords: x({}), y({})", localPosition.x, localPosition.y));
            auto bounds = m_coordDisplay.getLocalBounds();
            //m_coordDisplay.setPosition(localPositionF + sf::Vector2f { -100.F, 50.F});
            m_coordDisplay.setPosition(localPositionF + sf::Vector2f { 00.F, + bounds.getSize().y + m_circle.getRadius()}
                    -(bounds.getSize() / 2.0F));

            m_circle.setOutlineColor(sf::Color::Red);
            m_redrawn = true;
        } else {
            m_circle.setOutlineColor(sf::Color::Green);
            m_redrawn = false;
        }

        m_lastPosition = localPosition;
    } // Update

    void  Draw(sf::RenderTarget &target, sf::RenderStates states) const {
        //target.draw(m_rect, states);
        target.draw(m_circle, states);
        target.draw(m_cross, states);
        target.draw(m_coordDisplay, states);
    }

private:

    sf::RenderWindow &m_window;
    sf::Cursor m_cursor;
    sf::RectangleShape m_rect {sf::Vector2f(20, 20)};
    sf::CircleShape m_circle {40, 24};
    sf::VertexArray m_cross {sf::PrimitiveType::Lines, 4};
    //const sf::Font &m_font;
    sf::Text m_coordDisplay;
    sf::Vector2i m_lastPosition;
    bool m_redrawn = false;
};
void grg::Cursor::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    m_pImpl->Draw(target, states);
}

grg::Cursor::Cursor(sf::RenderWindow &window, const sf::Font &font) : m_pImpl(std::make_unique<grg::Cursor::Impl>(window, font)) {}

grg::Cursor::~Cursor() {}

void grg::Cursor::Update(sf::Time elapsed) {
    m_pImpl->Update(elapsed);
}
