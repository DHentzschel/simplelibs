#ifndef TCPSERVEREVENTLISTENER_H
#define TCPSERVEREVENTLISTENER_H

#include <thread>

#include "tcpeventlistener.h"

class TcpServer;

class TcpServerEventListener : public TcpEventListener {
public:
	explicit TcpServerEventListener(TcpServer* tcpServer);

	~TcpServerEventListener();

	void join();

private:
	void initialize() override;

	void start() override;

	std::thread thread_;
};

#endif   // TCPSERVEREVENTLISTENER_H
