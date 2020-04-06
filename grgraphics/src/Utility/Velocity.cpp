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

float grg::Velocity::DoCalc(const sf::Time& elapsed, float& velocity, bool moveKeyPressed) {
    const float elapsedSeconds = elapsed.asSeconds();
    // former scrolling calculations, now in Player.
    // ToDo: cleanup. maybe use it as a camera delay
    //bool viewChanged = false;
    constexpr float speedUp = 2.0F;
    //constexpr float keyAcceleration = 500.0F * speedUp;
    /*bool moveKeyPressed = false;
       if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        // m_view.move(-1.0F * 1000 * elapsedSeconds, 0.0F);
        m_xVelocity -= speedUp * keyAcceleration * elapsedSeconds;
        //spdlog::info("m_xVelocity={}.", m_xVelocity);
        viewChanged = true;
        moveKeyPressed = true;
       } else {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            //m_view.move(1.0F * 1000 * elapsedSeconds, 0.0F);
            m_xVelocity += speedUp * keyAcceleration * elapsedSeconds;
            //spdlog::info("m_xVelocity={}.", m_xVelocity);
            viewChanged = true;
            moveKeyPressed = true;
        }
       }*/

    const float absVelocity = std::abs(velocity);
    float speedRamp = 1.0F - elapsedSeconds * speedUp;
    //if(absVelocity + 1.0F < lastAbsVelocity) {
    if(!moveKeyPressed) {
        //} else {
        constexpr float slowDown = 1.4F * speedUp;
        speedRamp = 1.0F - elapsedSeconds * slowDown;
        constexpr float hysteresisEdge = 50.0F * slowDown;     // lower edge when friction
        // starts to
        // decrease velocity abrupt.
        if(absVelocity < hysteresisEdge) {
            speedRamp = 1.0F -
                        ((elapsedSeconds * slowDown * 1.0F) +
                         (0.01F * ((hysteresisEdge / 10.0F) - (absVelocity / (hysteresisEdge / 5.0F)))));
            //if(absVelocity < (hysteresisEdge / 100.0F)) {
            if(absVelocity < (0.5F)) {
                // stop all movement at 1% of the hysteresis low point.
                velocity = 0;
            }
        }
    }

    // -> m_player.Update(elapsed);

    //m_lastAbsVelocity = absVelocity;
    // -> m_xVelocity *= speedRamp;
    return speedRamp;

    //m_csvFile.WriteData(m_xVelocity);
    // -> grcore::writeTelemetryData(static_cast<double>(m_xVelocity));
} // grg::Velocity::DoCalc
