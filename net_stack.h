#pragma once


#include "packet.h"

class NetStack
{
public:
  NetStack();
  virtual int write(char* data);

protected:
};

