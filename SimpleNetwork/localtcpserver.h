#ifndef LOCALTCPSERVER_H
#define LOCALTCPSERVER_H

#include <astring.h>
#include "tcpserver.h"

/**
 * This class provides a local TcpServer with some useful functions.
 *
 * @author Daniel Hentzschel on 13.05.2019.
 */
class LocalTcpServer : public TcpServer {
public:
	/**
	 * Tries to listen at the specified port and returns success.
	 *
	 * @param port the port to listen to
	 * @return whether the server could listen to the specified port
	 */
	SIMPLENETWORK_API bool listen(ushort port);
private:
	bool listen(const AString& hostaddress, ushort port) override { return false; }
};

#endif // LOCALTCPSERVER_H
