#include "logger.h"

#include "tcpclienteventlistener.h"
#include "tcpsocket.h"

/**
* \brief Constructs instance by calling super constructor.
* \param tcpClient pointer to TcpClient instance
*/
TcpClientEventListener::TcpClientEventListener(TcpSocket* tcpClient) :
	TcpEventListener(tcpClient)
{
	TcpClientEventListener::initialize();
}

/**
 * \brief Joins thread to main thread.
 */
void TcpClientEventListener::join()
{
	if (thread_.joinable()) {
		thread_.join();
	}
}

/**
 * \brief Starts thread which calls start().
 */
void TcpClientEventListener::initialize()
{
	thread_ = std::thread(&TcpClientEventListener::start, this);
}

/**
* \brief Starts event listening process. Exists when isRunning is false.
*/
void TcpClientEventListener::start()
{
	auto receiveBufferLength = 1024;
	const auto bufferLength = 1024;
	auto* buffer = new char[bufferLength];
	FD_SET readFdSet;

	while (isRunning_) {
		FD_ZERO(&readFdSet);
		FD_SET(client->socket_, &readFdSet);

		auto sel = select(0, &readFdSet, nullptr, nullptr, nullptr);
		if (FD_ISSET(client->socket_, &readFdSet)) {
			ZeroMemory(buffer, bufferLength);
			receiveBufferLength =
				recv(client->socket_, buffer, bufferLength - 1, 0);
			if (receiveBufferLength > 0) {
				buffer[receiveBufferLength] = '\0';
				client->receive(buffer, receiveBufferLength);
			}
			else {
				client->disconnect();
				break;
			}
		}
	}
	delete[] buffer;
	WSACleanup();
}
