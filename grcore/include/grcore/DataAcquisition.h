/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the header-only CsvFile class.
 * \file       DataAcquisition.h
 * \date       2020-04-02
 * \author     Jedzia.
 *
 * modified    2020-04-05, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef OPENGLTEMPLATE_E247D1BA28B84E84B56D5C8D5C2BB424_DATAACQUISITION_H
#define OPENGLTEMPLATE_E247D1BA28B84E84B56D5C8D5C2BB424_DATAACQUISITION_H

#include <chrono>
#include <fstream>
#include <string>

namespace grcore {
/** @class CsvFile:
 *  A Comma Separated Data File.
 */
template<const char TDelimiter>
class CsvFile {
public:

    /** @brief Create a CSV-File with a given path.
     *
     * @param filepath The full path to the file been created.
     */
    CsvFile(const std::string &filepath) : M_Filepath(filepath) {
        m_outputStream.open(filepath);
    }

    /** @brief Write a data item to the file.
     *
     *  Writes the given data, prefixed by a unit time point in microseconds since epoch(1.1.1970).
     *  @param data A single precision floating point datum that is written in the file.
     *  @return <b>true</b> on success.
     */
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
#endif //OPENGLTEMPLATE_E247D1BA28B84E84B56D5C8D5C2BB424_DATAACQUISITION_H
