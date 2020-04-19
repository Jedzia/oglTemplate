/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Velocity.h class.
 * \file       Velocity.h
 * \date       2020-04-06
 * \author     Jedzia.
 *
 * modified    2020-04-06, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef OPENGLTEMPLATE_5B7B328397E344C48AC977D5E169E5C5_VELOCITY_H
#define OPENGLTEMPLATE_5B7B328397E344C48AC977D5E169E5C5_VELOCITY_H

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

namespace grg {
class Velocity {
public:

    static float DoCalc(const sf::Time& elapsed, float& velocity, bool moveKeyPressed);
    static sf::Vector2f DoCalc(const sf::Time& elapsed, sf::Vector2f& velocity, bool xMoveKeyPressed, bool yMoveKeyPressed);

    void DoUpdate(sf::Time elapsed);

    const sf::Vector2f &GetVelocity() const;
    void SetVelocity(const sf::Vector2f &velocity);
    const sf::Vector2f &GetPosition() const;
    void SetPosition(const sf::Vector2f &position);

  private:
    sf::Vector2f m_velocity{ 0, 0 };
    sf::Vector2f m_position{ 0, 0 };
    //float m_lastAbsVelocity = 0;
};
}

#endif //OPENGLTEMPLATE_5B7B328397E344C48AC977D5E169E5C5_VELOCITY_H
