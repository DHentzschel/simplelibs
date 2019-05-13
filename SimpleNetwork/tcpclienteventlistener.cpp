#include "logger.h"

#include "tcpclienteventlistener.h"
#include "tcpsocket.h"

TcpClientEventListener::TcpClientEventListener(TcpSocket* socket) :
	TcpEventListener(socket)
{
	thread_ = std::thread(&TcpClientEventListener::start, this);
}

void TcpClientEventListener::join()
{
	if (thread_.joinable()) {
		thread_.join();
	}
}

void TcpClientEventListener::start()
{
	setIsRunning(true);
	auto receiveBufferLength = 1024;
	const auto bufferLength = 1024;
	auto* buffer = new char[bufferLength];
	FD_SET readFdSet;

	while (isRunning_) {
		FD_ZERO(&readFdSet);
		FD_SET(client_->socket_, &readFdSet);

		auto sel = select(0, &readFdSet, nullptr, nullptr, nullptr);
		if (FD_ISSET(client_->socket_, &readFdSet)) {
			ZeroMemory(buffer, bufferLength);
			receiveBufferLength =
				recv(client_->socket_, buffer, bufferLength - 1, 0);
			if (receiveBufferLength > 0) {
				buffer[receiveBufferLength] = '\0';
				client_->receive(buffer, receiveBufferLength);
			}
			else {
				client_->disconnect();
				break;
			}
		}
	}
	delete[] buffer;
	WSACleanup();
}
