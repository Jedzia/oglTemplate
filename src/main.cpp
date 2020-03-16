/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the main.cpp class.
 * \file       main.cpp
 * \date       2020-03-14
 * \author     Jedzia.
 *
 * modified    2020-03-14, Jedzia
 */
/*---------------------------------------------------------*/
//#define USE_SPDLOG 1
#include "precompiled.h"
//
#include <boost/locale/info.hpp>
#include <grcore/grcore.h>
#include <grgraphics/grgraphics.h>
#include <iostream>

/*
   #include <SFML/Graphics.hpp>
   #include <SFML/System/Clock.hpp>
   #include <SFML/System/Thread.hpp>
   #include <fmt/format.h>
   #include <iostream>
 */

//#define USE_VSYNC false
constexpr bool USE_VSYNC = false;

#if USE_DOC_OPTS
static const char USAGE[] =
    R"(Naval Fate.

    Usage:
      naval_fate ship new <name>...
      naval_fate ship <name> move <x> <y> [--speed=<kn>]
      naval_fate ship shoot <x> <y>
      naval_fate mine (set|remove) <x> <y> [--moored | --drifting]
      naval_fate (-h | --help)
      naval_fate --version

    Options:
      -h --help     Show this screen.
      --version     Show version.
      --speed=<kn>  Speed in knots [default: 10].
      --moored      Moored (anchored) mine.
      --drifting    Drifting mine.
)";

/** Brief description of $(fclass), handle_main_arguments
 *  Detailed description.
 *  @param argc TODO
 *  @param argv TODO
 *  @return TODO
 */
int handle_main_arguments(int argc, const char* * argv){
    std::map<std::string, docopt::value> args =
        docopt::docopt(USAGE,
                { argv + 1, argv + argc },
                true,                   // show help if requested
                "Naval Fate 2.0");      // version string

    for(auto const& arg : args) {
        std::cout << arg.first << arg.second << std::endl;
    }
    return 0;
}

#endif // if USE_DOC_OPTS

/** Brief description of $(fclass), logSomething
 *  Detailed description.
 *
 */
void logSomething() {
//#if USE_SPDLOG
    //Use the default logger (stdout, multi-threaded, colored)
    spdlog::info("Hello, {}!", "World");
//#endif
    core::info();
    core::log("Erstes", "Zweites", "Drittes");
    fmt::print("Hello, from {}\n", "{fmt}");
}

/** Brief description of $(fclass), main
 *  Detailed description.
 *  @return TODO
 */
int main() {
    constexpr int WINDOW_WIDTH = 1280;
    constexpr auto WINDOW_RATIO = std::make_tuple(16.0, 9.0);
    constexpr int WINDOW_HEIGHT = static_cast<int>(WINDOW_WIDTH * std::get<1>(WINDOW_RATIO) /
                                                   std::get<0>(WINDOW_RATIO));

    logSomething();
    core::bla();
    auto title = fmt::format("SFML Window ({0}, {1} -> {2:.1f}:{3})", WINDOW_WIDTH, WINDOW_HEIGHT,
            std::get<0>(WINDOW_RATIO), std::get<1>(WINDOW_RATIO));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), title);
    if(USE_VSYNC) {
        window.setVerticalSyncEnabled(true);
    }
    else {
        window.setFramerateLimit(60 * 4);
    }

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Font mainGameFont;
    mainGameFont.loadFromFile("Futura Bk BT Book.ttf");
    sf::Text fpsDisplay("Test, Depp", mainGameFont);

    const float Speed = 250.f;
    float x = 0, y = 0;
    int frame_counter = 0;
    float fps_time = 0;

    sf::Clock clock; // starts the clock

    while(window.isOpen()) {
        sf::Time elapsed = clock.restart();
        float elapsedSeconds = elapsed.asSeconds();
        fps_time = fps_time + elapsedSeconds;
        //std::cout << elapsedSeconds << std::endl;
        //clock.restart();

        sf::Event event {};

        while(window.pollEvent(event)) {
            /*switch(event.type)
                case sf::Event::Closed:
                    window.close();*/

            if(event.type == sf::Event::Closed) {
                window.close();
            }

            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {
                    std::cout << "the escape key was pressed" << std::endl;
                    std::cout << "control:" << event.key.control << std::endl;
                    std::cout << "alt:" << event.key.alt << std::endl;
                    std::cout << "shift:" << event.key.shift << std::endl;
                    std::cout << "system:" << event.key.system << std::endl;
                    window.close();
                }
            }

            if(event.type == sf::Event::KeyPressed) {}
        }
        /*if(elapsedSeconds < 0.01)
           {
            const char *formatStr = "FPS: {:.1f}, Frame Counter: {}";
            fpsDisplay.setString(fmt::format(formatStr, 1.0 / elapsedSeconds, frame_counter));
           }*/

        if(frame_counter % 60 == 0) {
            const char* formatStr = "FPS: {:.1f}, Frame Counter: {}";
            fpsDisplay.setString(fmt::format(formatStr, 60 / fps_time, frame_counter));

            fps_time = 0;
        }

        shape.setPosition(x, y);
        x += Speed * elapsedSeconds;
        y += Speed * 0.5f * elapsedSeconds;
        if(x > 500) {
            x = 0;
        }

        if(y > 500) {
            y = 0;
        }

        window.clear();
        window.draw(shape);
        window.draw(fpsDisplay);
        window.display();

        if(USE_VSYNC) {
            sf::sleep(sf::milliseconds(12));
        }
        else {
            sf::sleep(sf::milliseconds(1));
        }

        //sf::Thread::wait(1);
        frame_counter++;
    }
    return 0;
} // main
