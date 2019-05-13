#include "tcpserver.h"

#include <WS2tcpip.h>

#include <mutex>

#include <functions.h>

#include "console.h"
#include "logger.h"
#include "tcpservereventlistener.h"

TcpServer::TcpServer() :
	currentSocket_(nullptr),
	addressLength_(0),
	serverEventListener_(nullptr)
{
	initialize();
}

TcpServer::~TcpServer()
{
	closesocket(socket_);
}

bool TcpServer::listen(const AString& hostaddress, const ushort port)
{
	SOCKADDR_IN server;
	ZEROMEMORY(&server);

	inet_pton(AF_INET, hostaddress.toCString(), &server.sin_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

#pragma warning(disable : 6385)
	if (::bind(socket_, (sockaddr*)(&server), sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
		Logger::error("bind() failed. Error code: " +
			AString::toString(WSAGetLastError()));
		return false;
	}
#pragma warning(default : 6385)

	if (::listen(socket_, 2)) {
		Logger::error("listen() failed. Error code: " +
			AString::toString(WSAGetLastError()));
		return false;
	}

	addressLength_ = sizeof(sockaddr_in);
	serverEventListener_ = std::make_shared<TcpServerEventListener>(this);
	return true;
}

void TcpServer::terminate() const
{
	if (serverEventListener_) {
		serverEventListener_.get()->setIsRunning(false);
		serverEventListener_.get()->join();
	}
}

void TcpServer::initialize()
{
	WSADATA wsaData;
	ZeroMemory(&wsaData, sizeof(WSADATA));

	if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
		Logger::error("WSAStartup() failed. Error code: " + AString::toString(WSAGetLastError()));
		exit(EXIT_FAILURE);
	}
	if ((socket_ = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		Logger::error("socket() failed. Error code: " + AString::toString(WSAGetLastError()));
		exit(EXIT_FAILURE);
	}

	socketList_.reserve(1024);
}

TcpSocket* TcpServer::getSocket(const SOCKET & socket)
{
	for (auto& tempSocket : socketList_) {
		if (tempSocket->socket_ == socket) {
			return tempSocket;
		}
	}
	return nullptr;
}
