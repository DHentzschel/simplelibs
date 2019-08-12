#include "tcpsocket.h"

#include <chrono>
#include <thread>
#include <WS2tcpip.h>

#include <functions.h>

#include <logger.h>
#include "tcpclienteventlistener.h"

#pragma comment(lib, "ws2_32.lib")

TcpSocket::TcpSocket() :
	socket_(SOCKET()),
	port_(0)
{}

TcpSocket::TcpSocket(const TcpSocket& tcpSocket) :
	socket_(tcpSocket.socket_),
	hostaddress_(tcpSocket.hostaddress_),
	port_(tcpSocket.port_),
	clientEventListener_(tcpSocket.clientEventListener_)
{}

TcpSocket::TcpSocket(SOCKET& socket, SOCKADDR_IN& address) :
	socket_(socket),
	hostaddress_(std::to_string(address.sin_addr.S_un.S_addr)),
	port_(ntohs(address.sin_port))
{
	char adddressBuffer[INET6_ADDRSTRLEN];
	inet_ntop(AF_INET, &static_cast<SOCKADDR_IN*>(&address)->sin_addr,
		adddressBuffer, sizeof adddressBuffer);
	hostaddress_ = adddressBuffer;
}

TcpSocket::~TcpSocket()
{
	terminate();
	disconnect();
}

bool TcpSocket::operator==(const TcpSocket& socket) const
{
	return socket.socket_ == socket_;
}

bool TcpSocket::connect(const AString& hostaddress, const ushort port)
{
	hostaddress_ = hostaddress;
	port_ = port;

	WSADATA wsaData;
	struct addrinfo hints;
	struct addrinfo* result = nullptr;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
		Logger::error("WSAStartup() failed. Error code: " + AString::toString(WSAGetLastError()));
		return false;
	}

	ZEROMEMORY(&hints);

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	getaddrinfo(hostaddress_.toCString(), AString::toString(port_).toCString(), &hints, &result);

	socket_ = INVALID_SOCKET;
	for (auto* ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
		socket_ = ::socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (socket_ == INVALID_SOCKET) {
			Logger::error("socket() failed. Error code: " + AString::toString(WSAGetLastError()));
			WSACleanup();
			return false;
		}
		if (::connect(socket_, ptr->ai_addr, static_cast<int>(ptr->ai_addrlen)) == SOCKET_ERROR) {
			Logger::error("connect() failed. Error code: " + AString::toString(WSAGetLastError()));
			WSACleanup();
			return false;
		}
	}

	freeaddrinfo(result);
	if (socket_ == INVALID_SOCKET) {
		Logger::error("connect() failed. Error code: " + AString::toString(WSAGetLastError()));
		WSACleanup();
		return false;
	}

	clientEventListener_ = std::make_shared<TcpClientEventListener>(this);
	return true;
}

void TcpSocket::disconnect() const
{
	using namespace std::chrono_literals;

	if (stopwatch_.getElapsedTimeInMillis().count() < 3) {
		std::this_thread::sleep_for(3ms);
	}

	closesocket(socket_);
}

void TcpSocket::send(const char* packet, const uint length)
{
	if (::send(socket_, packet, length, 0) == SOCKET_ERROR) {
		Logger::error("send() failed. Error code: " + AString::toString(WSAGetLastError()));
	}
	stopwatch_.restart();
}

bool TcpSocket::isPortAvailable(const AString & hostaddress, const ushort port)
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
		return false;
	}

	SOCKADDR_IN client;
	ZEROMEMORY(&client);

	inet_pton(AF_INET, hostaddress.toCString(), &(client.sin_addr));
	client.sin_family = AF_INET;
	client.sin_port = htons(port);

	auto socket = ::socket(AF_INET, SOCK_STREAM, 0);

#pragma warning(disable : 6385)
	const auto result = ::connect(socket, (SOCKADDR*)(&client), sizeof(SOCKADDR_IN));
#pragma warning(disable : 6385)

	WSACleanup();
	closesocket(socket);
	return result;
}

bool TcpSocket::isLocalPortAvailable(const ushort port)
{
	return isPortAvailable("127.0.0.1", port);
}

AString TcpSocket::getHostAddress() const
{
	return hostaddress_;
}

ushort TcpSocket::getPort() const
{
	return port_;
}

SOCKET TcpSocket::getSocket() const
{
	return socket_;
}

void TcpSocket::terminate() const
{
	if (clientEventListener_) {
		clientEventListener_.get()->setIsRunning(false);
		clientEventListener_.get()->join();
	}
}
