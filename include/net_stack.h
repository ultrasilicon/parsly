#pragma once

#include <string>
#include <functional>
#include "packet.h"

class NetStack
{
public:
  NetStack();
  virtual ~NetStack();

  void message(Packet *p, const char *ip);

  virtual int connect(const std::string &ip, const int& addr) = 0;
  virtual int write(std::string &data, const char *addr) = 0;

protected:
  std::function<void(Packet*)> onMessage;

};

