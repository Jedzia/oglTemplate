/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the sfml-test.cpp class.
 * \file       sfml-test.cpp
 * \date       2020-01-23
 * \author     Jedzia.
 *
 * modified    2020-01-23, Jedzia
 */
/*---------------------------------------------------------*/

//
// Created by Jedzia on 17.03.2020.
//

#include <grgraphics/grgraphics.h>
#if defined(__clang__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma clang diagnostic ignored "-Wsign-conversion"
#  pragma clang diagnostic ignored "-Wdouble-promotion"
#endif
#if defined(__GNUC__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma GCC diagnostic ignored "-Wsign-conversion"
#  pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif

#include <fmt/format.h>
#include <spdlog/spdlog.h>
namespace grg {
/** Brief description of $(fclass), update
 *  Detailed description.
 *  @param elapsed TODO
 */
void update(sf::Time elapsed) {
    std::string msg = fmt::format("update() Time is {}μs", elapsed.asMicroseconds());
    spdlog::info(msg);
}
}
