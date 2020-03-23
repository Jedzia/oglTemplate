#include "grgraphics/Setup.h"
#include "grgraphics/warning/FMT_format.h"
#include <iostream>
#include <grcore/math.h>
#include <utility>

sf::RenderWindow grg::createRenderWindow(unsigned int width, double ratio_antecedent, double ratio_consequent) {
    core::WindowCalculator wc(width, ratio_antecedent, ratio_consequent);
    auto title = fmt::format("SFML Window ({0}, {1} -> {2:.1f}:{3})", wc.getWidth(), wc.getHeight(),
      wc.getRatioAntecedent(), wc.getRatioConsequent());
    return sf::RenderWindow(sf::VideoMode(wc.getWidth(), wc.getHeight()), title);
}
