/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the CoordSystem.cpp class.
 * \file       CoordSystem.cpp
 * \date       2020-03-23
 * \author     Jedzia.
 *
 * modified    2020-03-23, Jedzia
 */
/*---------------------------------------------------------*/
#include "grgraphics/Drawables/CoordSystem.h"
#include "grgraphics/warning/SFML_Graphics.h"
#include <array>
#include <iostream>
#include <vector>

/*struct grg::CoordSystem::Impl {
    Impl() {}
    Impl() {
    }
   };*/

struct grg::CoordSystem::Impl {
    typedef std::unique_ptr<sf::Drawable> DrawPtr;

public:

    Impl(const sf::FloatRect &dimensions, const sf::Font &font) : m_dimensions(dimensions), m_font(font) {
        std::cout << "+++ Constructor " << __PRETTY_FUNCTION__ << " called. +++" << std::endl;
        //std::unique_ptr<sf::Drawable> shape = std::make_unique<sf::RectangleShape>(sf::Vector2f{
        // 60.F, 60.F });
        //m_drawables.push_back(std::make_unique<sf::RectangleShape>(sf::Vector2f{ 60.F, 60.F }));
        //m_drawables.end()->get()->setPosition(400,400);
        //->setPosition(400,400)
        m_drawables.push_back(DrawPtr(m_pRect = new sf::RectangleShape({ 60.F, 60.F })));
        m_pRect->setPosition(400, 400);

        //auto line = new sf::Lines({ 60.F, 60.F });
        //m_drawables.push_back(DrawPtr(line));

        AddLine({ 70.F, 120.F }, { 370.F, 520.F }, sf::Color::Green);
        AddLine({ 270.F, 620.F }, { 70.F, 20.F }, sf::Color::Yellow);

        AddLine({ dimensions.left, dimensions.top }, { dimensions.width, dimensions.height }, sf::Color::Red);

        float stepWidth = 50.0F;

        // X-Axis
        float horizontalOffset = -50.0F;
        sf::Vector2f xStart({ dimensions.left, dimensions.height + horizontalOffset });
        sf::Vector2f xEnd({ dimensions.width, dimensions.height + horizontalOffset });
        AddLine(xStart, xEnd, sf::Color::White);

        // Y-Axis
        float verticalOffset = 50.0F;
        sf::Vector2f yStart({ dimensions.left + verticalOffset, dimensions.top });
        sf::Vector2f yEnd({ dimensions.left + verticalOffset, dimensions.height });
        AddLine(yStart, yEnd, sf::Color::White);

        // X-Axis die striche<- namen
        auto xBaseline = dimensions.height + horizontalOffset;

        for(float x = stepWidth + verticalOffset; x < dimensions.width; x += stepWidth) {
            AddLine({ x, xBaseline - 20 }, { x, xBaseline + 20 }, sf::Color::Blue);
            //AddLine(xStart + 5.F, xEnd, sf::Color::White);
        }
        // Y-Axis die striche<- namen .. ToDo: invers abarbeiten ... oben ist ja 0
        auto yBaseline = dimensions.left + verticalOffset;

        for(float y = stepWidth + horizontalOffset; y < dimensions.height; y += stepWidth) {
            AddLine({ yBaseline - 20, y }, { yBaseline + 20, y }, sf::Color::Blue);
            //AddLine(xStart + 5.F, xEnd, sf::Color::White);
        }
        static_cast<void>(m_font);

        m_vertz[0].position = sf::Vector2f(100, 0);
        m_vertz[1].position = sf::Vector2f(200, 0);
        m_vertz[2].position = sf::Vector2f(300, 50);
        m_vertz[3].position = sf::Vector2f(400, 20);
    }

    inline void AddLine(const sf::Vector2f &start, const sf::Vector2f &end, sf::Color color = sf::Color::White) {
        //std::cout << "AddLine: " << start.x << ", " << start.y << " - " << end.x << ", " << end.y
        // << std::endl;
        m_vertices.push_back(sf::Vertex(start, color));
        m_vertices.push_back(sf::Vertex(end, color));
    }

    ~Impl() {
        std::cout << "+++ Destructor  " << __PRETTY_FUNCTION__ << " called. +++" << std::endl;
    }

    int DoSomething() const {
        //std::cout << "> grg::CoordSystem::Impl::DoSomething()" << std::endl;
        return m_n;
    }

    void Draw(sf::RenderTarget &target, sf::RenderStates states) const {
        //sf::Drawable::draw(target, states);
        //static_cast<void>(target);
        //static_cast<void>(states);
        for(const auto &item : m_drawables) {
            //item->draw(target, states);
            target.draw(*item, states);
        }
        /*sf::Vertex vertices[2] =
           {
            sf::Vertex({70.F, 120.F}),
            sf::Vertex({370.F, 520.F})
           };

           target.draw(vertices, 2, sf::Lines, states);*/
        target.draw(m_vertices.data(), m_vertices.size(), sf::Lines, states);
        target.draw(m_vertz, states);
    }

private:

    int m_n;// private data
    sf::FloatRect m_dimensions;
    std::vector<DrawPtr> m_drawables;
    //std::array<sf::Vertex> m_vertices;
    std::vector<sf::Vertex> m_vertices;// alternative is to use sf::VertexArray.
    //sf::VertexArray m_vertices;
    // managed by vector
    sf::RectangleShape* m_pRect;
    const sf::Font &m_font;
    sf::VertexArray m_vertz {sf::PrimitiveType::LineStrip, 4};
};

void grg::CoordSystem::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    //sf::Drawable::draw(target, states);
    //static_cast<void>(target);
    //static_cast<void>(states);
    m_pImpl->Draw(target, states);
}

grg::CoordSystem::CoordSystem(const sf::FloatRect &dimensions, const sf::Font &font)
//: m_pImpl(std::make_unique<grg::CoordSystem::Impl>(sf::FloatRect({0.F, 0.F}, {600.F, 600.F}))) {
    : m_pImpl(std::make_unique<grg::CoordSystem::Impl>(dimensions, font)) {
    //m_pImpl.reset(new grg::CoordSystem::Impl());
}

grg::CoordSystem::~CoordSystem() {}
