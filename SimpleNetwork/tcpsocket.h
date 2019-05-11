#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <memory>
#include <stopwatch.h>
#include <WinSock2.h>

#include "astring.h"

class TcpClientEventListener;

class TcpSocket {
    friend class TcpServer;

    friend class TcpClientEventListener;

    friend class TcpServerEventListener;

public:
    TcpSocket();

    TcpSocket(const TcpSocket& tcpSocket);

    TcpSocket(SOCKET& socket, SOCKADDR_IN& address);

    virtual ~TcpSocket();

    bool operator==(const TcpSocket& socket) const;

    virtual bool connect(const AString& hostaddress, ushort port);

    void disconnect() const;

    void send(const char* packet, uint length);

    static bool isPortAvailable(const AString& hostaddress, ushort port);

    static bool isLocalPortAvailable(ushort port);

    /* Events */

    virtual void disconnected()
    {}

    virtual void receive(const char* packet, uint length)
    {}

    /* Getters */

    AString getHostAddress() const;

    ushort getPort() const;

    SOCKET getSocket() const;

protected:
    SOCKET socket_;

    AString hostaddress_;

    ushort port_;

    std::shared_ptr<TcpClientEventListener> clientEventListener_;

    void terminate() const;

private:
    Stopwatch stopwatch_;
};

#endif   // TCPSOCKET_H
