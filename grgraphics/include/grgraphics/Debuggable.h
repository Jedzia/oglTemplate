/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Debuggable.h class.
 * \file       Debuggable.h
 * \date       2020-04-08
 * \author     Jedzia.
 *
 * modified    2020-04-08, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef OPENGLTEMPLATE_47425121E51D4AB1BF1CF3E34AD684A0_DEBUGGABLE_H
#define OPENGLTEMPLATE_47425121E51D4AB1BF1CF3E34AD684A0_DEBUGGABLE_H

#include "grgraphics/warning/SFML_Graphics.h"
//
#include <memory>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>

namespace sf {
class Text;
}

namespace grg {
class Debuggable {
protected:

    typedef typename std::vector<std::unique_ptr<sf::Text>> StorageType;

    static sf::Font m_debugFont;

    Debuggable();

    //std::vector<std::unique_ptr<sf::Text>>::reference emplace_back(_Args &&args) {
    /* std::unique_ptr<sf::Text>& emplace_back(std::unique_ptr<sf::Text>& args) {
       m_vDebugText.push_back(args);
       return m_vDebugText.back();
       }*/

    template<typename _Tp, typename ... _Args>
    StorageType::reference
    make_debug_text(_Args &&... args) {
        // borrowed at std::make_unique
        return m_vDebugText.emplace_back(std::unique_ptr<_Tp>(new _Tp(std::forward<_Args>(args)...)));
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    static constexpr bool Is_In_Debug_Mode = true;
    StorageType m_vDebugText;
};
}

#endif//OPENGLTEMPLATE_47425121E51D4AB1BF1CF3E34AD684A0_DEBUGGABLE_H
