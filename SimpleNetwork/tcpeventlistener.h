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
	explicit TcpEventListener(TcpSocket* socket);

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
		/** Represents the pointer to the listenable server */
		TcpServer* server_;

		/** Represents the pointer to the listenable client */
		TcpSocket* client_;
	};

	/** Represents whether the event listener should listen */
	bool isRunning_;

	/**
	 * Starts the event listener.
	 */
	virtual void start() = 0;
};

#endif   // TCPEVENTLISTENER_H
