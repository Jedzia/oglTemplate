/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             setup related stuff.
 * \file       Setup.h
 * \date       2020-03-23
 * \author     Jedzia.
 *
 * modified    2020-03-23, Jedzia
 */
/*---------------------------------------------------------*/
//
// Created by Jedzia on 23.03.2020.
//

#ifndef OPENGLTEMPLATE_97F4AB5A9AED47ACBD7F1FEF78FA4B1C_SETUP_H
#define OPENGLTEMPLATE_97F4AB5A9AED47ACBD7F1FEF78FA4B1C_SETUP_H
#include "warning/SFML_Graphics.h"

namespace grg {
sf::RenderWindow createRenderWindow(unsigned int width, double ratio_antecedent, double ratio_consequent,
        const std::string &title = "SFML Window");
}
#endif//OPENGLTEMPLATE_97F4AB5A9AED47ACBD7F1FEF78FA4B1C_SETUP_H
