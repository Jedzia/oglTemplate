/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TcpClient.h class.
 * \file       TcpClient.h
 * \date       2020-04-03
 * \author     Jedzia.
 *
 * modified    2020-04-04, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef OPENGLTEMPLATE_941E012CE7D14429BBE2EA958FFE4B4A_TCPCLIENT_H
#define OPENGLTEMPLATE_941E012CE7D14429BBE2EA958FFE4B4A_TCPCLIENT_H

#include "../Common.h"
#include <cstddef>
#include <experimental/propagate_const>
#include <memory>
#include <string>

namespace grcore {
namespace util {
const std::string G_TELEMETRY_DEFAULT_ADDRESS = "localhost";
const std::string G_TELEMETRY_DEFAULT_PORT = "27015";

/** @class TcpClient:
 *  Connect to a Server specified by G_TELEMETRY_DEFAULT_ADDRESS and G_TELEMETRY_DEFAULT_PORT.
 */
class TcpClient : public NonCopyable {
//        class TcpClient : public grcore::NonCopyable<TcpClient> {

public:

    TcpClient();

    explicit TcpClient(bool openConnection);

    virtual ~TcpClient();

    /** Send a file to the server.
     *  @param filename The path to the file on disk.
     */
    void SendFile(const std::string &filename);

    /** Send a double datum to the server.
     *
     *  The 8 byte of double precission floating point data is prefixed with 8 byte specifying the
     *  unix time since epoch in milliseconds.
     *  @param data Double precission floating point data to transmit.
     */
    void SendData(const double &data);

    /** Determine the size of a file.
     *  @param filename Full path of the file
     *  @return the size of the file.
     */
    static std::size_t GetFileSize(const std::string &filename);

private:

    struct Impl;
    std::experimental::propagate_const<std::unique_ptr<Impl>> m_pImpl;
};
}
}
#endif //OPENGLTEMPLATE_941E012CE7D14429BBE2EA958FFE4B4A_TCPCLIENT_H
