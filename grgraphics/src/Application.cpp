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
#include <grcore/Resource.h>
#include <iostream>
#include <spdlog/spdlog.h>

//constexpr bool USE_VSYNC = false;

grg::Application::Application(sf::RenderWindow &window, bool vSyncEnabled, unsigned short frameRateLimit) : m_window(window),
    Frame_Rate_Limit(std::max<unsigned short>(frameRateLimit, 10)) {
    SetVSync(vSyncEnabled);
    m_mainGameFont.loadFromFile("Futura Bk BT Book.ttf");
    m_fpsDisplay = sf::Text("Test, Test", m_mainGameFont);
    loadDebugFont();
}

/** Brief description of Application, Run
 *  Detailed description.
 *  @param app TODO
 *  @return TODO
 */
void grg::Application::Run(grg::SimpleApplication &app) {
    int frameCounter = 0;
    float fpsTime = 0;

    // init user application.
    app.OnInit(*this);

    // starts the clock
    sf::Clock clock;

    while(m_window.isOpen()) {
        sf::Time elapsed = clock.restart();
        float elapsedSeconds = elapsed.asSeconds();
        fpsTime = fpsTime + elapsedSeconds;
        //std::cout << elapsedSeconds << std::endl;
        //clock.restart();

        sf::Event event {};

        while(m_window.pollEvent(event)) {
            /*switch(event.type)
                case sf::Event::Closed:
                    window.close();*/

            if(event.type == sf::Event::Closed) {
                m_window.close();
                continue;
            }

            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {
                    std::cout << "the escape key was pressed" << std::endl;
                    std::cout << "control:" << event.key.control << std::endl;
                    std::cout << "alt:" << event.key.alt << std::endl;
                    std::cout << "shift:" << event.key.shift << std::endl;
                    std::cout << "system:" << event.key.system << std::endl;
                    m_window.close();
                    continue;
                } else if(event.key.code == sf::Keyboard::V) {
                    m_vsync = !m_vsync;
                    SetVSync(m_vsync);
                }
            }

            if(event.type == sf::Event::KeyPressed) {}

            // handle user events.
            app.OnEvent(event);
        }
        /*if(elapsedSeconds < 0.01)
            {
             const char *formatStr = "FPS: {:.1f}, Frame Counter: {}";
             m_fpsDisplay.setString(fmt::format(formatStr, 1.0 / elapsedSeconds, frameCounter));
            }*/
        //        grg::update(elapsed);

        if(frameCounter % 60 == 0) {
            const char* formatStr = "FPS: {:.1f}, Frame Counter: {}";
            m_fpsDisplay.setString(fmt::format(formatStr, 60 / fpsTime, frameCounter));

            fpsTime = 0;
        }

        // update user application.
        app.OnUpdate(elapsed);

        m_window.clear();
        // draw user application.
        app.OnDraw(m_window);
        m_window.draw(m_fpsDisplay);
        m_window.display();

        if(m_vsync) {
            sf::sleep(sf::milliseconds(16));
        } else {
            sf::sleep(sf::milliseconds(1));
        }

        //sf::Thread::wait(1);
        frameCounter++;
    }
} // grg::Application::Run

void grg::Application::SetVSync(bool enabled) {
    if(enabled) {
        this->m_window.setVerticalSyncEnabled(true);
        this->m_vsync = true;
    } else {
        this->m_window.setFramerateLimit(Frame_Rate_Limit);
        this->m_window.setVerticalSyncEnabled(false);
        this->m_vsync = false;
    }
}

sf::Vector2<unsigned int> grg::Application::GetSize() const {
    return m_window.getSize();
}

void grg::Application::loadDebugFont() {
    const int fontId = 129;
    auto fi = m_debugFont.getInfo();
    if(!(fi.family == "")) {return; }

    spdlog::warn("[{}] Loading Font from resource (id={}).", __PRETTY_FUNCTION__, fontId);
    grcore::Resource res(fontId);
    auto [data, size, error] = res.Get();
    //std::cout << "data:" << data << std::endl;
    //std::cout << "size:" << size << std::endl;
    //std::cout << "error:" << error << std::endl;
    if(!error) {
        bool success = m_debugFont.loadFromMemory(data, size);
        if(success) {
            fi = m_debugFont.getInfo();
            spdlog::warn("[{}] Loaded Font from resource (id={}): '{}'.", __PRETTY_FUNCTION__, fontId, fi.family);
        } else {
            spdlog::error("[{}] ERROR loading Font from resource (id={}).", __PRETTY_FUNCTION__, fontId);
        }
    }
} // grg::Application::loadDebugFont

// grg::Application::GetDebugFont

// grg::Application::Run
