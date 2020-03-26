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
 * modified    2020-03-23, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGL_TEMPLATE_PRECOMPILED_H
#define OPENGL_TEMPLATE_PRECOMPILED_H

/*#ifdef __has_feature
 #  define FMT_HAS_FEATURE(x) __has_feature(x)
 ##else
 #  define FMT_HAS_FEATURE(x) 0
 ##endif

 ##ifndef FMT_BEGIN_NAMESPACE
 #  if FMT_HAS_FEATURE(cxx_inline_namespaces) || FMT_GCC_VERSION >= 404 || \
      FMT_MSC_VER >= 1900
 #    define FMT_INLINE_NAMESPACE inline namespace
 #    define FMT_END_NAMESPACE \
      }                       \
      }
 #  else
 #    define FMT_INLINE_NAMESPACE namespace
 #    define FMT_END_NAMESPACE \
      }                       \
      using namespace v6;     \
      }
 #  endif
 #  define FMT_BEGIN_NAMESPACE \
    namespace fmtx {           \
    FMT_INLINE_NAMESPACE v6 {
 #endif*/

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

//#if USE_SPDLOG
#include <spdlog/spdlog.h>
#include <grcore/GrCore.h>
#include <grgraphics/grgraphics.h>
//#endif

#endif //OPENGL_TEMPLATE_PRECOMPILED_H
