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

#ifndef OPENGLTEMPLATE_7C6596A73F134A68A428CA3FD2E6D069_APPLICATION_H
#define OPENGLTEMPLATE_7C6596A73F134A68A428CA3FD2E6D069_APPLICATION_H

#include "SimpleApplication.h"
#include "warning/SFML_Graphics.h" // ToDo: remove me
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
  Application(sf::RenderWindow &window, bool vSyncEnabled = true, unsigned short frameRateLimit = 2 * 60);

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

    sf::RenderWindow &GetWindow() const {
        return m_window;
    }

    const sf::Font &GetMainGameFont() const {
        return m_mainGameFont;
    }

    const sf::Font &GetDebugFont() const {
        return m_debugFont;
    }

    sf::Vector2<unsigned int> GetSize() const;

    void SetVSync(bool enabled);

private:

    void loadDebugFont();

    sf::RenderWindow &m_window;
    sf::Text m_fpsDisplay;
    sf::Font m_mainGameFont;
    sf::Font m_debugFont;
    bool m_vsync;
    const unsigned short Frame_Rate_Limit;
};
}// namespace grg

#endif//OPENGLTEMPLATE_7C6596A73F134A68A428CA3FD2E6D069_APPLICATION_H
