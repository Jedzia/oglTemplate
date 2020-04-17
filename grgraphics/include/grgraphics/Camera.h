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
 * modified    2020-04-17, Jedzia
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

    /** Constructs a player bound camera.
     *
     * @param player Player that controls the camera
     * @param window Display windows. A View is used to drive it.
     */
    Camera(const Player &player, sf::RenderWindow &window);

    void UpdateView(sf::Time elapsed);

    /** Get screen coordinates from world coordinates
     *
     * The current view transformations are used to calculate the coordinates.
     * @param worldCoordinates World coordinates to calculate the screen pixels from.
     * @return the screen coordinates of the provided world coordinates.
     */
    sf::Vector2f GetScreenCoords(const sf::Vector2f &worldCoordinates);

    /** Get relative coordinates in world-space
     *
     * @code
     *           +1.0
     *            ^
     *            |
     * -1.0 <-- MIDDLE --> +1.0
     *            |
     *            V
     *           -1.0
     * @endcode
     * +1.0 reflects the screen width / 2 to the right and in the vertical direction
     * the screen height / 2 negated. So 0.0/0.0 represents always the middle of the screen.
     *
     * The current view transformations are used to calculate the coordinates.
     *
     * @param screenCoordinates Pixel x and y input.
     * @return the unit vectorized world coordinates.
     */
    sf::Vector2f GetRelativeWorldCoords(const sf::Vector2i &screenCoordinates);

private:

    const Player &m_player;
    sf::RenderWindow &m_window;
};
}

#endif //OPENGLTEMPLATE_3BAEF6E068CA4ECEA3FF4A45D6DDF3C2_CAMERA_H
