#include "tcpeventlistener.h"

TcpEventListener::TcpEventListener(TcpSocket* socket) :
	client(socket),
	isRunning_(false)
{
}
TcpEventListener::TcpEventListener(TcpServer* server) :
	server(server),
	isRunning_(false)
{
}

void TcpEventListener::setIsRunning(const bool isRunning)
{
	isRunning_ = isRunning;
}
