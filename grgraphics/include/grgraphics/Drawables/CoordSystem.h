/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the CoordSystem.h class.
 * \file       CoordSystem.h
 * \date       2020-03-23
 * \author     Jedzia.
 *
 * modified    2020-03-25, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef OPENGLTEMPLATE_9E8EADFBCB3D404C8029D83491885AF6_COORDSYSTEM_H
#define OPENGLTEMPLATE_9E8EADFBCB3D404C8029D83491885AF6_COORDSYSTEM_H

#include <SFML/Graphics/Drawable.hpp>
#include <experimental/propagate_const>
#include <memory>

namespace sf {
class SFML_GRAPHICS_API Font;
}
namespace grg {
class CoordSystem final : public sf::Drawable {
public:

    CoordSystem(const sf::FloatRect &dimensions, const sf::Font &font);
    ~CoordSystem();

protected:

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:

    struct impl;
    std::experimental::propagate_const<std::unique_ptr<impl>> p_impl;
    //std::unique_ptr<impl> p_impl;
    //std::experimental::propagate_const<std::shared_ptr<impl>> p_impl;
    //std::shared_ptr<impl> p_impl;
    const sf::Font &m_Font;
};
}

#endif//OPENGLTEMPLATE_9E8EADFBCB3D404C8029D83491885AF6_COORDSYSTEM_H
