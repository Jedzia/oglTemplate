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
 * modified    2020-04-03, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef OPENGLTEMPLATE_941E012CE7D14429BBE2EA958FFE4B4A_TCPCLIENT_H
#define OPENGLTEMPLATE_941E012CE7D14429BBE2EA958FFE4B4A_TCPCLIENT_H

#include <cstddef>
#include <experimental/propagate_const>
#include <memory>
#include <string>

namespace grcore {
namespace util {
class TcpClient {
public:

    TcpClient();
    TcpClient(bool openConnection);

    virtual ~TcpClient();

    void SendFile(const std::string &filename);
    void SendData(const float &data);

    static std::size_t GetFileSize(const std::string &filename);

private:

    struct Impl;
    std::experimental::propagate_const<std::unique_ptr<Impl>> m_pImpl;
    //bool m_openConnection;
};
}
}
#endif //OPENGLTEMPLATE_941E012CE7D14429BBE2EA958FFE4B4A_TCPCLIENT_H
