/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the implementation of
 *             collision detection related stuff.
 * \file       Collision.h
 * \date       2020-04-02
 * \author     Jedzia.
 *
 * modified    2020-04-02, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGLTEMPLATE_3192E36697EB4639B396650D575C1C19_COLLISION_H
#define OPENGLTEMPLATE_3192E36697EB4639B396650D575C1C19_COLLISION_H

#include <SFML/Graphics/Sprite.hpp>

namespace grg {
//////
/// Test for a collision between two sprites by comparing the alpha values of overlapping pixels
/// Supports scaling and rotation
/// AlphaLimit: The threshold at which a pixel becomes "solid". If AlphaLimit is 127, a pixel with
/// alpha value 128 will cause a collision and a pixel with alpha value 126 will not.
///
/// This functions creates bitmasks of the textures of the two sprites by
/// downloading the textures from the graphics card to memory -> SLOW!
/// You can avoid this by using the "createTextureAndBitmask" function
//////
bool pixelPerfectTest(const sf::Sprite &object1, const sf::Sprite &object2, sf::Uint8 alphaLimit = 0);

//////
/// Replaces Texture::loadFromFile
/// Load an imagefile into the given texture and create a bitmask for it
/// This is much faster than creating the bitmask for a texture on the first run of
// "pixelPerfectTest"
///
/// The function returns false if the file could not be opened for some reason
//////
bool createTextureAndBitmask(sf::Texture &loadInto, const std::string &filename);

//////
/// Test for collision using circle collision dection
/// Radius is averaged from the dimensions of the sprite so
/// roughly circular objects will be much more accurate
//////
bool circleTest(const sf::Sprite &object1, const sf::Sprite &object2);

//////
/// Test for bounding box collision using the Separating Axis Theorem
/// Supports scaling and rotation
//////
bool boundingBoxTest(const sf::Sprite &object1, const sf::Sprite &object2);
}

#endif //OPENGLTEMPLATE_3192E36697EB4639B396650D575C1C19_COLLISION_H
