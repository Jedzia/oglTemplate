/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the precompiled.h class.
 * \file       precompiled.h
 * \date       2020-03-15
 * \author     Jedzia.
 *
 * modified    2020-03-15, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGL_TEMPLATE_PRECOMPILED_H
#define OPENGL_TEMPLATE_PRECOMPILED_H

#if defined(__GNUC__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
#include <fmt/format.h>
#if defined(__GNUC__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma GCC diagnostic warning "-Wsign-conversion"
#endif
//
// warning : implicit conversion changes signedness
#if defined(__clang__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma clang diagnostic ignored "-Wsign-conversion"
#endif
#include <SFML/Graphics.hpp>
#if defined(__clang__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma clang diagnostic warning "-Wsign-conversion"
#endif
//
#include <SFML/System/Clock.hpp>
#include <SFML/System/Thread.hpp>
#include <iostream>

#if USE_DOC_OPTS
#  include "docopt.h"
#endif

#if USE_SPDLOG
#  include <spdlog/spdlog.h>
#endif

#endif //OPENGL_TEMPLATE_PRECOMPILED_H
