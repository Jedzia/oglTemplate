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
#include "grgraphics/warning/SFML_Graphics.h"
#include <array>
#include <iostream>
#include <vector>

struct grg::Cursor::Impl {
    Impl(sf::RenderWindow &window) : m_window(window) {
        std::cout << "+++ Constructor " << __PRETTY_FUNCTION__ << " called. +++" << std::endl;

        if(m_cursor.loadFromSystem(sf::Cursor::Hand)) {
            window.setMouseCursor(m_cursor);
        }
    }

    ~Impl() {
        std::cout << "+++ Destructor  " << __PRETTY_FUNCTION__ << " called. +++" << std::endl;
    }

    void Update(sf::Time elapsed) {
        static_cast<void>(elapsed);

        // get the local mouse position (relative to a window)
        sf::Vector2i localPosition = sf::Mouse::getPosition(m_window);
        m_rect.setPosition(static_cast<float>(localPosition.x), static_cast<float>(localPosition.y));
    }

    void  Draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(m_rect, states);
        //static_cast<void>(target);
        //static_cast<void>(states);
    }

private:

    sf::RenderWindow &m_window;
    sf::Cursor m_cursor;
    sf::RectangleShape m_rect {sf::Vector2f(20, 20)};
};
void grg::Cursor::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    m_pImpl->Draw(target, states);
}

grg::Cursor::Cursor(sf::RenderWindow &window) : m_pImpl(std::make_unique<grg::Cursor::Impl>(window)) {}

grg::Cursor::~Cursor() {}

void grg::Cursor::Update(sf::Time elapsed) {
    m_pImpl->Update(elapsed);
}
