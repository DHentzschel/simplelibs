#include "tcpeventlistener.h"

TcpEventListener::TcpEventListener(TcpSocket* socket) :
	client_(socket),
	isRunning_(false)
{
}
TcpEventListener::TcpEventListener(TcpServer* server) :
	server_(server),
	isRunning_(false)
{
}

void TcpEventListener::setIsRunning(const bool isRunning)
{
	isRunning_ = isRunning;
}
