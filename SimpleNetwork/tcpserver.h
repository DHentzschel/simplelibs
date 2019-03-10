#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <WinSock2.h>

#include "astring.h"
#include "tcpsocket.h"
#include "types.h"

class TcpServerEventListener;

class TcpServer : public TcpSocket {
    friend class TcpServerEventListener;

public:
    explicit TcpServer();

    virtual ~TcpServer();

    virtual bool listen(const AString& hostaddress, ushort port);

    void terminate() const;

protected:
    TcpSocket* currentSocket_;

    AVector<TcpSocket*> socketList_;

    uint addressLength_;

    virtual void incomingConnection(const TcpSocket& socket) = 0;

    virtual void disconnected(const TcpSocket& socket) = 0;

    void receive(const char* packet, uint length) override = 0;

    std::shared_ptr<TcpServerEventListener> serverEventListener_;

private:
    void initialize();

    TcpSocket* getSocket(const SOCKET& socket);
};

#endif   // TCPSERVER_H
