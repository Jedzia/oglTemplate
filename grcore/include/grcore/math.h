/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the math.h class.
 * \file       math.h
 * \date       2020-03-23
 * \author     Jedzia.
 *
 * modified    2020-03-23, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGLTEMPLATE_884460FB4F67411EB0A561A69967A142_MATH_H
#define OPENGLTEMPLATE_884460FB4F67411EB0A561A69967A142_MATH_H

#include <tuple>

namespace core {
class WindowCalculator {
public:

    explicit WindowCalculator(unsigned int width, double ratio_antecedent, double ratio_consequent);
    // explicit WindowCalculator(double ratio_antecedent, double ratio_consequent, int height);

    double calcHeight(unsigned int width, double ratio_antecedent, double ratio_consequent);

    //double calcWidth(int height, double ratio_antecedent, double ratio_consequent);
    //
    [[nodiscard]] unsigned int getWidth() const;

    [[nodiscard]] unsigned int getHeight() const;

    [[nodiscard]] double getRatioAntecedent() const;

    [[nodiscard]] double getRatioConsequent() const;

    //
    [[nodiscard]] std::tuple<double, double> getRatio() const;

private:

    unsigned int m_width = 0;
    unsigned int m_height = 0;
    //std::tuple<double, double> m_ratio;
    double m_ratio_antecedent = 0;
    double m_ratio_consequent = 0;
};
}// namespace core

#endif//OPENGLTEMPLATE_884460FB4F67411EB0A561A69967A142_MATH_H