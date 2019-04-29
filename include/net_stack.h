#pragma once

#include <string>
#include <functional>
#include <libparsley/function.h>
#include "packet.h"
#include "parse_engine.h"

class NetStack
{
public:
  Parsley::CallbackHandler<void(Packet*)> onMessage;

  NetStack();
  virtual ~NetStack();

  virtual void message(Packet *p, const char* ip = "");
  virtual int connect(const std::string& ip, const int& addr);

protected:
  virtual int write(const std::string& p, const char* ip) = 0;
  virtual void read(char* data);
  ParseEngine engine;
};

