#include <iostream>
#include <string>
#include <parsly/packet.h>
#include <parsly/parse_engine.h>
#include <libparsley/tcp_socket.h>
#include <libparsley/timer.h>

using namespace std;
using namespace Parsley;

class MyNetStack;

static MyNetStack* net;
static ParseEngine* engine;
static Loop* loop;
static int counter = 0;

class MyNetStack
    : public NetStack
{
public:
  MyNetStack(Loop *l)
    : sock(new TcpSocket(l))
  {
    connect("127.0.0.1", 63773);
  }

  virtual ~MyNetStack() {}

  int connect(const std::string &ip, const int& addr)
  {
    sock->connect(ip.c_str(), addr);
    sock->start();
    return 0;
  }

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

private:
  TcpSocket *sock;
};

void timeout_cb(Timer *t)
{
  Packet pk({
              {
                std::string{"UUID"},
                std::string{"Tim Zheng"},
                std::string{"PUBKEY"},
                uint32_t{2019}
              },
              0
            });
  engine->message(&pk, "127.0.0.1");

  if(3 == ++ counter)
    {
      t->stop();
    }
}

int main()
{
  loop = new Loop();
  net = new MyNetStack(loop);
  engine = new ParseEngine(net);

  Timer *timer = new Timer(3000, 1000, loop);
  on(&timer->onTimedOut, &timeout_cb);
  timer->start();

  return loop->run();
}


