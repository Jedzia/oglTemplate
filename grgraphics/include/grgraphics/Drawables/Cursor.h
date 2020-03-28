/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Cursor.h class.
 * \file       Cursor.h
 * \date       2020-03-28
 * \author     Jedzia.
 *
 * modified    2020-03-28, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGLTEMPLATE_ED62CB437F5146F2ADDE61CC764404BF_CURSOR_H
#define OPENGLTEMPLATE_ED62CB437F5146F2ADDE61CC764404BF_CURSOR_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>
#include <experimental/propagate_const>
#include <memory>

namespace sf {
class SFML_GRAPHICS_API RenderWindow;
}
namespace grg {
class Cursor final : public sf::Drawable {
public:

    Cursor(sf::RenderWindow &window);
    ~Cursor();
    void Update(sf::Time elapsed);

protected:

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:

    struct Impl;
    std::experimental::propagate_const<std::unique_ptr<Impl>> m_pImpl;
};
}
#endif//OPENGLTEMPLATE_ED62CB437F5146F2ADDE61CC764404BF_CURSOR_H
