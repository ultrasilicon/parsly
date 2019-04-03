#include "my_net_stack.h"


using namespace std;
using namespace Parsley;

static MyNetStack* net;
static int counter = 0;

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
  net->message(&pk);

  if(3 == ++ counter)
    {
      t->stop();
      net->stop();
    }
}

int main()
{
  Loop loop;;
  net = new MyNetStack(&loop);
  net->connect("127.0.0.1", 63773);

  Timer *timer = new Timer(3000, 1000, &loop);
  on(&timer->onTimedOut, &timeout_cb);
  timer->start();

  return loop.run();
}


