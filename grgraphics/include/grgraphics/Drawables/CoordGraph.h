/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the CoordGraph.h class.
 * \file       CoordGraph.h
 * \date       2020-04-01
 * \author     Jedzia.
 *
 * modified    2020-04-01, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGLTEMPLATE_AB3283CA4C25421EA6E21045A1E54CFD_COORDGRAPH_H
#define OPENGLTEMPLATE_AB3283CA4C25421EA6E21045A1E54CFD_COORDGRAPH_H



#include "CoordSystem.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <cstddef>

namespace grg {
class CoordGraph : public CoordSystem {
public:
    static constexpr std::size_t Graph_Size = 1024;
    static constexpr float G_Display_Height = 720.0F;

    CoordGraph(const sf::FloatRect &dimensions, const sf::Font &font);
    virtual ~CoordGraph();

    void OnUpdate(sf::Time elapsed) override;

    void SetGraphValue(float value);

protected:

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    void displayFrameTime(const sf::Time &elapsed);

    sf::VertexArray m_vertices {sf::PrimitiveType::LineStrip, Graph_Size};
    mutable std::size_t m_drawCalls = 0;
    bool m_displayFrametime = true;
};
}

#endif //OPENGLTEMPLATE_AB3283CA4C25421EA6E21045A1E54CFD_COORDGRAPH_H
