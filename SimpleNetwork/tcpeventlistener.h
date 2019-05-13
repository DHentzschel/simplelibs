#ifndef TCPEVENTLISTENER_H
#define TCPEVENTLISTENER_H

class TcpServer;

class TcpSocket;

/**
 * Provides an event listener class for both TcpSocket and TcpServer.
 *
 * @author Daniel Hentzschel on 13.05.2019.
 */
class TcpEventListener {
public:
	/**
	 * Sets the socket pointer to the specified value.
	 *
	 * @param socket the pointer to the socket
	 */
	explicit TcpEventListener(TcpSocket* client);

	/**
	 * Sets the server pointer to the specified value.
	 *
	 * @param server the pointer to the server
	 */
	explicit TcpEventListener(TcpServer* server);

	virtual ~TcpEventListener() = default;

	/**
	 * Sets isRunning to the specified value.
	 *
	 * @param isRunning whether the thread should run or not
	 */
	void setIsRunning(bool isRunning);

protected:
	union {
		TcpServer* server;

		TcpSocket* client;
	};

	bool isRunning_;

	/*
	 * Starts the event listener.
	 */
	virtual void start() = 0;
};

#endif   // TCPEVENTLISTENER_H
