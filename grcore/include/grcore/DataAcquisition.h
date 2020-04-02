/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the DataAcquisition.h class.
 * \file       DataAcquisition.h
 * \date       2020-04-02
 * \author     Jedzia.
 *
 * modified    2020-04-02, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef OPENGLTEMPLATE_5C801ED2691B4617A2BA8F75C73BD12F_DATAAQUISITION_H
#define OPENGLTEMPLATE_5C801ED2691B4617A2BA8F75C73BD12F_DATAAQUISITION_H

#include <chrono>
#include <fstream>
#include <string>

namespace grcore {
template<const char TDelimiter>
class CsvFile {
public:

    CsvFile(const std::string &filepath) : M_Filepath(filepath) {
        m_outputStream.open(filepath);
    }

    bool WriteData(const float &data) {
#if 1// MinGW, see https://github.com/msys2/MINGW-packages/issues/5086#issuecomment-476499828
        typedef std::chrono::steady_clock Clock;
#else
        typedef std::chrono::high_resolution_clock clock;
#endif
        auto dataTimepoint = Clock::now();
        auto dataTime = std::chrono::time_point_cast<std::chrono::microseconds>(dataTimepoint).time_since_epoch().count();
        m_outputStream << dataTime << TDelimiter;
        m_outputStream << data;
        m_outputStream << "\n";
        return true;
    }

private:

    const std::string M_Filepath;
    std::ofstream m_outputStream;
};
}
#endif //OPENGLTEMPLATE_5C801ED2691B4617A2BA8F75C73BD12F_DATAAQUISITION_H
