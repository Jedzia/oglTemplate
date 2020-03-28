/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the VectorUtil.h class.
 * \file       VectorUtil.h
 * \date       2020-03-28
 * \author     Jedzia.
 *
 * modified    2020-03-28, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGLTEMPLATE_B501BA72401D4BA782C6F24AB71BCFEA_VECTORUTIL_H
#define OPENGLTEMPLATE_B501BA72401D4BA782C6F24AB71BCFEA_VECTORUTIL_H
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace grg {
[[nodiscard]] sf::Vector2f restrict (sf::Vector2f in, sf::FloatRect bounds);
}
#endif//OPENGLTEMPLATE_B501BA72401D4BA782C6F24AB71BCFEA_VECTORUTIL_H
