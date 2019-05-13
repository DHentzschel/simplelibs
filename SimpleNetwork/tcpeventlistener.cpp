#include "tcpeventlistener.h"

TcpEventListener::TcpEventListener(TcpSocket* client) :
	client(client),
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
