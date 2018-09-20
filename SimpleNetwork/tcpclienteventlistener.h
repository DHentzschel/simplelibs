#ifndef TCPCLIENTEVENTLISTENER_H
#define TCPCLIENTEVENTLISTENER_H

#include <thread>

#include "tcpeventlistener.h"

class TcpClientEventListener : public TcpEventListener {
  public:
    explicit TcpClientEventListener(TcpSocket* client);

    virtual ~TcpClientEventListener() = default;

    void join();

  private:
    std::thread thread_;

    void initialize() override;

    void start() override;
};

#endif   // TCPCLIENTEVENTLISTENER_H
