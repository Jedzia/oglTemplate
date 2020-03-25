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

/*struct grg::CoordSystem::impl {
    impl() {}
    ~impl() {
    }
   };*/

struct grg::CoordSystem::impl {
    typedef std::unique_ptr<sf::Drawable> draw_ptr;

public:

    impl(const sf::FloatRect &dimensions) : m_dimensions(dimensions) {
        std::cout << "+++ Constructor grg::CoordSystem::impl called. +++" << std::endl;
        //std::unique_ptr<sf::Drawable> shape = std::make_unique<sf::RectangleShape>(sf::Vector2f{
        // 60.F, 60.F });
        //m_drawables.push_back(std::make_unique<sf::RectangleShape>(sf::Vector2f{ 60.F, 60.F }));
        //m_drawables.end()->get()->setPosition(400,400);
        //->setPosition(400,400)
        m_drawables.push_back(draw_ptr(p_rect = new sf::RectangleShape({ 60.F, 60.F })));
        p_rect->setPosition(400, 400);

        //auto line = new sf::Lines({ 60.F, 60.F });
        //m_drawables.push_back(draw_ptr(line));

        addLine({70.F, 120.F}, {370.F, 520.F}, sf::Color::Green);
        addLine({270.F, 620.F}, {70.F, 20.F}, sf::Color::Yellow);

        addLine({dimensions.left, dimensions.top}, {dimensions.width, dimensions.height}, sf::Color::Red);

        float stepWidth = 50.0F;

        // X-Axis
        float horizontalOffset = -50.0F;
        sf::Vector2f x_start({dimensions.left, dimensions.height + horizontalOffset});
        sf::Vector2f x_end({dimensions.width, dimensions.height + horizontalOffset});
        addLine(x_start, x_end, sf::Color::White);

        // Y-Axis
        float verticalOffset = 50.0F;
        sf::Vector2f y_start({dimensions.left + verticalOffset, dimensions.top});
        sf::Vector2f y_end({dimensions.left + verticalOffset, dimensions.height});
        addLine(y_start, y_end, sf::Color::White);

        // X-Axis die striche<- namen
        auto x_baseline = dimensions.height + horizontalOffset;

        for(float x = stepWidth + verticalOffset; x < dimensions.width; x += stepWidth) {
            addLine({x, x_baseline - 20}, {x, x_baseline + 20}, sf::Color::Blue);
            //addLine(x_start + 5.F, x_end, sf::Color::White);
        }
        // Y-Axis die striche<- namen .. ToDo: invers abarbeiten ... oben ist ja 0
        auto y_baseline = dimensions.left + verticalOffset;

        for(float y = stepWidth + horizontalOffset; y < dimensions.height; y += stepWidth) {
            addLine({y_baseline - 20, y}, {y_baseline + 20, y }, sf::Color::Blue);
            //addLine(x_start + 5.F, x_end, sf::Color::White);
        }
    }

    inline
    void addLine(const sf::Vector2f &start, const sf::Vector2f &end, sf::Color color = sf::Color::White) {
        std::cout << "addLine: " << start.x << ", " << start.y << " - " << end.x << ", " << end.y << std::endl;
        m_vertices.push_back(sf::Vertex(start, color));
        m_vertices.push_back(sf::Vertex(end, color));
    }

    ~impl() {
        std::cout << "+++ Destructor  grg::CoordSystem::impl called. +++" << std::endl;
    }

    int DoSomething() const {
        //std::cout << "> grg::CoordSystem::impl::DoSomething()" << std::endl;
        return n;
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const {
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
    }

private:

    int n; // private data
    sf::FloatRect m_dimensions;
    std::vector<draw_ptr> m_drawables;
    //std::array<sf::Vertex> m_vertices;
    std::vector<sf::Vertex> m_vertices; // alternative is to use sf::VertexArray.
    //sf::VertexArray m_vertices;
    // managed by vector
    sf::RectangleShape* p_rect;
};

void grg::CoordSystem::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    //sf::Drawable::draw(target, states);
    //static_cast<void>(target);
    //static_cast<void>(states);
    p_impl->draw(target, states);
}

grg::CoordSystem::CoordSystem(const sf::FloatRect &dimensions)
//: p_impl(std::make_unique<grg::CoordSystem::impl>(sf::FloatRect({0.F, 0.F}, {600.F, 600.F}))) {
    : p_impl(std::make_unique<grg::CoordSystem::impl>(dimensions)) {
    //p_impl.reset(new grg::CoordSystem::impl());
}

grg::CoordSystem::~CoordSystem() {}
