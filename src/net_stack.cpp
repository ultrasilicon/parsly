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

void NetStack::read(const Buffer* data)
{
  std::cout << "dataaa:" << data->data() << std::endl;
  Packet* p = engine.decode((char*)data->data(), data->length());
  onMessage(p);
  delete data;
}


