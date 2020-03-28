/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the VectorUtil.cpp class.
 * \file       VectorUtil.cpp
 * \date       2020-03-28
 * \author     Jedzia.
 *
 * modified    2020-03-28, Jedzia
 */
/*---------------------------------------------------------*/
#include "grgraphics/Utility/VectorUtil.h"
#include <algorithm>

namespace grg {
sf::Vector2f restrict (sf::Vector2f in, sf::FloatRect bounds) {
    /*auto x1 = std::max(in.x, bounds.left);
       auto x2 = std::min(in.x, bounds.width);
       auto y1 = std::max(in.y, bounds.top);
       auto y2 = std::min(in.y, bounds.height);*/

    //auto x = std::min(x1, x2);
    //auto y = std::min(y1, y2);
    return {
               (std::clamp(in.x, bounds.left, bounds.width)), (std::clamp(in.y, bounds.top, bounds.height))
    };
}
}
