#include "../common/my_net_stack.h"
#include "libparsley/tcp_server.h"

using namespace std;
using namespace Parsley;


static Loop loop;
static vector<TcpSocket*> clients;

void receive_cb(string& data, TcpSocket* sock)
{
  cout << sock->peerAddress()->toIPString() << ": " << data << endl;
}

void new_connection_cb(TcpServer* s)
{
  MyNetStack* ns = new MyNetStack(&loop);

  TcpSocket *sock = ns->getSocket();
  clients.push_back(sock);
  on(&sock->onReadyRead, &receive_cb);
  s->accept(sock);
}

int main()
{
  TcpServer *server = new TcpServer(&loop);
  server->bind("0.0.0.0", 63773);
  server->listen();
  on(&server->onNewConnection, &new_connection_cb);

  return loop.run();
}
