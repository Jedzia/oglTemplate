/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the resource.cpp class.
 * \file       resource.cpp
 * \date       2020-03-25
 * \author     Jedzia.
 *
 * modified    2020-03-26, Jedzia
 */
/*---------------------------------------------------------*/

#include "grcore/Resource.h"
#include "grcore/warning/FMT_format_log.h"
#include "GrCore.rc.s.Resource.h"
#include <iostream>
#include <stdexcept>


grcore::Resource::Resource(int resourceName) : m_id(resourceName) {
    spdlog::debug(" {1}:{2} +++ Constructor [{0}] (resourceName={0}) called. +++", __PRETTY_FUNCTION__, __FILE__,
                  __LINE__, resourceName);
}

grcore::Resource::~Resource() {
    spdlog::debug(" {1}:{2} +++ Destructor  [{0}]  called. +++", __PRETTY_FUNCTION__, __FILE__, __LINE__);
    // no need to free something, its a embedded resource.
}

std::tuple<const void *, size_t, int> grcore::Resource::Get() {
    int error = 0;
    auto size = 0;
    //auto data = static_cast<const void *>(::LockResource(rcData));
    const void *data = nullptr;

    //using namespace res;
    switch (m_id) {
        case IDR_MYFONT:
            data = static_cast<const void *>(IDR_MYFONT_D);
            size = static_cast<int>(IDR_MYFONT_D_size);
            break;
        case IDR_DATA1:
            data = static_cast<const void *>(IDR_DATA1_D);
            size = static_cast<int>(IDR_DATA1_D_size);
            break;
        default:
            throw std::runtime_error(
                    fmt::format("[{}]: unhandled default case with resource id={}", __PRETTY_FUNCTION__, m_id));
    }

    return {
            data, size, error
    };
} // core::Resource::Get
