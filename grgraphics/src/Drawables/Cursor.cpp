/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Cursor.cpp class.
 * \file       Cursor.cpp
 * \date       2020-03-28
 * \author     Jedzia.
 *
 * modified    2020-03-28, Jedzia
 */
/*---------------------------------------------------------*/

#include "grgraphics/Drawables/Cursor.h"
#include <spdlog/spdlog.h>
#include "grgraphics/warning/SFML_Graphics.h"
#include <grcore/Utility/Property.h>
#include <grgraphics/Camera.h>
#include <grgraphics/Constants.h>
#include <grgraphics/Math.h>
#include <grgraphics/Player.h>
#include <iostream>

struct grg::Cursor::Impl {
    Impl(sf::RenderWindow &window, const sf::Font &font) : m_window(window) { /*, m_font(font)*/
        std::cout << "+++ Constructor " << __PRETTY_FUNCTION__ << " called. +++" << std::endl;

        if(m_cursor.loadFromSystem(sf::Cursor::Hand)) {
            window.setMouseCursor(m_cursor);
        }

        const float radius = m_circle.getRadius();
        m_circle.setOrigin(radius, radius);
        m_circle.setFillColor(sf::Color::Transparent);
        m_circle.setOutlineColor(sf::Color::Red);
        m_circle.setOutlineThickness(2.F);

        UpdateCross(radius, sf::Vector2f());

        m_coordDisplay1 = sf::Text("Coords: ", font, Debug_Font_Character_Size);
        m_coordDisplay2 = sf::Text("View  : ", font, Debug_Font_Character_Size);
        m_coordDisplay3 = sf::Text("Player  : ", font, Debug_Font_Character_Size);
        m_coordDisplay4 = sf::Text("Camera  : ", font, Debug_Font_Character_Size);

        int a = 7;
        std::function<int(void)> f = [&a]() { return a; };
        //auto p1 = core::util::Property<int>(f);
        auto p1 = grcore::util::Property([&a]() { return a; });
        //auto p2 = core::util::Property2<int, std::function<int(void)>>( [&a]() { return a; } );

        //auto p = core::util::Property<int>(f);
        auto p = grcore::util::Property(f);
        std::cout << "HasChanged: " << p.HasChanged() << std::endl;
        a = 8;
        std::cout << "HasChanged: " << p.HasChanged() << std::endl;
        std::cout << "HasChanged: " << p.HasChanged() << std::endl;

        std::function<int(void)> fn( [&a]() { return a; });
        //auto l = core::util::PropertyList<int>();
        auto l = grcore::util::PropertyList();
        //l.Add(std::make_shared<core::util::Property<int>>(fn));
        ///auto lll = std::make_shared<core::util::Property<std::function<int(void)>>>([&a]() {
        // return a; });
        ///l.Add(lll);

        //l.AddProp([&a]() { return a; });

        //auto lll2 = std::make_shared<core::util::Property<int>>([&a]() { return a; });
        ///l.AddProp(fn);
        ///l.AddProp([&a]() { return a; });
        double b = 42.0;
        l.AddProp([&a]() { return a; });
        l.AddProp([&b]() { return b; });
        bool hasChanged = l.HasChanged();
        std::cout << "Loop HasChanged: " << hasChanged << std::endl;
        a = 9;
        hasChanged = l.HasChanged();
        std::cout << "Loop HasChanged: " << hasChanged << std::endl;
        hasChanged = l.HasChanged();
        std::cout << "Loop HasChanged: " << hasChanged << std::endl;
        b = 43.2;
        hasChanged = l.HasChanged();
        std::cout << "Loop HasChanged: " << hasChanged << std::endl;
        hasChanged = l.HasChanged();
        std::cout << "Loop HasChanged: " << hasChanged << std::endl;
    }

    void UpdateCross(const float radius, sf::Vector2f translation) {
        //auto xxx = translation / 2.0F;
        // cross is 90 % of outline/radius
        auto drawRadius = radius * 90.0F / 100.F;//
        m_cross[0].position = sf::Vector2f(0, -drawRadius) + translation;
        m_cross[1].position = sf::Vector2f(0, drawRadius) + translation;
        m_cross[2].position = sf::Vector2f(-drawRadius, 0) + translation;
        m_cross[3].position = sf::Vector2f(drawRadius, 0) + translation;
    }

    ~Impl() {
        std::cout << "+++ Destructor  " << __PRETTY_FUNCTION__ << " called. +++" << std::endl;
    }

    void Update(sf::Time /*elapsed*/) {
        //static_cast<void>(elapsed);

        // get the local mouse position (relative to a window)
        const auto screenPosition = sf::Mouse::getPosition(m_window);

        const auto worldPositionF = m_window.mapPixelToCoords(screenPosition);
        const sf::Vector2f screenPositionF {static_cast<float>(screenPosition.x), static_cast<float>(screenPosition.y) };
        const auto drawPositionF = screenPositionF;
        //const sf::Vector2f drawPositionF = restrict (localPositionF, { 100.F, 100.F, 400.F, 400.F
        // });
        const auto bounds = m_coordDisplay1.getLocalBounds();
        //m_coordDisplay1.setPosition(localPositionF + sf::Vector2f { -100.F, 50.F});
        const auto position = drawPositionF + sf::Vector2f { 00.F, +bounds.getSize().y + m_circle.getRadius() }
        -(bounds.getSize() / 2.0F);
        //const auto textPositionF = restrict (position, { bounds.getSize().x/2,
        // bounds.getSize().y/2, 400.F, 400.F });
        const auto lines = 4;
        const auto padLeft = 20.0F;
        const auto padTop = 20.0F;
        const auto padWidth = 20.0F;
        const auto padHeight = 20.0F;
        const auto textPositionF =
            restrict (position,
                      { padLeft, padTop,
                        static_cast<float>(m_window.getSize().x) - padWidth - bounds.getSize().x,
                        static_cast<float>(m_window.getSize().y) - padHeight - bounds.getSize().y * lines }
                      );

        if(m_lastScreenPosition != screenPosition) {
            m_rect.setPosition(drawPositionF);
            //m_circle.center
            m_circle.setPosition(drawPositionF);
            UpdateCross(m_circle.getRadius(), drawPositionF);
            m_coordDisplay1.setString(fmt::format("Cursor > screen: x({}), y({}), world x({:.1f}), y({:.1f})", screenPosition.x, screenPosition.y,
                            worldPositionF.x, worldPositionF.y));
            m_coordDisplay1.setPosition(textPositionF);

            m_circle.setOutlineColor(sf::Color::Red);
            m_redrawn = true;
        } else {
            m_circle.setOutlineColor(sf::Color::Green);
            m_redrawn = false;
        }

        //auto viewportSize = m_window.getView().getViewport().getSize();
        auto viewSize = m_window.getView().getSize();
        m_coordDisplay2.setString(fmt::format("View > size x({:.1f}), y({:.1f})", viewSize.x, viewSize.y));
        auto textPosition2 = textPositionF + sf::Vector2f { 00.F, m_coordDisplay2.getLocalBounds().getSize().y };
        m_coordDisplay2.setPosition(textPosition2);

        if(m_player) {
            m_coordDisplay3.setString(fmt::format("Player > world: x({:.1f}), y({:.1f})", m_player->getPosition().x,
                            m_player->getPosition().y));
            textPosition2 = textPosition2 + sf::Vector2f { 00.F, m_coordDisplay3.getLocalBounds().getSize().y };
            m_coordDisplay3.setPosition(textPosition2);
        }

        if(m_camera) {
            auto camWorldPos = m_camera->GetRelativeWorldCoords(screenPosition);
            m_coordDisplay4.setString(fmt::format("Camera > world: x({:.1f}), y({:.1f})", camWorldPos.x,
                            camWorldPos.y));
            textPosition2 = textPosition2 + sf::Vector2f { 00.F, m_coordDisplay4.getLocalBounds().getSize().y };
            m_coordDisplay4.setPosition(textPosition2);
        }

        m_lastScreenPosition = screenPosition;
    }// Update

    void Draw(sf::RenderTarget &target, sf::RenderStates states) const {
        //target.draw(m_rect, states);
        auto oldView = target.getView();
        target.setView(target.getDefaultView());
        target.draw(m_circle, states);
        target.draw(m_cross, states);
        target.draw(m_coordDisplay1, states);
        target.draw(m_coordDisplay2, states);
        if(m_player) {
            target.draw(m_coordDisplay3, states);
        }

        if(m_camera) {
            target.draw(m_coordDisplay4, states);
        }

        target.setView(oldView);
    } // Draw

    grg::Player* m_player = nullptr;
    grg::Camera* m_camera = nullptr;

private:

    //const sf::Font &m_font;
    bool m_redrawn = false;
    sf::CircleShape m_circle { 40, 24 };
    sf::Cursor m_cursor;
    sf::RectangleShape m_rect { sf::Vector2f(20, 20) };
    sf::RenderWindow &m_window;
    sf::Text m_coordDisplay1;
    sf::Text m_coordDisplay2;
    sf::Text m_coordDisplay3;
    sf::Text m_coordDisplay4;
    sf::Vector2i m_lastScreenPosition;
    sf::VertexArray m_cross { sf::PrimitiveType::Lines, 4 };
};
void grg::Cursor::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    m_pImpl->Draw(target, states);
}

grg::Cursor::Cursor(sf::RenderWindow &window, const sf::Font &font) : m_pImpl(std::make_unique<grg::Cursor::Impl>(window, font)) {}

grg::Cursor::~Cursor() {}

void grg::Cursor::Update(sf::Time elapsed) {
    m_pImpl->Update(elapsed);
}

void grg::Cursor::SetPlayer(grg::Player* player) {
    m_pImpl->m_player = player;
}

void grg::Cursor::SetCamera(grg::Camera* camera) {
    m_pImpl->m_camera = camera;
}
