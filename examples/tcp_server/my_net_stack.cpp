#include "my_net_stack.h"


MyNetStack::MyNetStack(Loop *l)
  : socket(new TcpSocket(l))
{}

MyNetStack::~MyNetStack()
{}

int MyNetStack::connect(const string &ip, const int &addr)
{
  socket->connect(ip.c_str(), addr);
  socket->start();
  return 0;
}

int MyNetStack::write(const string &data, const char *)
{
  socket->write(data);
  cout << "MyNetStack::write: " << data << endl;
  return 0;
}

void MyNetStack::stop()
{
  socket->close();
}

TcpSocket *MyNetStack::getSocket() const
{
  return socket;
}
