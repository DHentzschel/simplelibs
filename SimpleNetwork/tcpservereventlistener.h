#ifndef TCPSERVEREVENTLISTENER_H
#define TCPSERVEREVENTLISTENER_H

#include <thread>

#include "tcpeventlistener.h"

class TcpServer;

/**
 * Provides an event listener class for TcpServer.
 *
 * @author Daniel Hentzschel on 13.05.2019.
 */
class TcpServerEventListener : public TcpEventListener {
public:
	/**
	 * Calls the super constructor.
	 *
	 * @param server the pointer to the TcpServer to listen for
	 */
	SIMPLENETWORK_API explicit TcpServerEventListener(TcpServer* server);

	/**
	 * Joins the thread to the main thread.
	 */
	SIMPLENETWORK_API void join();

private:
	std::thread thread_;

	/**
	 * Starts the event listening process. Exits when isRunning is false.
	 */
	void start() override;
};

#endif   // TCPSERVEREVENTLISTENER_H
