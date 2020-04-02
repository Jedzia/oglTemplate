/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the implementation of
 *             collision detection related stuff.
 * \file       Collision.cpp
 * \date       2020-04-02
 * \author     Jedzia.
 *
 * modified    2020-04-02, Jedzia
 */
/*---------------------------------------------------------*/
#include "grgraphics/Utility/Collision.h"
#include <grgraphics/warning/SFML_Graphics.h>
#include <map>

namespace grg {
/** @class Provides the infrastructure to handle bitmasks.
 */
class BitmaskManager {
public:

    ~BitmaskManager() {
        std::map<const sf::Texture *, sf::Uint8 *>::const_iterator end = m_bitmasks.end();

        for(std::map<const sf::Texture *, sf::Uint8 *>::const_iterator iter = m_bitmasks.begin(); iter != end; iter++) {
            delete [] iter->second;
        }
    }

    /** Get pixel from a mask
     *  @param mask collision mask
     *  @param tex reference texture
     *  @param x horizontal coordinate
     *  @param y vertical coordinate
     *  @return the value of the pixel or 0 if the coordinates where out of bounds.
     */
    static sf::Uint8 GetPixel (const sf::Uint8* mask, const sf::Texture* tex, unsigned int x, unsigned int y) {
        if(x > tex->getSize().x||y > tex->getSize().y) {
            return 0;
        }

        return mask[x + y * tex->getSize().x];
    }

    /** Create Alpha Collision Mask.
     *  @param tex Source texture to collide.
     *  @return the collision mask.
     */
    sf::Uint8 * GetMask (const sf::Texture* tex) {
        sf::Uint8* mask;
        std::map<const sf::Texture *, sf::Uint8 *>::iterator pair = m_bitmasks.find(tex);
        if(pair == m_bitmasks.end()) {
            sf::Image img = tex->copyToImage();
            mask = CreateMask(tex, img);
        } else {
            mask = pair->second;
        }

        return mask;
    }

    /** Create Alpha Collision Mask.
     *  @param tex Source texture to collide.
     *  @param img Source image to collide.
     *  @return the collision mask.
     */
    sf::Uint8 * CreateMask (const sf::Texture* tex, const sf::Image &img) {
        sf::Uint8* mask = new sf::Uint8[tex->getSize().y * tex->getSize().x];

        for(unsigned int y = 0; y < tex->getSize().y; y++)
        {
            for(unsigned int x = 0; x < tex->getSize().x; x++) {
                mask[x + y * tex->getSize().x] = img.getPixel(x, y).a;
            }
        }
        m_bitmasks.insert(std::pair<const sf::Texture *, sf::Uint8 *>(tex, mask));

        return mask;
    }

private:

    std::map<const sf::Texture *, sf::Uint8 *> m_bitmasks;
};

BitmaskManager G_BITMASKS;

bool pixelPerfectTest(const sf::Sprite &object1, const sf::Sprite &object2, sf::Uint8 alphaLimit) {
    sf::FloatRect intersection;
    if(object1.getGlobalBounds().intersects(object2.getGlobalBounds(), intersection)) {
        sf::IntRect o1SubRect = object1.getTextureRect();
        sf::IntRect o2SubRect = object2.getTextureRect();

        sf::Uint8* mask1 = G_BITMASKS.GetMask(object1.getTexture());
        sf::Uint8* mask2 = G_BITMASKS.GetMask(object2.getTexture());

        // Loop through our pixels
        for(int i = static_cast<int>(intersection.left); i < intersection.left + intersection.width; i++) {
            for(int j = static_cast<int>(intersection.top); j < intersection.top + intersection.height; j++) {
                sf::Vector2f o1V = object1.getInverseTransform().transformPoint(i, j);
                sf::Vector2f o2V = object2.getInverseTransform().transformPoint(i, j);

                // Make sure pixels fall within the sprite's subrect
                if(o1V.x > 0 && o1V.y > 0 && o2V.x > 0 && o2V.y > 0 &&
                   o1V.x < o1SubRect.width && o1V.y < o1SubRect.height &&
                   o2V.x < o2SubRect.width && o2V.y < o2SubRect.height) {
                    if(G_BITMASKS.GetPixel(mask1, object1.getTexture(),
                               static_cast<unsigned int>(o1V.x + o1SubRect.left),
                               static_cast<unsigned int>(o1V.y + o1SubRect.top)) > alphaLimit &&
                       G_BITMASKS.GetPixel(mask2, object2.getTexture(),
                               static_cast<unsigned int>(o2V.x + o2SubRect.left),
                               static_cast<unsigned int>(o2V.y + o2SubRect.top)) > alphaLimit) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
} // pixelPerfectTest

bool createTextureAndBitmask(sf::Texture &loadInto, const std::string &filename) {
    sf::Image img;
    if(!img.loadFromFile(filename)) {
        return false;
    }

    if(!loadInto.loadFromImage(img)) {
        return false;
    }

    G_BITMASKS.CreateMask(&loadInto, img);
    return true;
}

/** Get the center point of a Sprite.
 *  Computes the midpoint of the specified Sprite.
 *  @param object Sprite object to get the property from.
 *  @return The center-point of the specified Sprite.
 */
sf::Vector2f getSpriteCenter (const sf::Sprite &object) {
    sf::FloatRect aabb = object.getGlobalBounds();
    return sf::Vector2f(aabb.left + aabb.width / 2.f, aabb.top + aabb.height / 2.f);
}

/** Get the size of a Sprite.
 *  Computes the size of the specified Sprite. Takes scaling into account.
 *  @param object Sprite object to get the dimensions from.
 *  @return The size of the specified Sprite.
 */
sf::Vector2f getSpriteSize (const sf::Sprite &object) {
    sf::IntRect originalSize = object.getTextureRect();
    sf::Vector2f scale = object.getScale();
    return sf::Vector2f(originalSize.width * scale.x, originalSize.height * scale.y);
}

bool circleTest(const sf::Sprite &object1, const sf::Sprite &object2) {
    sf::Vector2f obj1Size = getSpriteSize(object1);
    sf::Vector2f obj2Size = getSpriteSize(object2);
    const float radius1 = (obj1Size.x + obj1Size.y) / 4;
    const float radius2 = (obj2Size.x + obj2Size.y) / 4;

    sf::Vector2f distance = getSpriteCenter(object1) - getSpriteCenter(object2);

    return (distance.x * distance.x + distance.y * distance.y <= (radius1 + radius2) * (radius1 + radius2));
}

/** @class OrientedBoundingBox:
 *  Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite.
 */
class OrientedBoundingBox     // Used in the boundingBoxTest
{
public:

    /** Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite
     *  @param object The sf::Sprite used for calculation.
     */
    OrientedBoundingBox (const sf::Sprite &object) {
        sf::Transform trans = object.getTransform();
        sf::IntRect local = object.getTextureRect();
        m_points[0] = trans.transformPoint(0.f, 0.f);
        m_points[1] = trans.transformPoint(local.width, 0.f);
        m_points[2] = trans.transformPoint(local.width, local.height);
        m_points[3] = trans.transformPoint(0.f, local.height);
    }

    sf::Vector2f m_points[4];

    /** Project all four points of the OBB onto the given axis and return the dotproducts
     *  of the two outermost points.
     *  @param axis axis location
     *  @param min minimum point
     *  @param max maximum point
     */
    void ProjectOntoAxis (const sf::Vector2f &axis, float &min, float &max) {
        min = (m_points[0].x * axis.x + m_points[0].y * axis.y);
        max = min;

        for(int j = 1; j < 4; j++)
        {
            float projection = (m_points[j].x * axis.x + m_points[j].y * axis.y);

            if(projection < min) {
                min = projection;
            }

            if(projection > max) {
                max = projection;
            }
        }
    } // ProjectOntoAxis
};

bool boundingBoxTest(const sf::Sprite &object1, const sf::Sprite &object2) {
    OrientedBoundingBox obb1(object1);
    OrientedBoundingBox obb2(object2);

    // Create the four distinct axes that are perpendicular to the edges of the two rectangles
    sf::Vector2f axes[4] = {
        sf::Vector2f(obb1.m_points[1].x - obb1.m_points[0].x,
                obb1.m_points[1].y - obb1.m_points[0].y),
        sf::Vector2f(obb1.m_points[1].x - obb1.m_points[2].x,
                obb1.m_points[1].y - obb1.m_points[2].y),
        sf::Vector2f(obb2.m_points[0].x - obb2.m_points[3].x,
                obb2.m_points[0].y - obb2.m_points[3].y),
        sf::Vector2f(obb2.m_points[0].x - obb2.m_points[1].x,
                obb2.m_points[0].y - obb2.m_points[1].y)
    };

    for(int i = 0; i < 4; i++)    // For each axis...
    {
        float minObb1, maxObb1, minObb2, maxObb2;

        // ... project the points of both OBBs onto the axis ...
        obb1.ProjectOntoAxis(axes[i], minObb1, maxObb1);
        obb2.ProjectOntoAxis(axes[i], minObb2, maxObb2);

        // ... and check whether the outermost projected points of both OBBs overlap.
        // If this is not the case, the Separating Axis Theorem states that there can be no
        // collision between the rectangles
        if(!((minObb2 <= maxObb1) && (maxObb2 >= minObb1))) {
            return false;
        }
    }
    return true;
} // boundingBoxTest
}
