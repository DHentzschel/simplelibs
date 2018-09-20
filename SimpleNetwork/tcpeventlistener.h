#ifndef TCPEVENTLISTENER_H
#define TCPEVENTLISTENER_H

class TcpServer;

class TcpSocket;

class TcpEventListener {
  public:
    explicit TcpEventListener(TcpSocket* client);

    explicit TcpEventListener(TcpServer* server);

    virtual ~TcpEventListener() = default;

    void setIsRunning(bool isRunning);

  protected:
    union {
        TcpServer* server;

        TcpSocket* client;
    };

    bool isRunning_;

    virtual void initialize() = 0;

    virtual void start() = 0;
};

#endif   // TCPEVENTLISTENER_H
