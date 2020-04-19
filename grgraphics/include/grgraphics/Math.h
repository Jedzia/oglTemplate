/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Math.h class.
 * \file       Math.h
 * \date       2020-03-28
 * \author     Jedzia.
 *
 * modified    2020-03-28, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGLTEMPLATE_BA4DC712CBEB4B84B4502BCBC8613F84_MATH_H
#define OPENGLTEMPLATE_BA4DC712CBEB4B84B4502BCBC8613F84_MATH_H
#include "Utility/VectorUtil.h"
#include <SFML/System/Vector2.hpp>

namespace grg {
enum Direction {
    Up = 0,
    Right,
    Down,
    Left
};

extern std::array<sf::Vector2f, 4> G_DIRECTIONS;

template<typename VectorClass>
static int checkBounds(VectorClass &v, int xMax, int yMax, int xMin = 0, int yMin = 0) {
    int result = 0;
    if(static_cast<int>(v.x) < xMin) {
        v.x = static_cast<float>(xMax);
        result = -1;
    } else if(static_cast<int>(v.x) > xMax) {
        v.x = static_cast<float>(xMin);
        result = 1;
    }

    if(static_cast<int>(v.y) < yMin) {
        v.y = static_cast<float>(yMax);
        result = -2;
    } else if(static_cast<int>(v.y) > yMax) {
        v.y = static_cast<float>(yMin);
        result = 2;
    }

    return result;
}// checkBounds
}
#endif//OPENGLTEMPLATE_BA4DC712CBEB4B84B4502BCBC8613F84_MATH_H
