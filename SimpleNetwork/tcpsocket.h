#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <memory>
#include <stopwatch.h>
#include <WinSock2.h>

#include "astring.h"
#include "simplenetwork.h"

class TcpClientEventListener;

/**
 * This class provides a TCP socket and its connect, disconnect, receive and send packet functions.
 *
 * @author Daniel Hentzschel on 13.05.2019.
 */
class TcpSocket {
	friend class TcpServer;

	friend class TcpClientEventListener;

	friend class TcpServerEventListener;

	friend class LocalTcpSocket;

	friend class LocalTcpServer;

public:
	/**
	 * Sets some default values.
	 */
	SIMPLENETWORK_API TcpSocket();

	/**
	 * Copies the values from the specified socket.
	 *
	 * @param tcpSocket the socket to copy from
	 */
	SIMPLENETWORK_API TcpSocket(const TcpSocket& tcpSocket);

	/**
	 * Sets the specified socket and address.
	 *
	 * @param socket the socket to set
	 * @param address the address to set
	 */
	SIMPLENETWORK_API TcpSocket(SOCKET& socket, SOCKADDR_IN& address);

	/**
	 * Terminates the clientEventListener thread and disconnects (if connected).
	 */
	SIMPLENETWORK_API ~TcpSocket();

	/**
	 * Compares both sockets and returns whether they are equal.
	 *
	 * @param socket the socket to compare
	 * @return whether both sockets are equal
	 */
	SIMPLENETWORK_API bool operator==(const TcpSocket& socket) const;

	/**
	 * Tries to connect to the specified hostaddress and port and returns the success.
	 *
	 * @param hostaddress the hostaddress to connect to
	 * @param port the port to connect to
	 * @return whether the socket could connect to the specified hostaddress and port
	 */
	SIMPLENETWORK_API virtual bool connect(const AString& hostaddress, ushort port);

	/**
	 * Disconnects the socket (if connected).
	 */
	SIMPLENETWORK_API void disconnect() const;

	/**
	 * Sends the specified packet as char array to the socket.
	 *
	 * @param packet the char array
	 * @param length the packet length
	 */
	SIMPLENETWORK_API void send(const char* packet, uint length);

	/**
	* Returns whether the specified port is available under the specified hostaddress.
	*
	* @param hostaddress the hostaddress to check
	* @param port the port to check
	* @return whether the specified port is available under the specified hostaddress
	*/
	SIMPLENETWORK_API static bool isPortAvailable(const AString& hostaddress, ushort port);

	/**
	* Returns whether the specified port is available on localhost.
	*
	* @param port the port to check
	* @return whether the specified port is available on localhost
	*/
	SIMPLENETWORK_API static bool isLocalPortAvailable(ushort port);

	/* Events */

	/**
	 * This function will be called when the socket disconnects.
	 */
	SIMPLENETWORK_API virtual void disconnected()
	{}

	/**
	 * This function will be called when the socket receives a packet.
	 *
	 * @param packet the received packet
	 * @param length the length of the packet received
	 */
	SIMPLENETWORK_API virtual void receive(const char* packet, uint length)
	{}

	/**
	 * Returns the hostaddress as string.
	 *
	 * @return the hostaddress as string
	 */
	SIMPLENETWORK_API AString getHostAddress() const;

	/**
	 * Returns the port.
	 *
	 * @return port
	 */
	SIMPLENETWORK_API ushort getPort() const;

	/**
	 * Returns the WINAPI socket.
	 *
	 * @return the WINAPI socket
	 */
	SIMPLENETWORK_API SOCKET getSocket() const;
protected:
	/**
	 * Terminates the clientEventListener thread.
	 */
	SIMPLENETWORK_API void terminate() const;

private:
	/** The stopwatch instance of the socket */
	Stopwatch stopwatch_;

	/** The WINAPI socket */
	SOCKET socket_;

	/** The hostaddress of the socket */
	AString hostaddress_;

	/** The port of the socket */
	ushort port_;

	/** The clientEventListener instance of the socket */
	std::shared_ptr<TcpClientEventListener> clientEventListener_;
};

#endif   // TCPSOCKET_H
