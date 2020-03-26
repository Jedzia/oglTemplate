/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the resource.h class.
 * \file       resource.h
 * \date       2020-03-25
 * \author     Jedzia.
 *
 * modified    2020-03-25, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGLTEMPLATE_E425AE61B7064A80B6F46CA476262B60_RESOURCE_H
#define OPENGLTEMPLATE_E425AE61B7064A80B6F46CA476262B60_RESOURCE_H

#include <tuple>

namespace core {
class Resource final {
public:

    Resource(int resourceName);
    ~Resource();

    /*static void SetHandle(void* handle) {
        p_handle = handle;
    }*/

    [[nodiscard]] std::tuple<const void *, size_t, int> Get();

private:

    int m_id = 0;
    //static void* p_handle;
};
}// namespace core

#endif//OPENGLTEMPLATE_E425AE61B7064A80B6F46CA476262B60_RESOURCE_H
