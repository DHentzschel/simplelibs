#ifndef TCPCLIENTEVENTLISTENER_H
#define TCPCLIENTEVENTLISTENER_H

#include <types.h>
#include <thread>

#include "tcpeventlistener.h"

/**
 * Provides an event listener class for TcpSocket.
 *
 * @author Daniel Hentzschel on 13.05.2019.
 */
class TcpClientEventListener : public TcpEventListener {
public:
	/**
	 * Calls the super constructor.
	 *
	 * @param socket the pointer to the TcpSocket to listen for
	 */
	explicit TcpClientEventListener(TcpSocket* socket);

	/**
	 * Joins the thread to the main thread.
	 */
	void join();
private:
	std::thread thread_;

	/**
	 * Starts the event listening process. Exits when isRunning is false.
	 */
	void start() override;
};

#endif   // TCPCLIENTEVENTLISTENER_H
