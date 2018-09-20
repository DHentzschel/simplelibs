#ifndef LOCALTCPSERVER_H
#define LOCALTCPSERVER_H

#include "tcpserver.h"

class LocalTcpServer : public TcpServer {
public:
    bool listen(ushort port);
private:
    bool listen(const AString& hostaddress, ushort port) override {}
};

#endif // LOCALTCPSERVER_H
