#include "tcpserver.h"

#include <WS2tcpip.h>

#include <mutex>

#include <functions.h>

#include "console.h"
#include "logger.h"
#include "tcpservereventlistener.h"

/**
 * \brief Constructing instance by settin default values.
 */
TcpServer::TcpServer() :
    addressLength_(0),
    serverEventListener_(nullptr)
{
    initialize();
}

/**
 * \brief Destroys instance after closing socket.
 */
TcpServer::~TcpServer()
{
    closesocket(socket_);
}

/**
 * \brief Tries to listen to address and port passed by params and returns success.
 * \param address address to connect
 * \param port port to connect
 * \return success
 */
bool TcpServer::listen(const AString& hostaddress, const ushort port)
{
    SOCKADDR_IN server;
    ZEROMEMORY(&server);

    inet_pton(AF_INET, hostaddress.toCString(), &server.sin_addr);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (::bind(socket_, REINTERPRET_CAST(sockaddr*, &server), sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
        Logger::error("bind() failed. Error code: " +
            TO_STRING(WSAGetLastError()));
        return false;
    }

    if (::listen(socket_, 2)) {
        Logger::error("listen() failed. Error code: " +
            TO_STRING(WSAGetLastError()));
        return false;
    }

    addressLength_ = sizeof(sockaddr_in);
    serverEventListener_ = MAKE_SHARED(TcpServerEventListener, this);
    return true;
}

/**
 * \brief Terminates serverEventListener thread.
 */
void TcpServer::terminate() const
{
    if (serverEventListener_) {
        serverEventListener_.get()->setIsRunning(false);
        serverEventListener_.get()->join();
    }
}

/**
 * \brief Initializes current server instance by doing some WSA startup stuff.
 */
void TcpServer::initialize()
{
    WSADATA wsaData;
    ZeroMemory(&wsaData, sizeof(WSADATA));

    if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        Logger::error("WSAStartup() failed. Error code: " + TO_STRING(WSAGetLastError()));
        exit(EXIT_FAILURE);
    }
    if ((socket_ = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        Logger::error("socket() failed. Error code: " + TO_STRING(WSAGetLastError()));
        exit(EXIT_FAILURE);
    }

    socketList_.reserve(1024);
}

TcpSocket* TcpServer::getSocket(const SOCKET& socket)
{
    for (auto& tempSocket : socketList_) {
        if (tempSocket->socket_ == socket) {
            return tempSocket;
        }
    }
    return nullptr;
}
