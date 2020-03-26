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

#ifndef OPENGLTEMPLATE_07CF1308072042EB975B05372D54C611_MATH_H
#define OPENGLTEMPLATE_07CF1308072042EB975B05372D54C611_MATH_H

#include <tuple>

namespace core {
class WindowCalculator {
public:

    explicit WindowCalculator(unsigned int width, double ratioAntecedent, double ratioConsequent);
    // explicit WindowCalculator(double ratio_antecedent, double ratio_consequent, int height);

    static double CalcHeight(unsigned int width, double ratioAntecedent, double ratioConsequent);

    //double calcWidth(int height, double ratio_antecedent, double ratio_consequent);
    //
    [[nodiscard]] unsigned int GetWidth() const;

    [[nodiscard]] unsigned int GetHeight() const;

    [[nodiscard]] double GetRatioAntecedent() const;

    [[nodiscard]] double GetRatioConsequent() const;

    [[nodiscard]] std::tuple<double, double> GetRatio() const;

private:

    unsigned int m_width = 0;
    unsigned int m_height = 0;
    //std::tuple<double, double> m_ratio;
    double m_ratioAntecedent = 0;
    double m_ratioConsequent = 0;
};
}// namespace core

#endif//OPENGLTEMPLATE_07CF1308072042EB975B05372D54C611_MATH_H
