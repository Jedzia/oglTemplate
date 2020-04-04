/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Common.h class.
 * \file       Common.h
 * \date       2020-04-04
 * \author     Jedzia.
 *
 * modified    2020-04-04, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef OPENGLTEMPLATE_E836ABB942FC4999A4FB04827232DD5A_COMMON_H
#define OPENGLTEMPLATE_E836ABB942FC4999A4FB04827232DD5A_COMMON_H

//  Private copy constructor and copy assignment ensure classes derived from
//  class noncopyable cannot be copied.
namespace grcore {
// noncopyable derives from base_token to enable Type Traits to detect
// whether a type derives from noncopyable without needing the definition
// of noncopyable itself.
//
// The definition of base_token is macro-guarded so that Type Trais can
// define it locally without including this header, to avoid a dependency
// on Core.
struct BaseToken {};

/** @class NonCopyable:
 *  Private copy constructor and copy assignment ensure classes derived from class NonCopyable
 *  cannot be copied.
 */
class NonCopyable : BaseToken {
protected:

    constexpr NonCopyable() = default;

    ~NonCopyable() = default;

private:

    NonCopyable(const NonCopyable &) = delete;
    NonCopyable &operator=(const NonCopyable &) = delete;
};
}
#endif //OPENGLTEMPLATE_E836ABB942FC4999A4FB04827232DD5A_COMMON_H
