//
// Created by Jedzia on 17.03.2020.
//

#ifndef OPENGLTEMPLATE_APPLICATION_H
#define OPENGLTEMPLATE_APPLICATION_H

#include "warning/SFML_Graphics.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Thread.hpp>
#include "SimpleApplication.h"

namespace grg {
    class Application {

    public:
        Application(sf::RenderWindow &window);

        void DoDing();

        void Run(SimpleApplication &app);

    private:
        sf::RenderWindow &_window;
        sf::Text fpsDisplay;
        sf::Font mainGameFont;
    };
}


#endif //OPENGLTEMPLATE_APPLICATION_H
