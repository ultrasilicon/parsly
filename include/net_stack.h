#pragma once

#include <string>
#include "packet.h"

class NetStack
{
public:
  NetStack();
  virtual ~NetStack();

  virtual int write(char* data, std::string ip);

protected:
};

