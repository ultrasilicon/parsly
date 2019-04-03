#ifndef MY_NET_STACK_H
#define MY_NET_STACK_H

#include <parsly/packet.h>
#include <parsly/net_stack.h>
#include <libparsley/tcp_socket.h>
#include <libparsley/timer.h>

using namespace std;
using namespace Parsley;

class MyNetStack
    : public NetStack
{
public:
  MyNetStack(Loop* l);
  virtual ~MyNetStack();

  int connect(const std::string& ip, const int& addr);
  void stop();

  TcpSocket *getSocket() const;

protected:
  int write(const std::string& data, const char*);

private:
  TcpSocket* socket;
};



#endif // MY_NET_STACK_H
