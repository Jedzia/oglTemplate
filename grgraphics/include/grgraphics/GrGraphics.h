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
 * modified    2020-04-06, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef OPENGLTEMPLATE_B1455E0B12FF458990FEEA6F2E5B6ACB_GRGRAPHICS_H
#define OPENGLTEMPLATE_B1455E0B12FF458990FEEA6F2E5B6ACB_GRGRAPHICS_H

#include <SFML/System/Clock.hpp>
//
#include "Application.h"
#include "Camera.h"
#include "Drawables/CoordGraph.h"
#include "Drawables/CoordSystem.h"
#include "Drawables/Cursor.h"
#include "Drawables/SpriteOverlay.h"
#include "Drawables/TileMap.h"
#include "Math.h"
#include "Player.h"
#include "Setup.h"
#include "Utility/Collision.h"
#include "Utility/Velocity.h"
namespace grg {
void bla();

void update(sf::Time elapsed);
}

#endif //OPENGLTEMPLATE_B1455E0B12FF458990FEEA6F2E5B6ACB_GRGRAPHICS_H
