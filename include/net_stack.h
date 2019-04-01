#pragma once

#include <string>
#include "packet.h"

class NetStack
{
public:
  NetStack();
  virtual ~NetStack();

  virtual int write(std::string &data, const char *addr) = 0;

protected:
};

