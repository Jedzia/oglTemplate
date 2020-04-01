/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the CoordGraph.h class.
 * \file       CoordGraph.h
 * \date       2020-04-01
 * \author     Jedzia.
 *
 * modified    2020-04-01, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGLTEMPLATE_AB3283CA4C25421EA6E21045A1E54CFD_COORDGRAPH_H
#define OPENGLTEMPLATE_AB3283CA4C25421EA6E21045A1E54CFD_COORDGRAPH_H

#include "CoordSystem.h"

namespace grg {
class CoordGraph : public CoordSystem {
public:

    CoordGraph(const sf::FloatRect &dimensions, const sf::Font &font);
    virtual ~CoordGraph();
};
}

#endif //OPENGLTEMPLATE_AB3283CA4C25421EA6E21045A1E54CFD_COORDGRAPH_H
