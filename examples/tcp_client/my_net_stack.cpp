#include "my_net_stack.h"


MyNetStack::MyNetStack(Loop *l)
  : sock(new TcpSocket(l))
{}

MyNetStack::~MyNetStack()
{}

int MyNetStack::connect(const string &ip, const int &addr)
{
  sock->connect(ip.c_str(), addr);
  sock->start();
  return 0;
}

int MyNetStack::write(const string &data, const char *)
{
  sock->write(data);
  cout << "MyNetStack::write: " << data << endl;
  return 0;
}

void MyNetStack::stop()
{
  sock->close();
}
