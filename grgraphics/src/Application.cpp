/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Application.cpp class.
 * \file       Application.cpp
 * \date       2020-03-17
 * \author     Jedzia.
 *
 * modified    2020-03-17, Jedzia
 */
/*---------------------------------------------------------*/

#include "grgraphics/Application.h"
#include "grgraphics/warning/FMT_format.h"
#include <iostream>

constexpr bool USE_VSYNC = false;

/** Brief description of Application, DoDing
 *  Detailed description.
 *  @return TODO
 */
void grg::Application::DoDing() {
    //_window.close();
}

grg::Application::Application(sf::RenderWindow &window) : _window(window) {
    mainGameFont.loadFromFile("Futura Bk BT Book.ttf");
    fpsDisplay = sf::Text("Test, Depp", mainGameFont);
}

/** Brief description of Application, Run
 *  Detailed description.
 *  @param app TODO
 *  @return TODO
 */
void grg::Application::Run(grg::SimpleApplication &app) {
    int frame_counter = 0;
    float fps_time = 0;

    sf::Clock clock; // starts the clock

    while(_window.isOpen()) {
        sf::Time elapsed = clock.restart();
        float elapsedSeconds = elapsed.asSeconds();
        fps_time = fps_time + elapsedSeconds;
        //std::cout << elapsedSeconds << std::endl;
        //clock.restart();

        sf::Event event {};

        while(_window.pollEvent(event)) {
            /*switch(event.type)
                case sf::Event::Closed:
                    window.close();*/

            if(event.type == sf::Event::Closed) {
                _window.close();
                continue;
            }

            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {
                    std::cout << "the escape key was pressed" << std::endl;
                    std::cout << "control:" << event.key.control << std::endl;
                    std::cout << "alt:" << event.key.alt << std::endl;
                    std::cout << "shift:" << event.key.shift << std::endl;
                    std::cout << "system:" << event.key.system << std::endl;
                    _window.close();
                    continue;
                }
                else if(event.key.code == sf::Keyboard::V) {
                    _window.setVerticalSyncEnabled(true);
                }
            }

            if(event.type == sf::Event::KeyPressed) {}

            app.OnEvent(event);
        }
        /*if(elapsedSeconds < 0.01)
            {
             const char *formatStr = "FPS: {:.1f}, Frame Counter: {}";
             fpsDisplay.setString(fmt::format(formatStr, 1.0 / elapsedSeconds, frame_counter));
            }*/
//        grg::update(elapsed);

        if(frame_counter % 60 == 0) {
            const char* formatStr = "FPS: {:.1f}, Frame Counter: {}";
            fpsDisplay.setString(fmt::format(formatStr, 60 / fps_time, frame_counter));

            fps_time = 0;
        }

        app.OnUpdate(elapsed);

        _window.clear();
        app.OnDraw(_window);
        _window.draw(fpsDisplay);
        _window.display();

        if(USE_VSYNC) {
            sf::sleep(sf::milliseconds(12));
        }
        else {
            sf::sleep(sf::milliseconds(1));
        }

        //sf::Thread::wait(1);
        frame_counter++;
    }
} // grg::Application::Run
