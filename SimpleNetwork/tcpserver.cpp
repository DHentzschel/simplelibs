#include "tcpserver.h"

#ifdef _WIN32
#include <WS2tcpip.h>
#elif __unix__
#include <netdb.h>
#include <netinet/in.h>
#endif // __unix__

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
#ifdef _WIN32
    closesocket(socket_);
#elif __unix__
    close(socket_);
#endif // __unix__
}

/**
 * \brief Tries to listen to address and port passed by params and returns success.
 * \param address address to connect
 * \param port port to connect
 * \return success
 */
bool TcpServer::listen(const AString& hostaddress, const ushort port)
{
#ifdef _WIN32
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

#elif __unix__
    sockaddr_in server;
    ZEROMEMORY(&server);

    server.sin_famiy = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if (::bind(socket_, REINTERPRET_CAST(sockaddr*, &server), sizeof(sockaddr_in)) == SOCKET_ERROR) {
        Logger::error("bind() failed.");
        return false;
    }

    if (::list(socket_, 2)) {
        Logger::error("listen() failed.");
        return false;
    }

#endif // __unix__
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
#ifdef _WIN32
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
#elif __unix__
    if ((socket_ = ::socket(AF_INT, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        Logger::error("socket() failed.");
        exit(EXIT_FAILURE);
    }
#endif // __unix__

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
