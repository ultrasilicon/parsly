#include "my_net_stack.h"


ClientSocket::ClientSocket(Loop *l)
  : socket(new TcpSocket(l))
{}

ClientSocket::~ClientSocket()
{}

int ClientSocket::connect(const string &ip, const int &addr)
{
  socket->connect(ip.c_str(), addr);
  socket->start();
  return 0;
}

int ClientSocket::write(const string &data, const char *)
{
  socket->write(data);
  cout << "MyNetStack::write: " << data << endl;
  return 0;
}

void ClientSocket::stop()
{
  socket->close();
}

TcpSocket *ClientSocket::getSocket() const
{
  return socket;
}
