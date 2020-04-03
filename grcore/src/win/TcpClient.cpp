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
#include <filesystem>
#include <iostream>
#include <windows.h>
#include <ws2tcpip.h>

namespace fs = std::filesystem;

#define DEFAULT_PORT "27015"

struct grcore::util::TcpClient::Impl {
    WSADATA m_wsaData;
    SOCKET m_connectSocket = INVALID_SOCKET;

    int Init() {
        std::string address {
            "localhost"
        };
        int iResult;
        struct ::addrinfo* result = NULL, * ptr = NULL, hints;

        // Initialize Winsock
        iResult = WSAStartup(MAKEWORD(2, 2), &m_wsaData);
        if(iResult != 0) {
            //printf("WSAStartup failed with error: %d\n", iResult);
            throw std::runtime_error(fmt::format("WSAStartup failed with error: {}", iResult));
        }

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        // Resolve the server address and port
        iResult = getaddrinfo(address.c_str(), DEFAULT_PORT, &hints, &result);
        if(iResult != 0) {
            WSACleanup();
            throw std::runtime_error(fmt::format("getaddrinfo failed with error: {}", iResult));
        }

        // Attempt to connect to an address until one succeeds
        for(ptr = result; ptr != NULL; ptr = ptr->ai_next) {
            // Create a SOCKET for connecting to server
            m_connectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                    ptr->ai_protocol);
            if(m_connectSocket == INVALID_SOCKET) {
                WSACleanup();
                throw std::runtime_error(fmt::format("socket failed with error: {}", WSAGetLastError()));
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
            throw std::runtime_error("Unable to connect to server!");
        }

        return iResult;
    } // Init

    void Shutdown() {
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
        WSACleanup();
    }
};

std::size_t grcore::util::TcpClient::GetFileSize(const std::string &filename) {
    fs::path p = fs::current_path() / filename;
    return fs::file_size(p);
}

void grcore::util::TcpClient::SendFile(const std::string &filename) {
    m_pImpl->Init();
    HANDLE hFile = CreateFile(
            filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
    //Send file size
    //const std::size_t size = GetFileSize(filename);
    const int size = static_cast<const int>(GetFileSize(filename));
    //send(sock, static_cast<const int*>(&size), sizeof(std::size_t), 0);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
    send(m_pImpl->m_connectSocket, (const char *)&size, sizeof(std::size_t), 0);
#pragma clang diagnostic pop
    //LogManager::log(std::to_string(GetFileSize(filename_str)));
    spdlog::info("[{}]  called. +++", __PRETTY_FUNCTION__, GetFileSize(filename));

    //Send file
    TransmitFile(m_pImpl->m_connectSocket, hFile, ::GetFileSize(hFile, NULL), 1024, NULL, NULL, TF_USE_KERNEL_APC | TF_WRITE_BEHIND);
    CloseHandle(hFile);

    //printf("Bytes Sent: %ld\n", iResult);
    m_pImpl->Shutdown();
} // grcore::util::TcpClient::SendFile

grcore::util::TcpClient::~TcpClient() {}

grcore::util::TcpClient::TcpClient() : m_pImpl(std::make_unique<grcore::util::TcpClient::Impl>()) {}

// grcore::util::TcpClient::init
