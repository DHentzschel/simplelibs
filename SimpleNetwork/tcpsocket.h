#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <memory>
#include <stopwatch.h>
#include <WinSock2.h>

#include "astring.h"

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

public:
	/**
	 * Sets some default values.
	 */
	TcpSocket();

	/**
	 * Copies the values from the specified socket.
	 *
	 * @param tcpSocket the socket to copy from
	 */
	TcpSocket(const TcpSocket& tcpSocket);

	/**
	 * Sets the specified socket and address.
	 *
	 * @param socket the socket to set
	 * @param address the address to set
	 */
	TcpSocket(SOCKET& socket, SOCKADDR_IN& address);

	/**
	 * Terminates the clientEventListener thread and disconnects (if connected).
	 */
	~TcpSocket();

	/**
	 * Compares both sockets and returns whether they are equal.
	 *
	 * @param socket the socket to compare
	 * @return whether both sockets are equal
	 */
	bool operator==(const TcpSocket& socket) const;

	/**
	 * Tries to connect to the specified hostaddress and port and returns the success.
	 *
	 * @param hostaddress the hostaddress to connect to
	 * @param port the port to connect to
	 * @return whether the socket could connect to the specified hostaddress and port
	 */
	virtual bool connect(const AString& hostaddress, ushort port);

	/**
	 * Disconnects the socket (if connected).
	 */
	void disconnect() const;

	/**
	 * Sends the specified packet as char array to the socket.
	 *
	 * @param packet the char array
	 * @param length the packet length
	 */
	void send(const char* packet, uint length);

	static bool isPortAvailable(const AString& hostaddress, ushort port);

	static bool isLocalPortAvailable(ushort port);

	/* Events */

	/**
	 * This function will be called when the socket disconnects.
	 */
	virtual void disconnected()
	{}

	/**
	 * This function will be called when the socket receives a packet.
	 *
	 * @param packet the received packet
	 * @param length the length of the packet received
	 */
	virtual void receive(const char* packet, uint length)
	{}

	/**
	 * Returns the hostaddress as string.
	 *
	 * @return the hostaddress as string
	 */
	AString getHostAddress() const;

	/**
	 * Returns the port.
	 *
	 * @return port
	 */
	ushort getPort() const;

	/**
	 * Returns the WINAPI socket.
	 *
	 * @return the WINAPI socket
	 */
	SOCKET getSocket() const;
protected:
	SOCKET socket_;

	AString hostaddress_;

	ushort port_;

	std::shared_ptr<TcpClientEventListener> clientEventListener_;

	/**
	 * Terminates the clientEventListener thread.
	 */
	void terminate() const;

private:
	Stopwatch stopwatch_;
};

#endif   // TCPSOCKET_H
