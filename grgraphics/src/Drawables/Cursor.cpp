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
    Impl(sf::RenderWindow &window, const sf::Font &font) : m_window(window) { /*, m_font(font)*/
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

        m_coordDisplay1 = sf::Text("Coords: ", font);
        m_coordDisplay2 = sf::Text("View  : ", font);
    }

    void UpdateCross(const float radius, sf::Vector2f translation) {
        //auto xxx = translation / 2.0F;
        // cross is 90 % of outline/radius
        auto drawRadius = radius * 90.0F / 100.F;//
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

        const sf::Vector2f globalPositionF = m_window.mapPixelToCoords(localPosition);
        const sf::Vector2f localPositionF { static_cast<float>(localPosition.x), static_cast<float>(localPosition.y) };
        const sf::Vector2f drawPositionF = globalPositionF;
        auto bounds = m_coordDisplay1.getLocalBounds();
        //m_coordDisplay1.setPosition(localPositionF + sf::Vector2f { -100.F, 50.F});
        auto position = drawPositionF + sf::Vector2f { 00.F, +bounds.getSize().y + m_circle.getRadius() }
                        -(bounds.getSize() / 2.0F);

        if(m_lastPosition != localPosition) {
            m_rect.setPosition(drawPositionF);
            //m_circle.center
            m_circle.setPosition(drawPositionF);
            UpdateCross(m_circle.getRadius(), drawPositionF);
            m_coordDisplay1.setString(fmt::format("Coords: x({}), y({}) - x({:.1f}), y({:.1f})", localPosition.x, localPosition.y, globalPositionF.x, globalPositionF.y));
            m_coordDisplay1.setPosition(position);

            m_circle.setOutlineColor(sf::Color::Red);
            m_redrawn = true;
        } else {
            m_circle.setOutlineColor(sf::Color::Green);
            m_redrawn = false;
        }

        //auto viewportSize = m_window.getView().getViewport().getSize();
        auto viewSize = m_window.getView().getSize();
        m_coordDisplay2.setString(fmt::format("View  : x({:.1f}), y({:.1f})", viewSize.x, viewSize.y));
        m_coordDisplay2.setPosition(position + sf::Vector2f { 00.F, m_coordDisplay2.getLocalBounds().getSize().y});

        m_lastPosition = localPosition;
    }// Update

    void Draw(sf::RenderTarget &target, sf::RenderStates states) const {
        //target.draw(m_rect, states);
        target.draw(m_circle, states);
        target.draw(m_cross, states);
        target.draw(m_coordDisplay1, states);
        target.draw(m_coordDisplay2, states);
    }

private:

    //const sf::Font &m_font;
    bool m_redrawn = false;
    sf::CircleShape m_circle { 40, 24 };
    sf::Cursor m_cursor;
    sf::RectangleShape m_rect { sf::Vector2f(20, 20) };
    sf::RenderWindow &m_window;
    sf::Text m_coordDisplay1;
    sf::Text m_coordDisplay2;
    sf::Vector2i m_lastPosition;
    sf::VertexArray m_cross { sf::PrimitiveType::Lines, 4 };
};
void grg::Cursor::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    m_pImpl->Draw(target, states);
}

grg::Cursor::Cursor(sf::RenderWindow &window, const sf::Font &font) : m_pImpl(std::make_unique<grg::Cursor::Impl>(window, font)) {}

grg::Cursor::~Cursor() {}

void grg::Cursor::Update(sf::Time elapsed) {
    m_pImpl->Update(elapsed);
}
