#include "tcpservereventlistener.h"

#include <functions.h>
#include "logger.h"
#include "tcpserver.h"
#include "tcpsocket.h"

TcpServerEventListener::TcpServerEventListener(TcpServer* server) :
	TcpEventListener(server)
{
	thread_ = std::thread(&TcpServerEventListener::start, this);
}

void TcpServerEventListener::join()
{
	if (thread_.joinable()) {
		thread_.join();
	}
}

void TcpServerEventListener::start()
{
	setIsRunning(true);
	SOCKADDR_IN address;
	FD_SET readFdSet;
	int receiveBufferLength;

	auto bufferLength = 1024;
	auto* buffer = new char[bufferLength];
	auto error = false;

	ZEROMEMORY(&address);
	ZEROMEMORY(&readFdSet);

	while (isRunning_ && !error) {
		FD_ZERO(&readFdSet);
		FD_SET(server_->socket_, &readFdSet);

		auto handle = [this, &receiveBufferLength, &readFdSet, &address, buffer,
			bufferLength]() -> bool {

			timeval a;
			a.tv_sec = 1;
			a.tv_usec = 0;
			select(0, &readFdSet, nullptr, nullptr, &a);
			if (FD_ISSET(server_->socket_, &readFdSet)) {
				auto incomingSocket = accept(server_->socket_, reinterpret_cast<sockaddr*>(&address),
					reinterpret_cast<int*>(&server_->addressLength_));

				if (incomingSocket == 0 || incomingSocket == INVALID_SOCKET) {
					Logger::error("accept() failed. Error code: " +
						AString::toString(WSAGetLastError()));
					return true;
				}

				server_->socketList_.append(new TcpSocket(incomingSocket, address));
				server_->incomingConnection(*server_->socketList_.last());
			}
			for (uint i = 0; i < readFdSet.fd_count; ++i) {
				const auto tempSocket = readFdSet.fd_array[static_cast<int>(i)];
				if (server_->currentSocket_ = server_->getSocket(tempSocket)) {
					receiveBufferLength = recv(server_->currentSocket_->socket_, buffer,
						bufferLength - 1, 0);
					if (receiveBufferLength > 0) {
						buffer[receiveBufferLength] = '\0';
						server_->receive(buffer, receiveBufferLength);
					}
					else {
						server_->socketList_.removeFirst(server_->currentSocket_);
						server_->disconnected(*server_->currentSocket_);
						closesocket(server_->currentSocket_->socket_);
						delete server_->currentSocket_;
					}
				}
			}
			return false;
		};

		for (auto& socket : server_->socketList_) {
			if (readFdSet.fd_count >= FD_SETSIZE) {
				error = !handle();
				FD_ZERO(&readFdSet);
			}
			FD_SET(socket->socket_, &readFdSet);
		}
		error = handle();
	}
	delete[] buffer;
	WSACleanup();
}
