#include "tcpservereventlistener.h"

#include <functions.h>
#include "logger.h"
#include "tcpserver.h"
#include "tcpsocket.h"

/**
 * \brief Constructs instance by calling super constructor.
 * \param tcpServer pointer to TcpServer instance
 */
TcpServerEventListener::TcpServerEventListener(TcpServer* tcpServer) :
    TcpEventListener(tcpServer)
{
    TcpServerEventListener::initialize();
}

/**
 * \brief Destroys instance after joining thread to main thread.
 */
TcpServerEventListener::~TcpServerEventListener()
{
    join();
}

/**
* \brief Joins thread to main thread.
*/
void TcpServerEventListener::join()
{
    if (thread_.joinable()) {
        thread_.join();
    }
}

/**
* \brief Starts thread which calls start().
*/
void TcpServerEventListener::initialize()
{
    thread_ = std::thread(&TcpServerEventListener::start, this);
}

/**
 * \brief Starts event listening process. Exists when isRunning is false.
 */
void TcpServerEventListener::start()
{
#ifdef _WIN32
    SOCKADDR_IN address;
    FD_SET readFdSet;
    int receiveBufferLength;

    auto bufferLength = 1024;
    auto* buffer = new char[bufferLength];
    auto error = false;

    ZEROMEMORY(&address);
    ZEROMEMORY(&readFdSet);

    while (isRunning_ && !error) {
        FD_ZERO(&readFdSet);
        FD_SET(server->socket_, &readFdSet);

        auto handle = [this, &receiveBufferLength, &readFdSet, &address, buffer,
            bufferLength]() -> bool {

            timeval a;
            a.tv_sec = 1;
            a.tv_usec = 0;
            select(0, &readFdSet, nullptr, nullptr, &a);
            if (FD_ISSET(server->socket_, &readFdSet)) {
                auto incomingSocket = accept(server->socket_, REINTERPRET_CAST(sockaddr*, &address),
                    REINTERPRET_CAST(int*, &server->addressLength_));

                if (incomingSocket == 0 || incomingSocket == INVALID_SOCKET) {
#ifdef _DEBUG
#ifdef _DBG_SOCKERR
                    Logger::error("accept() failed. Error code: " +
                        TO_STRING(WSAGetLastError()));
#endif
#endif
                    return true;
                }

                server->socketList_.append(new TcpSocket(incomingSocket, address));
                server->incomingConnection(*server->socketList_.last());
            }
            for (uint i = 0; i < readFdSet.fd_count; ++i) {
                const auto tempSocket = readFdSet.fd_array[STATIC_CAST(int, i)];
                if (server->currentSocket_ = server->getSocket(tempSocket)) {
                    receiveBufferLength = recv(server->currentSocket_->socket_, buffer,
                        bufferLength - 1, 0);
                    if (receiveBufferLength > 0) {
                        buffer[receiveBufferLength] = '\0';
                        server->receive(buffer, receiveBufferLength);
                    }
                    else {
                        server->socketList_.removeFirst(server->currentSocket_);
                        server->disconnected(*server->currentSocket_);
                        closesocket(server->currentSocket_->socket_);
                        delete server->currentSocket_;
                    }
                }
            }
            return false;
        };

        for (auto& socket : server->socketList_) {
            if (readFdSet.fd_count >= FD_SETSIZE) {
                error = !handle();
                FD_ZERO(&readFdSet);
            }
            FD_SET(socket->socket_, &readFdSet);
        }
        error = handle();
    }
    delete[] buffer;
    WSACleanup();
#elif __unix__
    
#endif // __unix__
}
