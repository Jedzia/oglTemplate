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
 * modified    2020-03-23, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef OPENGLTEMPLATE_9E8EADFBCB3D404C8029D83491885AF6_COORDSYSTEM_H
#define OPENGLTEMPLATE_9E8EADFBCB3D404C8029D83491885AF6_COORDSYSTEM_H

#include <SFML/Graphics/Drawable.hpp>
namespace grg {
class CoordSystem : public sf::Drawable {
protected:

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
}

#endif//OPENGLTEMPLATE_9E8EADFBCB3D404C8029D83491885AF6_COORDSYSTEM_H
