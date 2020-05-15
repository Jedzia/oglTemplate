/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Common.cpp class.
 * \file       Common.cpp
 * \date       2020-04-08
 * \author     Jedzia.
 *
 * modified    2020-04-08, Jedzia
 */
/*---------------------------------------------------------*/
#include "grgraphics/Utility/Common.h"
#include <grcore/Resource.h>
#include <spdlog/spdlog.h>

void grg::loadDebugFont(sf::Font &debugFont) {
    const int fontId = 129;
    auto fi = debugFont.getInfo();
    if(!(fi.family == "")) {
        spdlog::info("[{}] Font from resource (id={}): '{}' already loaded.", __PRETTY_FUNCTION__, fontId, fi.family);
        return;
    }

    spdlog::warn("[{}] Loading Font from resource (id={}).", __PRETTY_FUNCTION__, fontId);
    grcore::Resource res(fontId);
    auto [data, size, error] = res.Get();
    //std::cout << "data:" << data << std::endl;
    //std::cout << "size:" << size << std::endl;
    //std::cout << "error:" << error << std::endl;
    if(!error) {
        bool success = debugFont.loadFromMemory(data, size);
        if(success) {
            fi = debugFont.getInfo();
            spdlog::warn("[{}] Loaded Font from resource (id={}): '{}'.", __PRETTY_FUNCTION__, fontId, fi.family);
        } else {
            spdlog::error("[{}] ERROR loading Font from resource (id={}).", __PRETTY_FUNCTION__, fontId);
        }
    }
} // grg::loadDebugFont
