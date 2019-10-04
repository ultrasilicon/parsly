#ifndef MY_NET_STACK_H
#define MY_NET_STACK_H

#include <iostream>

#include <parsly/packet.h>
#include <parsly/net_stack.h>
#include <libagio/tcp_socket.h>
#include <libagio/timer.h>

using namespace std;
using namespace Agio;

class ClientSocket
    : public NetStack
{
public:
  ClientSocket(Loop* l);
  virtual ~ClientSocket();

  int connect(const std::string& ip, const int& addr);
  void stop();

  TcpSocket *getSocket() const;

protected:
  int write(const std::string& data, const char*);

private:
  TcpSocket* socket;
};



#endif // MY_NET_STACK_H
