/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the CoordGraph.cpp class.
 * \file       CoordGraph.cpp
 * \date       2020-04-01
 * \author     Jedzia.
 *
 * modified    2020-04-01, Jedzia
 */
/*---------------------------------------------------------*/

#include "grgraphics/Drawables/CoordGraph.h"

grg::CoordGraph::CoordGraph(const sf::FloatRect &dimensions, const sf::Font &font) : CoordSystem(dimensions, font) {}

grg::CoordGraph::~CoordGraph() {}
