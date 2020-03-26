/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Setup.cpp class.
 * \file       Setup.cpp
 * \date       2020-03-23
 * \author     Jedzia.
 *
 * modified    2020-03-23, Jedzia
 */
/*---------------------------------------------------------*/
#include "grgraphics/Setup.h"
#include "grgraphics/warning/FMT_format.h"
#include <grcore/Math.h>
#include <iostream>
#include <utility>

sf::RenderWindow grg::createRenderWindow(unsigned int width, double ratio_antecedent, double ratio_consequent,
        const std::string &title_string) {
    core::WindowCalculator wc(width, ratio_antecedent, ratio_consequent);
    auto title = fmt::format("{4} ({0}, {1} -> {2:.1f}:{3})", wc.GetWidth(), wc.GetHeight(), wc.GetRatioAntecedent(),
            wc.GetRatioConsequent(), title_string);
    return sf::RenderWindow(sf::VideoMode(wc.GetWidth(), wc.GetHeight()), title);
}
