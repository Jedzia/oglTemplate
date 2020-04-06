/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Camera.h class.
 * \file       Camera.h
 * \date       2020-04-06
 * \author     Jedzia.
 *
 * modified    2020-04-06, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef OPENGLTEMPLATE_3BAEF6E068CA4ECEA3FF4A45D6DDF3C2_CAMERA_H
#define OPENGLTEMPLATE_3BAEF6E068CA4ECEA3FF4A45D6DDF3C2_CAMERA_H
#include "Player.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>

namespace grg {
class Camera {
public:

    Camera(const Player &player, sf::RenderWindow &window);

    void UpdateView(sf::Time elapsed);

private:

    const Player &m_player;
    sf::RenderWindow &m_window;
    //sf::View m_view;
};
}

#endif //OPENGLTEMPLATE_3BAEF6E068CA4ECEA3FF4A45D6DDF3C2_CAMERA_H
