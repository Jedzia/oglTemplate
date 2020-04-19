/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Velocity.cpp class.
 * \file       Velocity.cpp
 * \date       2020-04-06
 * \author     Jedzia.
 *
 * modified    2020-04-06, Jedzia
 */
/*---------------------------------------------------------*/
#include "grgraphics/Utility/Velocity.h"
#include <algorithm>

float grg::Velocity::DoCalc(const sf::Time &elapsed, float &velocity, bool moveKeyPressed) {
    const float elapsedSeconds = elapsed.asSeconds();
    constexpr float speedUp = 2.0F;

    const float absVelocity = std::abs(velocity);
    float speedRamp = 1.0F - elapsedSeconds * speedUp;
    if(!moveKeyPressed) {
        constexpr float slowDown = 1.4F * speedUp;
        speedRamp = 1.0F - elapsedSeconds * slowDown;
        constexpr float hysteresisEdge = 50.0F * slowDown;     // lower edge when friction
        // starts to decrease velocity abrupt.
        if(absVelocity < hysteresisEdge) {
            speedRamp = 1.0F -
                        ((elapsedSeconds * slowDown * 1.0F) +
                         (0.01F * ((hysteresisEdge / 10.0F) - (absVelocity / (hysteresisEdge / 5.0F)))));
            if(absVelocity < (0.5F)) {
                // stop all movement at 1% of the hysteresis low point.
                velocity = 0;
            }
        }
    }

    return speedRamp;

    //m_csvFile.WriteData(m_xVelocity);
    // -> grcore::writeTelemetryData(static_cast<double>(m_xVelocity));
} // grg::Velocity

sf::Vector2f grg::Velocity::DoCalc(const sf::Time &elapsed, sf::Vector2f &velocity, bool xMoveKeyPressed, bool yMoveKeyPressed) {
    return sf::Vector2f(
            velocity.x * grg::Velocity::DoCalc(elapsed, velocity.x, xMoveKeyPressed),
            velocity.y * grg::Velocity::DoCalc(elapsed, velocity.y, yMoveKeyPressed)
            );
}

void grg::Velocity::DoUpdate(sf::Time elapsed) {
    const float elapsedSeconds = elapsed.asSeconds();
    constexpr float speedUp = 2.0F;
    constexpr float keyAcceleration = 500.0F * speedUp;

    bool horizontalMoveKeyPressed = false;
    if(m_keyMapping == Direction::Left) {
        m_velocity.x -= speedUp * keyAcceleration * elapsedSeconds;
        horizontalMoveKeyPressed = true;
    } else {
        if(m_keyMapping == Direction::Right) {
            m_velocity.x += speedUp * keyAcceleration * elapsedSeconds;
            horizontalMoveKeyPressed = true;
        }
    }

    bool verticalMoveKeyPressed = false;
    if(m_keyMapping == Direction::Up) {
        m_velocity.y -= speedUp * keyAcceleration * elapsedSeconds;
        verticalMoveKeyPressed = true;
    } else {
        if(m_keyMapping == Direction::Down) {
            m_velocity.y += speedUp * keyAcceleration * elapsedSeconds;
            verticalMoveKeyPressed = true;
        }
    }

    m_velocity = grg::Velocity::DoCalc(elapsed, m_velocity, horizontalMoveKeyPressed, verticalMoveKeyPressed);
    m_position += m_velocity * elapsedSeconds;
} // grg::Velocity

const sf::Vector2f &grg::Velocity::GetVelocity() const {
    return m_velocity;
}

[[maybe_unused]] void grg::Velocity::SetVelocity(const sf::Vector2f &velocity) {
    m_velocity = velocity;
}

const sf::Vector2f &grg::Velocity::GetPosition() const {
    return m_position;
}

[[maybe_unused]] void grg::Velocity::SetPosition(const sf::Vector2f &position) {
    m_position = position;
}

grg::Velocity::Velocity(const grg::KeyToDirectionMapping &keyMapping) : m_keyMapping(keyMapping) {}

grg::KeyToDirectionMapping::KeyToDirectionMapping(const std::array<sf::Keyboard::Key, 4> &aMapping) : m_aMapping(aMapping) {}

grg::KeyToDirectionMapping::KeyToDirectionMapping() : m_aMapping(
{
    sf::Keyboard::Up,
    sf::Keyboard::Right,
    sf::Keyboard::Down,
    sf::Keyboard::Left
}) {}

bool grg::KeyToDirectionMapping::operator==(const grg::Direction &dir) const {
    return sf::Keyboard::isKeyPressed(m_aMapping[dir]);
}

bool grg::KeyToDirectionMapping::IsKeyPressed(const grg::Direction &dir) const {
    return sf::Keyboard::isKeyPressed(m_aMapping[dir]);
}

const grg::KeyToDirectionMapping &grg::KeyToDirectionMapping::Default() {
    static KeyToDirectionMapping defaultMapping;
    return defaultMapping;
}

const grg::KeyToDirectionMapping &grg::KeyToDirectionMapping::WASD() {
    static KeyToDirectionMapping defaultMapping(
    {
        sf::Keyboard::W,
        sf::Keyboard::D,
        sf::Keyboard::S,
        sf::Keyboard::A
    });

    return defaultMapping;
}
