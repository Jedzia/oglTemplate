/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Application.h class.
 * \file       Application.h
 * \date       2020-03-17
 * \author     Jedzia.
 *
 * modified    2020-03-17, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef GRGRAPHICS_APPLICATION_H
#define GRGRAPHICS_APPLICATION_H

#include "SimpleApplication.h"
#include "warning/SFML_Graphics.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Thread.hpp>
#include <type_traits>

namespace grg {
/** @class Application:
 *  Detailed description.
 *
 */
class Application {
public:

    Application(sf::RenderWindow &window);

    void DoDing();

    void Run(SimpleApplication &app);

    /** Brief description of Application, Run
     *  Detailed description.
     *
     */
    template<typename T>
    void Run() {
        static_assert(std::is_base_of<SimpleApplication, T>::value, "T must inherit from grg::SimpleApplication");
        T app;
        Run(app);
    }

    const sf::Font &getMainGameFont() const {
        return m_mainGameFont;
    }

    const sf::Font &getDebugFont() const {
        return m_debugFont;
    }

    sf::Vector2<unsigned int> getSize() const;

private:

    void loadDebugFont();

    sf::RenderWindow &m_window;
    sf::Text m_fpsDisplay;
    sf::Font m_mainGameFont;
    sf::Font m_debugFont;
};
}// namespace grg

#endif//GRGRAPHICS_APPLICATION_H
