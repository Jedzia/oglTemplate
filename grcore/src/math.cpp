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
core::WindowCalculator::WindowCalculator(unsigned int width, double ratio_antecedent, double ratio_consequent) : m_width(width),
    m_ratio_antecedent(ratio_antecedent), m_ratio_consequent(ratio_consequent) {
    m_height = static_cast<unsigned int>(calcHeight(width, ratio_antecedent, ratio_consequent));
}

/*core::WindowCalculator::WindowCalculator(double ratio_antecedent, double ratio_consequent, int height) : m_height(height),
    m_ratio_antecedent(ratio_antecedent), m_ratio_consequent(ratio_consequent) {}*/

double core::WindowCalculator::calcHeight(unsigned int width, double ratio_antecedent, double ratio_consequent) {
    return width * ratio_consequent / ratio_antecedent;
}
unsigned int core::WindowCalculator::getWidth() const {
    return m_width;
}
unsigned int core::WindowCalculator::getHeight() const {
    return m_height;
}
double core::WindowCalculator::getRatioAntecedent() const {
    return m_ratio_antecedent;
}
double core::WindowCalculator::getRatioConsequent() const {
    return m_ratio_consequent;
}
std::tuple<double, double> core::WindowCalculator::getRatio() const {
    return std::make_tuple(m_ratio_antecedent, m_ratio_consequent);
}
