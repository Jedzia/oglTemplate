/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Camera.cpp class.
 * \file       Camera.cpp
 * \date       2020-04-06
 * \author     Jedzia.
 *
 * modified    2020-04-06, Jedzia
 */
/*---------------------------------------------------------*/
#include "grcore/warning/FMT_format_log.h"
#include "grgraphics/warning/SFML_Graphics.h"
//
#include "grgraphics/Camera.h"

grg::Camera::Camera(const grg::Player &player, sf::RenderWindow &window) : m_player(player), m_window(window) {}

void grg::Camera::UpdateView(sf::Time elapsed) {
    static_cast<void>(elapsed);
    static_cast<void>(m_window);
    static_cast<void>(m_player);

    auto view = m_window.getView();
    //m_view.move(m_xVelocity * elapsedSeconds, 0.0F);

    bool viewChanged = false;

    { // zoom
        const float zoomFactor = 1.01F;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            view.zoom(zoomFactor);
            spdlog::info("View zoom {}, {}.", view.getSize().x, view.getSize().y);
            viewChanged = true;
        } else {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                view.zoom(1.0F / zoomFactor);
                spdlog::info("View zoom {}, {}.", view.getSize().x, view.getSize().y);
                viewChanged = true;
            }
        }
    }

    { // Set camera from player position.
        sf::Vector2f cameraTranslation{0.0F, 0.0F};
        view.setCenter(m_player.GetPlayerPosition() + cameraTranslation);

        if(viewChanged || m_window.getView().getTransform() != view.getTransform()) {
            //spdlog::info("m_window.setView Center x{}, y{}.", view.getCenter().x, view.getCenter().y);
            m_window.setView(view);
        }
    }
} // grg::Camera::UpdateView
