#pragma once

#include <string>
#include "packet.h"

class NetStack
{
public:
  NetStack();

  virtual int write(std::string &data, const char *ip);

protected:
};

