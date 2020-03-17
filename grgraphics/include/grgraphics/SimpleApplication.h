//
// Created by Jedzia on 17.03.2020.
//

#ifndef OPENGLTEMPLATE_61CDCBB50D51466E91769A07F3D44D19_SIMPLEAPPLICATION_H
#define OPENGLTEMPLATE_61CDCBB50D51466E91769A07F3D44D19_SIMPLEAPPLICATION_H


#include "warning/SFML_Graphics.h"

namespace grg {
    class SimpleApplication {
    public:
        virtual void OnDraw(sf::RenderWindow &window, sf::Time elapsed) = 0;
        virtual ~SimpleApplication() = default;
    };
}


#endif //OPENGLTEMPLATE_61CDCBB50D51466E91769A07F3D44D19_SIMPLEAPPLICATION_H
