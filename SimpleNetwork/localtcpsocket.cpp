#include "localtcpsocket.h"

#include <chrono>
#include <thread>
#include <WS2tcpip.h>
#include <astring.h>
#include <functions.h>

#include <logger.h>
#include "tcpclienteventlistener.h"

#pragma comment(lib, "ws2_32.lib")

bool LocalTcpSocket::connect(ushort port)
{
    hostaddress_ = "127.0.0.1";
    port_ = port;

    WSADATA wsaData;
    struct addrinfo hints;
    struct addrinfo* result = nullptr;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        Logger::error("WSAStartup() failed. Error code: " + AString::toString(WSAGetLastError()));
        return false;
    }

    ZEROMEMORY(&hints);

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    getaddrinfo(hostaddress_.toCString(), AString::toString(port_).toCString(), &hints, &result);

    socket_ = INVALID_SOCKET;
    for (auto* ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
        socket_ = ::socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (socket_ == INVALID_SOCKET) {
            Logger::error("socket() failed. Error code: " + AString::toString(WSAGetLastError()));
            WSACleanup();
            return false;
        }
        if (::connect(socket_, ptr->ai_addr, static_cast<int>(ptr->ai_addrlen)) == SOCKET_ERROR) {
            Logger::error("connect() failed. Error code: " + AString::toString(WSAGetLastError()));
            WSACleanup();
            return false;
        }
    }

    freeaddrinfo(result);
    if (socket_ == INVALID_SOCKET) {
        Logger::error("connect() failed. Error code: " + AString::toString(WSAGetLastError()));
        WSACleanup();
        return false;
    }

    clientEventListener_ = std::make_shared<TcpClientEventListener>(this);
    return true;
}
