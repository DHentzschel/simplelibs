#ifndef LOCALTCPSOCKET_H
#define LOCALTCPSOCKET_H

#include "tcpsocket.h"

/**
 * Extends the TcpSocket class and only connects to the localhost.
 *
 * @author Daniel Hentzschel on 13.05.2019.
 */
class LocalTcpSocket : public TcpSocket {
public:
	/**
	 * Connects to the localhost with the specified port.
	 *
	 * @param port the port to connect to
	 */
	SIMPLENETWORK_API bool connect(ushort port);
private:
	bool connect(const AString& hostaddress, ushort port) override { return false; }
};

#endif // LOCALTCPSOCKET_H
