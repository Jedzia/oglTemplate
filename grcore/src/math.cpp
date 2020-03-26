/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the math.cpp class.
 * \file       math.cpp
 * \date       2020-03-23
 * \author     Jedzia.
 *
 * modified    2020-03-23, Jedzia
 */
/*---------------------------------------------------------*/
//
// Created by Jedzia on 23.03.2020.
//

#include "grcore/math.h"
core::WindowCalculator::WindowCalculator(unsigned int width, double ratioAntecedent, double ratioConsequent) : m_width(width),
    m_ratioAntecedent(ratioAntecedent), m_ratioConsequent(ratioConsequent) {
    m_height = static_cast<unsigned int>(CalcHeight(width, ratioAntecedent, ratioConsequent));
}

/*core::WindowCalculator::WindowCalculator(double ratioAntecedent, double ratioConsequent, int height) : m_height(height),
    m_ratioAntecedent(ratioAntecedent), m_ratioConsequent(ratioConsequent) {}*/

double core::WindowCalculator::CalcHeight(unsigned int width, double ratioAntecedent, double ratioConsequent) {
    return width * ratioConsequent / ratioAntecedent;
}
unsigned int core::WindowCalculator::GetWidth() const {
    return m_width;
}
unsigned int core::WindowCalculator::GetHeight() const {
    return m_height;
}
double core::WindowCalculator::GetRatioAntecedent() const {
    return m_ratioAntecedent;
}
double core::WindowCalculator::GetRatioConsequent() const {
    return m_ratioConsequent;
}
std::tuple<double, double> core::WindowCalculator::GetRatio() const {
    return std::make_tuple(m_ratioAntecedent, m_ratioConsequent);
}
