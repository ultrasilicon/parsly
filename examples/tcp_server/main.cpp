#include <iostream>
#include <string>
#include <vector>
#include <libparsley/tcp_server.h>
#include <parsly/parse_engine.h>

using namespace std;
using namespace Parsley;

class MyNetStack;


static Loop loop;
static vector<TcpSocket*> clients;

class MyNetStack
    : public NetStack
{
public:
  MyNetStack(Loop *l)
    : sock(new TcpSocket(l))
  {}
  virtual ~MyNetStack()
  {}

  int write(string& data, const char *)
  {
    sock->write(data);
    cout << "MyNetStack::write: " << data << endl;
    return 0;
  }

  void stop()
  {
    sock->close();
  }

  TcpSocket* getSocket() const
  {
    return sock;
  }

private:
  TcpSocket *sock;
};

void receive_cb(string& data, TcpSocket* sock)
{
  cout << sock->peerAddress()->toIPString() << ": " << data << endl;
}

void new_connection_cb(TcpServer* s)
{
  MyNetStack* ns = new MyNetStack(&loop);
  ParseEngine *engine = new ParseEngine(ns);

  TcpSocket *sock = ns->getSocket();
  clients.push_back(sock);
  connect(&sock->onReadyRead, &receive_cb);
  s->accept(sock);
}

int main()
{
  TcpServer *server = new TcpServer(&loop);
  server->bind("0.0.0.0", 63773);
  server->listen();
  connect(&server->onNewConnection, &new_connection_cb);

  return loop.run();
}
