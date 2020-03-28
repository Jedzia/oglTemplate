/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the SimpleApplication.h class.
 * \file       SimpleApplication.h
 * \date       2020-03-17
 * \author     Jedzia.
 *
 * modified    2020-03-17, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGLTEMPLATE_61CDCBB50D51466E91769A07F3D44D19_SIMPLEAPPLICATION_H
#define OPENGLTEMPLATE_61CDCBB50D51466E91769A07F3D44D19_SIMPLEAPPLICATION_H

#include "warning/SFML_Graphics.h" // ToDo: remove me
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

namespace grg {
class Application;

/** @class SimpleApplication:
 *  Main loop for a SFML based application.
 */
class SimpleApplication {
public:

    /** @brief Setup Routine.
     *  The place you can initialize your implementation.
     *  @param application Host application providing system and window data.
     */
    virtual void OnInit(const Application & /*application*/) {}

    /** @brief Does fire on every event.
     *  The place you can handle Keyboard, Mouse, etc. events.
     *  @param event The event data.
     */
    virtual void OnEvent(const sf::Event /*&event*/) {}

    /** Update state.
     *  Refresh the state of your application here. Not guaranteed to run every frame. But can be
     * configured to run more often than in frames to provide a smooth user experience or AI.
     *  @param elapsed The elapsed time between calls to OnUpdate.
     */
    virtual void OnUpdate(sf::Time elapsed) = 0;

    /** Draw content.
     *  Draw your content to the window every frame.
     *  @param window Provides the RenderTarget::draw(...) endpoint.
     */
    virtual void OnDraw(sf::RenderWindow &window) = 0;

    virtual ~SimpleApplication() = default;
};
}// namespace grg

#endif//OPENGLTEMPLATE_61CDCBB50D51466E91769A07F3D44D19_SIMPLEAPPLICATION_H
