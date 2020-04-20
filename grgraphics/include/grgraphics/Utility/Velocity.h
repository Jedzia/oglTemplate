/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             velocity related calculations.
 * \file       Velocity.h
 * \date       2020-04-06
 * \author     Jedzia.
 *
 * modified    2020-04-19, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef OPENGLTEMPLATE_5B7B328397E344C48AC977D5E169E5C5_VELOCITY_H
#define OPENGLTEMPLATE_5B7B328397E344C48AC977D5E169E5C5_VELOCITY_H

#include <array>
#include <grgraphics/Math.h>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace grg {
/**
 * @brief Configuration that associates keys with directions.
 */
class KeyToDirectionMapping {
public:

    static const KeyToDirectionMapping &Default();

    static const KeyToDirectionMapping &Wasd();

    bool operator==(const Direction &dir) const;

    [[nodiscard]] bool IsKeyPressed(const Direction &dir) const;

    explicit KeyToDirectionMapping(const std::array<sf::Keyboard::Key, 4> &aMapping);

private:

    KeyToDirectionMapping();
    std::array<sf::Keyboard::Key, 4> m_aMapping;
};

typedef KeyToDirectionMapping Ktd;

class Velocity {
public:

    [[nodiscard]] static float DoCalc(const sf::Time &elapsed, float &velocity, bool moveKeyPressed);

    [[nodiscard]] static sf::Vector2f DoCalc(const sf::Time &elapsed, sf::Vector2f &velocity, bool xMoveKeyPressed, bool yMoveKeyPressed);

    explicit Velocity(const KeyToDirectionMapping &keyMapping = KeyToDirectionMapping::Default());

    const sf::Vector2<float> &DoUpdate(sf::Time elapsed);

    [[nodiscard]] const sf::Vector2f &GetVelocity() const;

    [[maybe_unused]] void SetVelocity(const sf::Vector2f &velocity);

    [[nodiscard]] const sf::Vector2f &GetPosition() const;

    [[maybe_unused]] void SetPosition(const sf::Vector2f &position);

private:

    sf::Vector2f m_velocity{ 0, 0 };
    sf::Vector2f m_position{ 0, 0 };
    KeyToDirectionMapping m_keyMapping;
};
}

#endif //OPENGLTEMPLATE_5B7B328397E344C48AC977D5E169E5C5_VELOCITY_H
