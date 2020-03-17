//
// Created by Jedzia on 17.03.2020.
//

#ifndef OPENGLTEMPLATE_SFML_GRAPHICS_H
#define OPENGLTEMPLATE_SFML_GRAPHICS_H

// ToDo: This is a temporary fix as SFML does not like my inhumane pursuit of warnings.

// Warn for implicit conversions that may change the sign of an integer value, like assigning a
// signed integer expression to an unsigned integer variable. An explicit cast silences the warning.
// In C, this option is enabled also by -Wconversion.

// Disable for CLang
#if defined(__clang__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma clang diagnostic ignored "-Wsign-conversion"
#endif

#include <SFML/Graphics.hpp>

// Re-Enable warning
#if defined(__clang__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma clang diagnostic warning "-Wsign-conversion"
#endif
//

#endif //OPENGLTEMPLATE_SFML_GRAPHICS_H
