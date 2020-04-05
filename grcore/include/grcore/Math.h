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
 * modified    2020-04-05, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGLTEMPLATE_07CF1308072042EB975B05372D54C611_MATH_H
#define OPENGLTEMPLATE_07CF1308072042EB975B05372D54C611_MATH_H

#include <tuple>

namespace grcore {
/** @class WindowCalculator:
 *  Calculates window dimensions by ratio.
 */
class WindowCalculator {
public:

    /**
     * @brief Creates a new instance by width and ratio.
     *
     * The height is calculated by width and ratio.
     * @param width The horizontal width of the window.
     * @param ratioAntecedent Left side of the ratio calculation, as 16 in 16:9.
     * @param ratioConsequent Right side of the ratio calculation, as 9 in 16:9.
     */
    explicit WindowCalculator(unsigned int width, double ratioAntecedent, double ratioConsequent);
    // explicit WindowCalculator(double ratio_antecedent, double ratio_consequent, int height);

    /** @brief Calculate the height by width and ratio.
     *
     * The height is calculated by width and ratio.
     * @param width The horizontal width of the window.
     * @param ratioAntecedent Left side of the ratio calculation, as 16 in 16:9.
     * @param ratioConsequent Right side of the ratio calculation, as 9 in 16:9.
     *  @return the height resulting from the calculation of the parameters.
     */
    static double CalcHeight(unsigned int width, double ratioAntecedent, double ratioConsequent);

    /** @brief Get the window width.
     *  @return the width of the window.
     */
    [[nodiscard]] unsigned int GetWidth() const;

    /** @brief Get the window height.
     *  @return the height of the window.
     */
    [[nodiscard]] unsigned int GetHeight() const;

    /** @brief Get the window ratio.
     *  @return the left hand side of the ratio of the window, like 16 in 16:9.
     */
    [[nodiscard]] double GetRatioAntecedent() const;

    /** @brief Get the window ratio.
     *  @return the right hand side of the ratio of the window, like 9 in 16:9.
     */
    [[nodiscard]] double GetRatioConsequent() const;

    /** @brief Get the window ratio as tuple.
     *  @return the ratio of the window, tuple(16, 9) for a 16:9 ratio.
     */
    [[nodiscard]] std::tuple<double, double> GetRatio() const;

private:

    unsigned int m_width = 0;
    unsigned int m_height = 0;
    double m_ratioAntecedent = 0;
    double m_ratioConsequent = 0;
};
}// namespace grcore

#endif//OPENGLTEMPLATE_07CF1308072042EB975B05372D54C611_MATH_H
