#include "tcpeventlistener.h"

/**
 * \brief Constructs instance by setting local client pointer
 * to passed param and isRunning to true.
 * \param client pointer to client instance
 */
TcpEventListener::TcpEventListener(TcpSocket* client) :
	client(client),
	isRunning_(true)
{
}

/**
* \brief Constructs instance by setting local server pointer
* to passed param and isRunning to true.
* \param server pointer to server instance
*/
TcpEventListener::TcpEventListener(TcpServer* server) :
	server(server),
	isRunning_(true)
{
}

/**
 * \brief Sets isRunning to value passed by param isRunning.
 * \param isRunning whether thread should run or not
 */
void TcpEventListener::setIsRunning(const bool isRunning)
{
	isRunning_ = isRunning;
}
