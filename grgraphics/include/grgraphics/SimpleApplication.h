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

#include "warning/SFML_Graphics.h"

namespace grg {
/** @class SimpleApplication:
 *  Detailed description.
 *  @param window TODO
 *  @param elapsed TODO
 */
class SimpleApplication {
public:

    /** @brief Does fire on every event.
     *  The place you can handle Keyboard, Mouse, etc. events.
     *  @param event The event data.
     */
    virtual void OnEvent(const sf::Event /*&event*/) {};

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
}

#endif //OPENGLTEMPLATE_61CDCBB50D51466E91769A07F3D44D19_SIMPLEAPPLICATION_H
