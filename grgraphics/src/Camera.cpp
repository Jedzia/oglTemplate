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
#include "grgraphics/warning/SFML_Graphics.h"
#include "grcore/warning/FMT_format_log.h"
//
#include "grgraphics/Camera.h"

grg::Camera::Camera(const grg::Player &player, sf::RenderWindow &window) : m_player(player), m_window(window) {}

void grg::Camera::UpdateView(sf::Time elapsed) {
    static_cast<void>(elapsed);
    static_cast<void>(m_window);
    static_cast<void>(m_player);

    auto view = m_window.getView();
    //m_view.move(m_xVelocity * elapsedSeconds, 0.0F);

    // Here a camera should do its work
    view.setCenter(m_player.GetPlayerPosition() + sf::Vector2f {0.0F, 0.0F});

    //if(viewChanged || m_window->getView().getTransform() != m_view.getTransform()) {
    m_window.setView(view);
    //}
}
