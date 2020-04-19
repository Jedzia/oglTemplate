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
#include <grgraphics/Utility/VectorUtil.h>
//
#include "grgraphics/Camera.h"

grg::Camera::Camera(const grg::Player &player, sf::RenderWindow &window) : m_player(player), m_window(window) {}

void grg::Camera::UpdateView(sf::Time /*elapsed*/) {
    //static_cast<void>(elapsed);
    //static_cast<void>(m_window);
    //static_cast<void>(m_player);

    auto view = m_window.getView();
    //m_view.move(m_xVelocity * elapsedSeconds, 0.0F);

    bool viewChanged = false;

    {// zoom
        const float zoomFactor = 1.01F;
        //if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                spdlog::info("View zoom {}, {}.", view.getSize().x, view.getSize().y);
                view.zoom(1.0F / zoomFactor);
                viewChanged = true;
            } else {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
                    spdlog::info("View zoom {}, {}.", view.getSize().x, view.getSize().y);
                    view.zoom(zoomFactor);
                    viewChanged = true;
                }
            }
        //}
    }

    {// Set camera from player position.
        sf::Vector2f cameraTranslation{ 0.0F, 0.0F };
        const auto position = m_player.GetPlayerPosition() + cameraTranslation;

        const auto lines = 1;
        const auto padLeft = 120.0F;
        const auto padTop = 120.0F;
        const auto padWidth = 120.0F;
        const auto padHeight = 120.0F;
        const auto boundsX = 0.0F;
        const auto boundsY = 0.0F;
        const auto restrictedPosition =
            restrict (position,
                      { padLeft, padTop, static_cast<float>(m_window.getSize().x) - padWidth - boundsX,
                        static_cast<float>(m_window.getSize().y) - padHeight - boundsY * lines });

        static_cast<void>(restrictedPosition);
//        view.setCenter(restrictedPosition);

        //if(viewChanged || m_window.getView().getTransform() != view.getTransform()) {
        //spdlog::info("m_window.setView Center x{}, y{}.", view.getCenter().x,
        // view.getCenter().y);

        m_window.setView(view);
        static_cast<void>(viewChanged); // ToDo: masked out

        //}
    }
}// grg::Camera::UpdateView

sf::Vector2f grg::Camera::GetScreenCoords(const sf::Vector2f &worldCoordinates) {
    const sf::Vector2i screenCoordsI = m_window.mapCoordsToPixel(worldCoordinates);
    const sf::Vector2f screenCoordsF(static_cast<float>(screenCoordsI.x), static_cast<float>(screenCoordsI.y));
    return screenCoordsF;
}

sf::Vector2f grg::Camera::GetRelativeWorldCoords(const sf::Vector2i &screenCoordinates) {
    const sf::Vector2f worldCoordsF = m_window.mapPixelToCoords(screenCoordinates);
    //const sf::Vector2f worldCoordsF(static_cast<float>(worldCoordsI.x),
    // static_cast<float>(worldCoordsI.y));
    const sf::Vector2f screensizeHalf =
        (sf::Vector2f(static_cast<float>(m_window.getSize().x), static_cast<float>(m_window.getSize().y)) / 2.0F);
    const sf::Vector2f relF = worldCoordsF - screensizeHalf;
    const float resultX = relF.x / screensizeHalf.x;
    const float resultY = -relF.y / screensizeHalf.y;

    return { resultX, resultY };
}
