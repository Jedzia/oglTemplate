/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Telemetry.cpp class.
 * \file       Telemetry.cpp
 * \date       2020-04-04
 * \author     Jedzia.
 *
 * modified    2020-04-04, Jedzia
 */
/*---------------------------------------------------------*/
#include "grcore/Telemetry.h"
#include "grcore/Utility/TcpClient.h"
#include <spdlog/spdlog.h>
#include <iostream>

//grcore::util::TcpClient G_CLIENT{true};

bool grcore::writeTelemetryData(const double &data) {
    // Used as a blocker. Once an error occurred, we shutdown the whole story.
    static bool skipMe = false;
    if(skipMe) {
        return false;
    }

    try {
        static grcore::util::TcpClient client {
            true
        };
        client.SendData(data);
    }
    catch(std::exception &ex) {
        skipMe = true;
        //std::cerr << "Error: " << ex.what() << std::endl;
        spdlog::error("Exception in '{}': {}", __PRETTY_FUNCTION__, ex.what());
    }
    return true;
} // grcore::writeTelemetryData
