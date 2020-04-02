/*---------------------------------------------------------*/
/*!
 * This file is part of GrCore, the efficient I/O library.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             some items for initial R&D testing.
 * \file       grcore.h
 * \date       2020-01-23
 * \author     Jedzia.
 *
 * modified    2020-01-28, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef GRGRAPHICS_GRGRAPHICS_H
#define GRGRAPHICS_GRGRAPHICS_H

#include <SFML/System/Clock.hpp>
//
#include "Application.h"
#include "Drawables/CoordSystem.h"
#include "Drawables/CoordGraph.h"
#include "Drawables/Cursor.h"
#include "Drawables/TileMap.h"
#include "Utility/Collision.h"
#include "Math.h"
#include "Setup.h"
namespace grg {
void bla();

void update(sf::Time elapsed);
}

#endif // GRGRAPHICS_GRGRAPHICS_H
