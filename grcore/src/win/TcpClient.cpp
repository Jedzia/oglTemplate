/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TcpClient.cpp class.
 * \file       TcpClient.cpp
 * \date       2020-04-03
 * \author     Jedzia.
 *
 * modified    2020-04-03, Jedzia
 */
/*---------------------------------------------------------*/
//
//#include <winsock2.h>
#include <mswsock.h>
//
#include "grcore/Utility/TcpClient.h"
#include "grcore/warning/FMT_format_log.h"
#include <chrono>
#include <filesystem>
#include <iostream>
#include <string>
#include <windows.h>
#include <ws2tcpip.h>

namespace fs = std::filesystem;

struct grcore::util::TcpClient::Impl {
    WSADATA m_wsaData;
    SOCKET m_connectSocket = INVALID_SOCKET;

    /** Check if this instance is already connected.
     *  @return <b>true</b> if the socket is connected; otherwise <b>false</b>.
     */
    bool IsConnected() {
        return m_connectSocket != INVALID_SOCKET;
    }

    /** Initialize WSA and the connection.
     *
     *  First the Winsock Stack is initialized. Then a connection to G_TELEMETRY_DEFAULT_ADDRESS and
     *  G_TELEMETRY_DEFAULT_PORT is established.
     *  @return <b>zero</b> if initialized correctly; otherwise an error number.
     */
    int Init() {
        if(m_wsaInitialized) {
            return 0;
        }

        spdlog::info("[{}]  called. +++", __PRETTY_FUNCTION__);

        int iResult;
        struct ::addrinfo* result = NULL, * ptr = NULL, hints;

        // Initialize Winsock
        iResult = WSAStartup(MAKEWORD(2, 2), &m_wsaData);
        if(iResult != 0) {
            //printf("WSAStartup failed with error: %d\n", iResult);
            throw std::runtime_error(fmt::format("WSAStartup failed with error: {}", iResult));
        }

        m_wsaInitialized = true;
        spdlog::info("wsaInitialized = true");

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        // Resolve the server address and port
        iResult = getaddrinfo(G_TELEMETRY_DEFAULT_ADDRESS.c_str(), G_TELEMETRY_DEFAULT_PORT.c_str(), &hints, &result);
        if(iResult != 0) {
            WSACleanup();
            m_wsaInitialized = false;
            throw std::runtime_error(fmt::format("WSACleanup, getaddrinfo failed with error: {}", iResult));
        }

        // Attempt to connect to an address until one succeeds
        for(ptr = result; ptr != NULL; ptr = ptr->ai_next) {
            // Create a SOCKET for connecting to server
            m_connectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                    ptr->ai_protocol);
            if(m_connectSocket == INVALID_SOCKET) {
                WSACleanup();
                m_wsaInitialized = false;
                throw std::runtime_error(fmt::format("WSACleanup, socket failed with error: {}", WSAGetLastError()));
            }

            // Connect to server.
            iResult = connect(m_connectSocket, ptr->ai_addr, static_cast<int>(ptr->ai_addrlen));
            if(iResult == SOCKET_ERROR) {
                closesocket(m_connectSocket);
                m_connectSocket = INVALID_SOCKET;
                continue;
            }

            break;
        }
        freeaddrinfo(result);

        if(m_connectSocket == INVALID_SOCKET) {
            //printf("Unable to connect to server!\n");
            WSACleanup();
            m_wsaInitialized = false;
            throw std::runtime_error("WSACleanup, Unable to connect to server!");
        }

        return iResult;
    } // Init

    /** Disconnect the socket and shutdown Winsock.
     *
     *  When Winsock wasn't initialized this simply does nothing.
     *  Otherwise it is checked if there is a existing connection and the socket connection is
     * closed.
     *  After that Winsock is cleaned up and shut down.
     */
    void Shutdown() {
        if(!m_wsaInitialized) {
            return;
        }

        if(m_connectSocket != INVALID_SOCKET) {
            // shutdown the connection since no more data will be sent
            int iResult = ::shutdown(m_connectSocket, SD_SEND);
            if(iResult == SOCKET_ERROR) {
                //printf("shutdown failed with error: %d\n", WSAGetLastError());
                closesocket(m_connectSocket);
                WSACleanup();
                spdlog::info("shutdown failed with error: {}", WSAGetLastError());
            }

            // cleanup
            closesocket(m_connectSocket);
        }

        WSACleanup();
        m_wsaInitialized = false;
        spdlog::info("WSACleanup, [{}]  called. +++", __PRETTY_FUNCTION__);
    } // Shutdown

    bool m_wsaInitialized = false;
};

std::size_t grcore::util::TcpClient::GetFileSize(const std::string &filename) {
    fs::path p = fs::current_path() / filename;
    return fs::file_size(p);
}

void grcore::util::TcpClient::SendFile(const std::string &filename) {
    m_pImpl->Init();
    if(!m_pImpl->IsConnected()) {
        return;
    }

    HANDLE hFile = CreateFile(
            filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
    //Send file size
    //const std::size_t size = GetFileSize(filename);
    //const int size = static_cast<const int>(GetFileSize(filename));
    const auto size = GetFileSize(filename);
    //send(sock, static_cast<const int*>(&size), sizeof(std::size_t), 0);

/*#if defined(__clang__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__) && defined(WARNINGS_SKIP_TEMPORARY)
    #  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#endif*/
    send(m_pImpl->m_connectSocket, reinterpret_cast<const char *>( &size), sizeof(size), 0);
/*#if defined(__clang__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma clang diagnostic pop
#elif defined(__GNUC__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma GCC diagnostic pop
#endif*/
    //LogManager::log(std::to_string(GetFileSize(filename_str)));
    spdlog::info("[{}]  called. +++", __PRETTY_FUNCTION__, GetFileSize(filename));

    //Send file
    TransmitFile(m_pImpl->m_connectSocket, hFile, ::GetFileSize(hFile, NULL), 1024, NULL, NULL,
            TF_USE_KERNEL_APC | TF_WRITE_BEHIND);
    CloseHandle(hFile);

    //printf("Bytes Sent: %ld\n", iResult);
    m_pImpl->Shutdown();
} // grcore::util::TcpClient::SendFile

grcore::util::TcpClient::~TcpClient() {
    m_pImpl->Shutdown();
}

grcore::util::TcpClient::TcpClient() : m_pImpl(std::make_unique<grcore::util::TcpClient::Impl>()) /*,
                                                                                                     m_openConnection(false)*/
{}

grcore::util::TcpClient::TcpClient(bool openConnection) : m_pImpl(std::make_unique<grcore::util::TcpClient::Impl>()) {
    /*:
       m_openConnection(openConnection)*/
    if(openConnection) {
        m_pImpl->Init();
    }
}

struct TelemetryData {
    const long long int Time;
    const double Data;
};

void grcore::util::TcpClient::SendData(const double &data) {
    m_pImpl->Init();
    if(!m_pImpl->IsConnected()) {
        return;
    }

#if 1// MinGW, see https://github.com/msys2/MINGW-packages/issues/5086#issuecomment-476499828
    typedef std::chrono::system_clock Clock;
#else
    typedef std::chrono::high_resolution_clock clock;
#endif
    const auto dataTime = std::chrono::time_point_cast<std::chrono::milliseconds>(
            Clock::now()).time_since_epoch().count();

    const TelemetryData telemetryData {
        dataTime, data
    };

    //Send file size
    //const std::size_t size = GetFileSize(filename);
    //const int size = sizeof(data);
    //send(sock, static_cast<const int*>(&size), sizeof(std::size_t), 0);
/*
#if defined(__clang__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#endif
*/
    //send(m_pImpl->m_connectSocket, (const char *)&size, sizeof(std::size_t), 0);
    //send(m_pImpl->m_connectSocket, (const char *)&data, sizeof(data), 0);
    send(m_pImpl->m_connectSocket, reinterpret_cast<const char *>(&telemetryData), sizeof(telemetryData), 0);
/*
#if defined(__clang__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma clang diagnostic pop
#elif defined(__GNUC__) && defined(WARNINGS_SKIP_TEMPORARY)
#  pragma GCC diagnostic pop
#endif
*/
    //LogManager::log(std::to_string(GetFileSize(filename_str)));
    //spdlog::info("[{}]  called. +++", __PRETTY_FUNCTION__);

    //Send file
    //TransmitFile(m_pImpl->m_connectSocket, hFile, ::GetFileSize(hFile, NULL), 1024, NULL, NULL,
    // TF_USE_KERNEL_APC | TF_WRITE_BEHIND);
    //CloseHandle(hFile);

    //printf("Bytes Sent: %ld\n", iResult);
    //m_pImpl->Shutdown();
} // grcore::util::TcpClient::SendData

// grcore::util::TcpClient::init
