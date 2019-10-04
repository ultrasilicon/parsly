#pragma once

#include <string>
#include <libagio/function.h>
#include <libagio/buffer.h>
#include "parse_engine.h"

using namespace Agio;

class NetStack
{
public:
  Agio::CallbackHandler<void(Packet*)> onMessage;

  NetStack();
  virtual ~NetStack();

  virtual void message(Packet *p, const char* ip = "");
  void read(const Buffer* data);
  virtual int connect(const std::string& ip, const int& addr);

protected:
  virtual int write(const std::string& p, const char* ip) = 0;
  ParseEngine engine;
};

