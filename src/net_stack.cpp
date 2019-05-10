#include "net_stack.h"
#include <iostream>

NetStack::NetStack()
{

}

NetStack::~NetStack()
{

}

void NetStack::message(Packet *p, const char *ip)
{
  if(p)
    {
      iovec v = engine.encode(p);
      std::string s((char*)v.iov_base, v.iov_len);
      write(s, ip);
    }
}

int NetStack::connect(const std::string &ip, const int &addr)
{

}

void NetStack::read(char *data)
{
  Packet* p = engine.decode(data, strlen(data));
  onMessage(p);
}


