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
 * modified    2020-04-05, Jedzia
 */

#include "grcore/Math.h"

grcore::WindowCalculator::WindowCalculator(unsigned int width, double ratioAntecedent, double ratioConsequent) : m_width(width),
    m_ratioAntecedent(ratioAntecedent), m_ratioConsequent(ratioConsequent) {
    m_height = static_cast<unsigned int>(CalcHeight(width, ratioAntecedent, ratioConsequent));
}

double grcore::WindowCalculator::CalcHeight(unsigned int width, double ratioAntecedent, double ratioConsequent) {
    return width * ratioConsequent / ratioAntecedent;
}

unsigned int grcore::WindowCalculator::GetWidth() const {
    return m_width;
}

unsigned int grcore::WindowCalculator::GetHeight() const {
    return m_height;
}

double grcore::WindowCalculator::GetRatioAntecedent() const {
    return m_ratioAntecedent;
}

double grcore::WindowCalculator::GetRatioConsequent() const {
    return m_ratioConsequent;
}

std::tuple<double, double> grcore::WindowCalculator::GetRatio() const {
    return std::make_tuple(m_ratioAntecedent, m_ratioConsequent);
}
