/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the CoordGraph.cpp class.
 * \file       CoordGraph.cpp
 * \date       2020-04-01
 * \author     Jedzia.
 *
 * modified    2020-04-01, Jedzia
 */
/*---------------------------------------------------------*/

#include "grcore/warning/FMT_format_log.h"
#include "grgraphics/Drawables/CoordGraph.h"
#include <Constants.h>

grg::CoordGraph::CoordGraph(const sf::FloatRect &dimensions, const sf::Font &font) : CoordSystem(dimensions, font) {
    float horizontalOffset = -50.0F;

    for(std::size_t x = 0; x < Graph_Size; ++x) {
        m_vertices[x].position.x = x + 50.0F - horizontalOffset;
        m_vertices[x].position.y = G_Display_Height / 2;
    }
}

grg::CoordGraph::~CoordGraph() {}

void grg::CoordGraph::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    CoordSystem::draw(target, states);
    target.draw(m_vertices, states);

    m_drawCalls++;
}

void grg::CoordGraph::OnUpdate(sf::Time elapsed) {
    CoordSystem::OnUpdate(elapsed);
    if(m_displayFrametime) {
        displayFrameTime(elapsed);
    }
}

void grg::CoordGraph::displayFrameTime(const sf::Time &elapsed) {
    const float elapsedSeconds = elapsed.asSeconds();
    const float defaultFrameTime = 1.0F / grg::G_FRAME_RATE_LIMIT;
    constexpr float displayFlatline = grg::CoordGraph::G_Display_Height / 2;
    constexpr float displayFactor = 400.0F;
    float normTime = defaultFrameTime / elapsedSeconds;
    this->m_vertices[this->m_drawCalls % grg::CoordGraph::Graph_Size].position.y = displayFlatline - ((1.0F - normTime) * displayFactor);
    //spdlog::trace("defFT {:.3f} / elapsed {:.3f} = {:.3f}.", defaultFrameTime, elapsedSeconds, normTime);
}

void grg::CoordGraph::SetGraphValue(float value) {
    m_displayFrametime = false;
    size_t index = this->m_drawCalls % grg::CoordGraph::Graph_Size;
    this->m_vertices[index].position.y = value;
    spdlog::trace("i[{}] = {:.3f}.", index, value);
}
