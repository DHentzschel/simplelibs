#ifndef LOCALTCPSOCKET_H
#define LOCALTCPSOCKET_H

#include "tcpsocket.h"

class LocalTcpSocket : public TcpSocket {
public:
    bool connect(ushort port);
private:
    bool connect(const AString& hostaddress, ushort port) override {}
};

#endif // LOCALTCPSOCKET_H
