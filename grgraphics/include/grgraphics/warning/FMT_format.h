//
// Created by Jedzia on 17.03.2020.
//

#ifndef OPENGLTEMPLATE_7632BB2FFD294C358889253541C3C244_FMT_FORMAT_H
#define OPENGLTEMPLATE_7632BB2FFD294C358889253541C3C244_FMT_FORMAT_H

// ToDo: This is a temporary fix as fmt::format does not like my inhumane pursuit of warnings.

// Warn for implicit conversions that may change the sign of an integer value, like assigning a
// signed integer expression to an unsigned integer variable. An explicit cast silences the warning.
// In C, this option is enabled also by -Wconversion.

// Disable for GCC
#if defined(__GNUC__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

#include <fmt/format.h>

// Re-Enable warning
#if defined(__GNUC__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma GCC diagnostic warning "-Wsign-conversion"
#endif
//
// Disable for CLang
#if defined(__clang__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma clang diagnostic ignored "-Wsign-conversion"
#endif

#include <fmt/format.h>

// Re-Enable warning
#if defined(__clang__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma clang diagnostic warning "-Wsign-conversion"
#endif
//

#endif //OPENGLTEMPLATE_7632BB2FFD294C358889253541C3C244_FMT_FORMAT_H
