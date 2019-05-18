#include "localtcpserver.h"

#include <WS2tcpip.h>

#include <logger.h>

#include "tcpservereventlistener.h"

bool LocalTcpServer::listen(ushort port)
{
    SOCKADDR_IN server;
    ZeroMemory(&server, sizeof(SOCKADDR_IN));

    inet_pton(AF_INET, "127.0.0.1", &(server.sin_addr));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (::bind(socket_, reinterpret_cast<sockaddr*>(&server), sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
        Logger::error("bind() failed. Error code: " + AString::toString(WSAGetLastError()));
        return false;
    }

    if (::listen(socket_, 2)) {
        Logger::error("listen() failed. Error code: " + AString::toString(WSAGetLastError()));
        return false;
    }

    addressLength_ = sizeof(sockaddr_in);
    serverEventListener_ = std::make_shared<TcpServerEventListener>(this);
    return true;
}
